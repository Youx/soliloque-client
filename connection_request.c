/**
 *  file        : connection_request.c
 *  license     : GPLV3
 *  copyright   : Hugo Camboulive
 *  description : This source connects us to a
 *   teamspeak server using some low level structures
 *   and functions.
 *
 *  TODO : replace the struct message1 by a data block
 *   (void *) so that we are sure to avoid all padding
 *   and alignement problems.
 */

/* hidden */

#include "connection_request.h"


struct message1 {
  uint32_t function;
  uint32_t private_id;
  uint32_t public_id;
  uint32_t counter;

  uint32_t checksum;

  uint8_t client_size;
  char client[29];

  uint8_t machine_size;
  char machine[29];

  uint32_t data1;
  uint32_t data2;

  uint8_t assign_nick;

  uint8_t always1;

  uint8_t login_size;
  char login[29];

  uint8_t pass_size;
  char pass[29];

  uint8_t nick_size;
  char nick[29];
};

/* No need to access it from outside */
static struct message1 * encode_connection_request(struct connection_request * req) {
  struct message1 * msg;
  msg = (struct message1 *)calloc(1, sizeof(struct message1));

  msg->function = GUINT32_TO_LE(0x0003bef4);
  msg->counter = GUINT32_TO_LE(1);

  msg->client_size = 9;
  memcpy(msg->client, "TeamSpeak", 9);

  /* cut machine if too long */
  if(strlen(req->machine) > 29)
    req->machine[29] = '\0';
  msg->machine_size = (uint8_t)strlen(req->machine);
  memcpy(msg->machine, req->machine, strlen(req->machine));

  msg->data1 = GUINT32_TO_LE(0x02000000);
  msg->data2 = GUINT32_TO_LE(0x20003C00);

  msg->assign_nick = req->assign_nick;
  msg->always1 = 0x01;

  /* Insert login */
  if(strlen(req->login) > 29)
    req->login[29] = '\0';
  msg->login_size = (uint8_t)strlen(req->login);
  memcpy(msg->login, req->login, strlen(req->login));

  /* Insert password */
  if(strlen(req->pass) > 29)
    req->pass[29] = '\0';
  msg->pass_size = (uint8_t)strlen(req->pass);
  memcpy(msg->pass, req->pass, strlen(req->pass));

  /* Insert nick */
  if(strlen(req->nick) > 29)
    req->nick[29] = '\0';
  msg->nick_size = (uint8_t)strlen(req->nick);
  memcpy(msg->nick, req->nick, strlen(req->nick));

  msg->checksum = GINT32_TO_LE(crc_32(msg, sizeof(struct message1), 0xEDB88320));

  return msg;
}

int connect_to(struct connection_request * req, int * sockfd, struct sockaddr_in * servaddr) {	
  struct message1 * msg1;

  * sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  bzero(servaddr, sizeof(*servaddr));
  servaddr->sin_family = AF_INET;
/*  servaddr->sin_addr.s_addr = inet_addr("127.0.0.1");*/
  servaddr->sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr->sin_port = htons(8767);

  msg1 = encode_connection_request(req);
  sendto(*sockfd, msg1, 180, 0, (struct sockaddr *)servaddr, sizeof(*servaddr));

  free(msg1);

  return *sockfd;
}
