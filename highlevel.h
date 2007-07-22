/**
 * file 		:	highlevel.h
 * creator		:	Hugo Camboulive
 * description	:	Contains abstract structures for teamspeak
 */

#ifndef __HIGH_LEVEL_H__
#define __HIGH_LEVEL_H__


#include <glib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void receive(int sockfd, struct sockaddr_in * servaddr);

/* List of codecs with values */
enum codec {
	CELP_5_1,
	CELP_6_3,
	GSM_14_8,
	GSM_16_4,
	CELPWin_5_2,
	SPEEX_3_4,
	SPEEX_5_2,
	SPEEX_7_2,
	SPEEX_9_3,
	SPEEX_12_3,
	SPEEX_16_3,
	SPEEX_19_6,
	SPEEX_25_9
};

#endif

