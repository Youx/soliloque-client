/**
 * file 		:	highlevel.h
 * creator		:	Hugo Camboulive
 * description	:	Contains abstract structures for teamspeak
 */

#ifndef __HIGH_LEVEL_H__
#define __HIGH_LEVEL_H__


#include "compat.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void receive(int sockfd, struct sockaddr_in * servaddr);

/* List of codecs with values */


#endif

