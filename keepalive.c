#include "keepalive.h"



static void  * init_keepalive(guint32 priv_id, guint32 pub_id, guint32 counter) {
  guint32 * msg = calloc(sizeof(guint32), 5);
  msg[0] = GUINT32_TO_LE(0x0001bef4);
  msg[1] = GINT32_TO_LE(priv_id);
  msg[2] = GINT32_TO_LE(pub_id);
  msg[3] = GINT32_TO_LE(counter);
  msg[4] = GINT32_TO_LE(crc_32(msg, sizeof(guint32) * 5, 0xEDB88320));

  return msg;
}

static void destroy_keepalive(void * msg) {
  free(msg);
}

void send_keepalive(guint32 private_id, guint32 public_id, guint32 counter,int s, const struct sockaddr * to) {
  guint8 * msg = init_keepalive(private_id, public_id, counter);
  sendto(s, msg, 5*sizeof(guint32), 0, to, sizeof(*to));
  destroy_keepalive(msg);
}

