/**
 *  file        : acknowledge.h
 *  license     : GPLV3
 *  copyright   : Hugo Camboulive
 *  description : This header contains information
 *   about functions and structures used to send an
 *   ACK message to a teamspeak server.
 */


#include "acknowledge.h"


struct acknowledge * init_acknowledge(guint32 * client_id) {
  struct acknowledge * msg;
  msg = (struct acknowledge *)calloc(1, sizeof(struct acknowledge));
  msg->function = 0x0000bef1;
  memcpy(msg->client_id, client_id, 8);
  msg->counter = 1;
  return msg;
}

void send_acknowledge(guint32 * client_id, )