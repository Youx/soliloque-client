/**
 *  file        : acknowledge.h
 *  license     : GPLV3
 *  copyright   : Hugo Camboulive
 *  description : This header contains information
 *   about functions and structures used to send an
 *   ACK message to a teamspeak server.
 */

#ifndef __ACKNOWLEDGE_H__
#define __ACKNOWLEDGE_H__

#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define TYPE_ACKNOWLEDGE GINT32_TO_LE(0x0000bef1)



void send_acknowledge(guint32 private_id, guint32 public_id, guint32 counter, int s, const struct sockaddr * to);


#endif

