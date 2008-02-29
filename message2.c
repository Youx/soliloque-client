#include "message2.h"
#include "highlevel.h"

struct message2 {
  uint32_t function;
  uint32_t private_id;
  uint32_t public_id;
  uint32_t counter;
  uint32_t empty;
  uint32_t checksum;

  unsigned char data [96];
};


static struct message2 * init_message2(uint32_t private_id, uint32_t public_id, uint32_t counter) {
  struct message2 * msg;
  msg = (struct message2 *)calloc(1, sizeof(struct message2));

  msg->function = TYPE_SERVER_INFO_RESPONSE;
  msg->private_id = GINT32_TO_LE(private_id);
  msg->public_id = GINT32_TO_LE(public_id);
  msg->counter = GINT32_TO_LE(counter);

  /*  memcpy(msg->data, "\x00\x00\x00\x00\x9b\x90\xdf\xb2\x01\x00\x00\xbf\x10\x00\x00\x00\x7e\x67\xdf\xb7\x7e\x67\xdf\xb7\x90\x9e\x7f\x08\x48\xc7\xcd\xbf\xa9\x72\xd2\xb7\x01\x15\x00\x00\x00\x15\x00\x00\x20\x81\xde\xb7\x98\x8b\x32\x08\x3c\x7b\xdf\xb7\x3c\x7b\xdf\xb7\x20\x81\xde\xb7\x01\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\xf8\xba\x2c\x08\xf8\xc7\xcd\xbf\x6c\xc7\xcd\xbf\x20\x7f\xdf\xb7\x9c\x05\x08\x08\xf8\xba\x2c\x08\x00\x00\x00\x00", 96);
  */
  msg->checksum = GINT32_TO_LE(crc_32(msg, sizeof(struct message2), 0xEDB88320));
  return msg;
}

static void destroy_message2(struct message2 * msg) {
  free(msg);
}

void send_message2(uint32_t private_id, uint32_t public_id, int s, const struct sockaddr * to) {
  struct message2 * msg;

  msg = init_message2(private_id, public_id, 1);

  sendto(s, msg, sizeof(struct message2), 0, to, sizeof(*to));

  destroy_message2(msg);
}

