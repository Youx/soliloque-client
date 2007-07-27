/**
 *  file        : acknowledge.h
 *  license     : GPLV3
 *  copyright   : Hugo Camboulive
 *  description : This header contains information
 *   about functions and structures used to send an
 *   ACK message to a teamspeak server.
 */


#include "acknowledge.h"


struct acknowledge {
  guint32 function;
  guint32 private_id;
  guint32 public_id;
  guint32 counter;
};



static struct acknowledge * init_acknowledge(guint32 private_id, guint32 public_id, guint32 counter) {
  struct acknowledge * msg;
  msg = (struct acknowledge *)calloc(1, sizeof(struct acknowledge));

  msg->function =  TYPE_ACKNOWLEDGE;

  msg->private_id = GUINT32_TO_LE(private_id);
  msg->public_id = GUINT32_TO_LE(public_id);

  msg->counter = GUINT32_TO_LE(counter);
  return msg;
}

static void destroy_acknowledge(struct acknowledge * msg) {
  free(msg);
}

void send_acknowledge(guint32 private_id, guint32 public_id, guint32 counter, int s, const struct sockaddr * to) {
  struct acknowledge * msg;

  msg = init_acknowledge(private_id, public_id, counter);

  sendto(s, msg, sizeof(struct acknowledge), 0, to, sizeof(*to));

  destroy_acknowledge(msg);
}

