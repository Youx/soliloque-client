#include "message2.h"

struct message2 {
  guint32 function;
  guint32 client_id[2];
  guint32 counter;
  guint32 empty;
  guint32 checksum;

  guchar data [96];
};


static struct message2 * init_message2(guint32 * client_id) {
  struct message2 * msg;
  msg = (struct message2 *)calloc(1, sizeof(struct message2));
  
  client_id[0] = GINT32_TO_LE(client_id[0]);
  client_id[1] = GINT32_TO_LE(client_id[1]);

  msg->function = TYPE_SERVER_INFO_RESPONSE;
  memcpy(msg->client_id, client_id, 8);
  msg->counter = GINT32_TO_LE(1);
/*  memcpy(msg->data, "\x00\x00\x00\x00\x9b\x90\xdf\xb2\x01\x00\x00\xbf\x10\x00\x00\x00\x7e\x67\xdf\xb7\x7e\x67\xdf\xb7\x90\x9e\x7f\x08\x48\xc7\xcd\xbf\xa9\x72\xd2\xb7\x01\x15\x00\x00\x00\x15\x00\x00\x20\x81\xde\xb7\x98\x8b\x32\x08\x3c\x7b\xdf\xb7\x3c\x7b\xdf\xb7\x20\x81\xde\xb7\x01\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\xf8\xba\x2c\x08\xf8\xc7\xcd\xbf\x6c\xc7\xcd\xbf\x20\x7f\xdf\xb7\x9c\x05\x08\x08\xf8\xba\x2c\x08\x00\x00\x00\x00", 96);
*/
  msg->checksum = GINT32_TO_LE(crc_32(msg, sizeof(struct message2), 0xEDB88320));
  return msg;
}

void send_message2(guint32 * client_id, int s, const struct sockaddr * to) {
	struct message2 * msg = init_message2(client_id);
	
	sendto(s, msg, sizeof(struct message2), 0, to, sizeof(*to));
}