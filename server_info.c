#include "server_info.h"


struct message1a {
  guint32 function;
  guint32 useless_client_id[2];
  guint32 counter;

  guint32 checksum;

  guint8 servername_size;
  gchar servername[29];

  guint8 machine_size;
  gchar machine[29];

  guint8 data1[92];

  guint32 private_id;
  guint32 public_id;

  guint8 welcome_size;
  gchar welcome[255];
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

