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

#define TYPE_SERVER_INFO GINT32_TO_LE(0x0004bef4)


struct server_info {
	guint32 private_id;
	guint32 public_id;
	char servername[30];
	char machine[30];
};

struct server_info * decode_server_info(void * resp);
void print_server_info(struct server_info * si);

#endif

