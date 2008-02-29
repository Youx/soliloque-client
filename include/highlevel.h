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
#include "player_quit.h"


#define TYPE_SERVER_INFO_RESPONSE 		GINT32_TO_LE(0x0005bef0)
#define TYPE_CHANNEL_LIST							GINT32_TO_LE(0x0006bef0)
#define TYPE_PLAYER_LIST 							GINT32_TO_LE(0x0007bef0)
#define TYPE_AFTER_PLAYER_LIST	GINT32_TO_LE(0x0008bef0)
#define TYPE_NEW_PLAYER								GINT32_TO_LE(0x0064bef0)
/* Unknown : 
 *  0x6dbef0
 *  0x68bef0
 * debut de conversation ou qqch comme ça?   
 */


#define TYPE_ACKNOWLEDGE					GINT32_TO_LE(0x0000bef1)

#define TYPE_CONNECTION_REQUEST		GINT32_TO_LE(0x0003bef4)
#define TYPE_SERVER_INFO 					GINT32_TO_LE(0x0004bef4)
#define TYPE_KEEPALIVE						GINT32_TO_LE(0x0002bef4)
#define TYPE_RESP_8BEF0						GINT32_TO_LE(0x0001bef4)

void receive(int sockfd, struct sockaddr_in * servaddr);

/* List of codecs with values */


#endif

