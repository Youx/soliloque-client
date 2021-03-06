/**
 *  file        : server_info.h
 *  license     : GPLV3
 *  copyright   : Hugo Camboulive
 *  description : This header contains information
 *   about functions and structures used to connect
 *   to a teamspeak server.
 */

#ifndef __SERVER_INFO_H__
#define __SERVER_INFO_H__

#include "compat.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct server_info {
	uint32_t private_id;
	uint32_t public_id;
	char servername[30];
	char machine[30];
};

struct server_info * decode_server_info(void * resp);
void print_server_info(struct server_info * si);

#endif

