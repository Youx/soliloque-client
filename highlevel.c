#include "highlevel.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "compat.h"

#include "connection_request.h"
#include "message2.h"
#include "server_info.h"
#include "acknowledge.h"
#include "channel_list.h"
#include "player_list.h"
#include "keepalive.h"

void dump(void * str, int len, char * filename) {
  int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  write(fd, str, len);
  close(fd);
}

void append(void * str, int len, char * filename) {
  int fd = open(filename, O_APPEND|O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  write(fd, str, len);
  close(fd);
}

void printtype(gint32 type) {
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
    printtype(*(gint32 *)data);

    switch(*((gint32 *) data)) {
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
      case GUINT32_TO_LE(0xc00bef3): /* audio */
	/* dump(data, n, "audiopacket.dat"); */
	append(data+24, n-24, "audiopacket2.spx");
	send_keepalive(si->private_id, si->public_id, keepalive_counter++, sockfd, (struct sockaddr *)servaddr);
	/*exit(0);*/
      default: /* try this to keep it alive... */
	send_keepalive(si->private_id, si->public_id, keepalive_counter++, sockfd, (struct sockaddr *)servaddr);
    }
  }
}
