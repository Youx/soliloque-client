#include "keepalive.h"



static void  * init_keepalive(uint32_t priv_id, uint32_t pub_id, uint32_t counter) {
  uint32_t * msg = calloc(sizeof(uint32_t), 5);
  msg[0] = GUINT32_TO_LE(0x0001bef4);
  msg[1] = GINT32_TO_LE(priv_id);
  msg[2] = GINT32_TO_LE(pub_id);
  msg[3] = GINT32_TO_LE(counter);
  msg[4] = GINT32_TO_LE(crc_32(msg, sizeof(uint32_t) * 5, 0xEDB88320));

  return msg;
}

static void destroy_keepalive(void * msg) {
  free(msg);
}

void send_keepalive(uint32_t private_id, uint32_t public_id, uint32_t counter,int s, const struct sockaddr * to) {
  uint8_t * msg = init_keepalive(private_id, public_id, counter);
  sendto(s, msg, 5*sizeof(uint32_t), 0, to, sizeof(*to));
  destroy_keepalive(msg);
}

