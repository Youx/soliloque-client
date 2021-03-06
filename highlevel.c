#include "highlevel.h"
#include "log_packet.h"
#include "ringbuffer.h"
#include "encoder.h"
#include <semaphore.h>

struct server_info * si;
struct channel_list * chl;
struct player_list * pll;
int ack_counter = 1;
int keepalive_counter = 2;
int32_t audiosend_counter = 0;

extern ringbuffer_t * microphone;

int16_t encode_buffer[5*160];

extern int sockfd;
extern struct sockaddr_in * pservaddr;
extern sem_t * sem_microphone;

void * encode_thread(void * args) {
	int i,n;
	unsigned char data[10000];
  printf("thread launched\n");
	while(1) {
    for(i=0;i<5;i++) {
      //printf("sem_wait\n");
      sem_wait(sem_microphone);
    }
		//if(ringbuffer_canRead(microphone, 5)) {
    for(i=0;i<5;i++)
      ringbuffer_read(microphone, encode_buffer + (i*160) );

    n = encode_audio(encode_buffer, 5, (char *)data, CODEC_SPEEX_19_6);
    send_audio(si->public_id, si->private_id, audiosend_counter++,
        (char *)data, n, sockfd, (struct sockaddr *)pservaddr);
		//}
	}
}


void receive(int sockfd, struct sockaddr_in * servaddr) {
  int n, i;

  unsigned char data[10000];

  while(1) {
    bzero(data, 10000);
    n = recvfrom(sockfd, data, 10000, 0, NULL, NULL);
    //printtype(*(int32_t *)data);

    switch(*((int32_t *) data)) {
      case TYPE_SERVER_INFO:
				si = decode_server_info( (struct message1a *)data);
				print_server_info(si);
				send_message2(si->private_id, si->public_id, sockfd, (struct sockaddr *)servaddr);
				break;
      case TYPE_ACKNOWLEDGE:
				break;
      case TYPE_CHANNEL_LIST:
				chl = decode_channel_list(data);
				print_channel_list(chl);
				send_acknowledge(si->private_id, si->public_id, ack_counter++, sockfd, (struct sockaddr *)servaddr);
				break;
      case TYPE_PLAYER_LIST:
				pll = decode_player_list(data);
				print_player_list(pll);
				send_acknowledge(si->private_id, si->public_id, ack_counter++, sockfd, (struct sockaddr *)servaddr);
				break;
      case GUINT32_TO_LE(TYPE_AFTER_PLAYER_LIST):
				send_acknowledge(si->private_id, si->public_id, ack_counter++, sockfd, (struct sockaddr *)servaddr);
				send_keepalive(si->private_id, si->public_id, keepalive_counter++, sockfd, (struct sockaddr *)servaddr);
				break;
      case GUINT32_TO_LE(0x0002bef4): /* some kind of keepalive? or maybe data? */
				//usleep(10);
				send_keepalive(si->private_id, si->public_id, keepalive_counter++, sockfd, (struct sockaddr *)servaddr);
				break;
      case GUINT32_TO_LE(0x0c00bef3): /* speex 26.4 kbps */
      case GUINT32_TO_LE(0x0b00bef3): /* speex 18.2 kbps */
      case GUINT32_TO_LE(0x0a00bef3): /* speex 15 kbps */
      case GUINT32_TO_LE(0x0900bef3): /* speex 11 kbps */
      case GUINT32_TO_LE(0x0800bef3): /* speex 8 kbps */
      case GUINT32_TO_LE(0x0700bef3): /* speex 8 kbps */
      case GUINT32_TO_LE(0x0300bef3): /* gsm 16.4 kbps */
      case GUINT32_TO_LE(0x0200bef3): /* gsm 14.8 kbps */
      case GUINT32_TO_LE(0x0100bef3): /* celp 6.3 kbps */
      case GUINT32_TO_LE(0x0000bef3): /* celp 5.1 kbps */
				decode_audio_packet(data);
				break;
      case GUINT32_TO_LE(0x0064bef0): /* player arrived */
				decode_new_player(data);
				send_acknowledge(si->private_id, si->public_id, ack_counter++, sockfd, (struct sockaddr *)servaddr);
				break;
      case GUINT32_TO_LE(0x0065bef0): /* player quit */
				decode_player_quit(data);
				send_acknowledge(si->private_id, si->public_id, ack_counter++, sockfd, (struct sockaddr *)servaddr);
				break;
      default: /* try this to keep it alive... */
        //usleep(10);
        log_packet((char *)data, n);
				send_acknowledge(si->private_id, si->public_id, ack_counter++, sockfd, (struct sockaddr *)servaddr);
				//send_keepalive(si->private_id, si->public_id, keepalive_counter++, sockfd, (struct sockaddr *)servaddr);
    }
  }
}



void printtype(int32_t type) {
  switch(type) {
    case TYPE_CONNECTION_REQUEST:
      printf("type : Connection Request\n");
      break;
    case TYPE_SERVER_INFO:
      printf("type : Server Info\n");
      break;
    case TYPE_ACKNOWLEDGE:
      printf("type : Acknowledge\n");
      break;
    case TYPE_CHANNEL_LIST:
      printf("type : Channel list\n");
      break;
    case TYPE_PLAYER_LIST:
      printf("type : Player list\n");
      break;
		case TYPE_AFTER_PLAYER_LIST:
			printf("type : After player list\n");
			break;
    case TYPE_KEEPALIVE: /* some kind of keepalive? or maybe data? */
      printf("type : Keepalive\n");
      break;
    case GUINT32_TO_LE(0x0c00bef3): /* speex 26.4 kbps */
    case GUINT32_TO_LE(0x0b00bef3): /* speex 18.2 kbps */ // <--- ici
    case GUINT32_TO_LE(0x0a00bef3): /* speex 15 kbps */
    case GUINT32_TO_LE(0x0900bef3): /* speex 11 kbps */
    case GUINT32_TO_LE(0x0800bef3): /* speex 8 kbps */
    case GUINT32_TO_LE(0x0700bef3): /* speex 8 kbps */
    case GUINT32_TO_LE(0x0300bef3): /* gsm 16.4 kbps */
    case GUINT32_TO_LE(0x0200bef3): /* gsm 14.8 kbps */
    case GUINT32_TO_LE(0x0100bef3): /* celp 6.3 kbps */
    case GUINT32_TO_LE(0x0000bef3): /* celp 5.1 kbps */
/*		: (unknown) 0x6dbef0
		type : (unknown) 0x68bef0           audio aussi... ou demande d'audio p-e???
*/
      printf("type : Audio data\n");
      break;
    case TYPE_NEW_PLAYER: /* new player arrived */
      printf("type : New player\n");
      break;
    default:
      printf("type : (unknown) 0x%x\n", type);
  }
}
