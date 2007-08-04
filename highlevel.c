#include "highlevel.h"



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
    case GUINT32_TO_LE(0xc00bef3):
      printf("type : Audio data\n");
      break;
    default:
      printf("type : (unknown) 0x%x\n", type);
  }
}

struct server_info * si;
struct channel_list * chl;
struct player_list * pll;
int ack_counter = 1;
int keepalive_counter = 2;

void receive(int sockfd, struct sockaddr_in * servaddr) {
  int n;

  unsigned char data[10000];

  while(1) {
    bzero(data, 10000);
    n = recvfrom(sockfd, data, 10000, 0, NULL, NULL);
/*    printf("%i char received\n", n);*/
    printtype(*(int32_t *)data);

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
      case GUINT32_TO_LE(0x0008bef0):
	send_acknowledge(si->private_id, si->public_id, ack_counter++, sockfd, (struct sockaddr *)servaddr);
	send_keepalive(si->private_id, si->public_id, keepalive_counter++, sockfd, (struct sockaddr *)servaddr);
	break;
      case GUINT32_TO_LE(0x0002bef4): /* some kind of keepalive? or maybe data? */
	sleep(1);
	send_keepalive(si->private_id, si->public_id, keepalive_counter++, sockfd, (struct sockaddr *)servaddr);
	break;
      case GUINT32_TO_LE(0xc00bef3): /* speex 26.4 kbps */
      case GUINT32_TO_LE(0xb00bef3): /* speex 18.2 kbps */
      case GUINT32_TO_LE(0xa00bef3): /* speex 15 kbps */
      case GUINT32_TO_LE(0x900bef3): /* speex 11 kbps */
      case GUINT32_TO_LE(0x800bef3): /* speex 8 kbps */
      case GUINT32_TO_LE(0x700bef3): /* speex 8 kbps */
	decode_audio_packet(data);
	break;
      default: /* try this to keep it alive... */
	send_keepalive(si->private_id, si->public_id, keepalive_counter++, sockfd, (struct sockaddr *)servaddr);
    }
  }
}
