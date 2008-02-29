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

#include "compat.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>




void send_acknowledge(uint32_t private_id, uint32_t public_id, uint32_t counter, int s, const struct sockaddr * to);


#endif

