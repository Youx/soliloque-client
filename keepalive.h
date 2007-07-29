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

void send_keepalive(guint32 private_id, guint32 public_id, guint32 counter,int s, const struct sockaddr * to);

#endif
