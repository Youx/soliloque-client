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

#include "connection_request.h"
#include "message2.h"
#include "server_info.h"
#include "acknowledge.h"
#include "channel_list.h"
#include "player_list.h"
#include "keepalive.h"
#include "toolbox.h"
#include "decoder.h"
#include "new_player.h"


void receive(int sockfd, struct sockaddr_in * servaddr);

/* List of codecs with values */


#endif

