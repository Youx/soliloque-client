#ifndef __KEEPALIVE_H__
#define __KEEPALIVE_H__

#include "compat.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "crc.h"

void send_keepalive(uint32_t private_id, uint32_t public_id, uint32_t counter,int s, const struct sockaddr * to);

#endif
