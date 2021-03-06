/**
 *  file        : connection_request.h
 *  license     : GPLV3
 *  copyright   : Hugo Camboulive
 *  description : This header contains information
 *   about functions and structures used to connect
 *   to a teamspeak server.
 */

#ifndef __CONNECTION_REQUEST_H__
#define __CONNECTION_REQUEST_H__


#include "compat.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h> /* htons */
#include <stdlib.h>
#include <string.h>

#include "crc.h"





/** This structure contains information 
 *  to connect to a teamspeak server     */
struct connection_request {
	char * machine;
	char * login;
	char * pass;
	char * nick;
	uint8_t assign_nick;
};


/** Connect to a teamspeak server.
 *  @return : socket                  */
int connect_to(struct connection_request * req, int * sockfd, struct sockaddr_in * servaddr);

#endif

