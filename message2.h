#ifndef __MESSAGE2_H__
#define __MESSAGE2_H__

#include "compat.h"
#include <stdlib.h>
#include "crc.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define TYPE_SERVER_INFO_RESPONSE GINT32_TO_LE(0x0005bef0)


void send_message2(uint32_t private_id, uint32_t public_id, int s, const struct sockaddr * to);

#endif

