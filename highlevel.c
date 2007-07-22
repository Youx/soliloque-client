#include "highlevel.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

#include "connection_request.h"
#include "message2.h"
#include "server_info.h"
#include "acknowledge.h"




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
	}
}




void receive(int sockfd, struct sockaddr_in * servaddr) {
	int n;
	struct server_info * si;
	
	guchar data[10000];
	n = recvfrom(sockfd, data, 10000, 0, NULL, NULL);
  	printf("%i char received\n", n);
	printf("packet type : %x\n", *(gint32 *)data);
	printtype(*(gint32 *)data);

	
	switch(*((gint32 *) data)) {
		case TYPE_SERVER_INFO:
		si = decode_server_info( (struct message1a *)data);
		print_server_info(si);
/*		m2 = init_message2(si->client_id);*/
/*		dump(data, sizeof(struct message1a), "message1a.dat");
		dump(m2, sizeof(struct message2), "message2.dat"); */
		send_message2(si->client_id, sockfd, (struct sockaddr *)servaddr);
		receive(sockfd, servaddr);
		break;
		
		case TYPE_ACKNOWLEDGE:

		break;
	}
}
