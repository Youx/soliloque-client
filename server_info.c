#include "server_info.h"


struct message1a {
  uint32_t function;
  uint32_t useless_client_id[2];
  uint32_t counter;

  uint32_t checksum;

  uint8_t servername_size;
  char servername[29];

  uint8_t machine_size;
  char machine[29];

  uint8_t data1[92];

  uint32_t private_id;
  uint32_t public_id;

  uint8_t welcome_size;
  char welcome[255];
};


struct server_info * decode_server_info(void * respo) {
  struct message1a * resp = (struct message1a *)respo;
  struct server_info * r;
  r = (struct server_info *)calloc(sizeof(struct server_info), 1);

  r->private_id = GINT32_FROM_LE(resp->private_id);
  r->public_id = GINT32_FROM_LE(resp->public_id);

  strcpy(r->machine, resp->machine);
  strcpy(r->servername, resp->servername);

  return r;
}


void print_server_info(struct server_info * si){
  printf("Server Info\n");
/*  printf("  Client ID   : 0x%x%x\n", si->client_id[0], si->client_id[1]); */
  printf("  Server name : %s\n", si->servername);
  printf("  Machine     : %s\n", si->machine);
}

