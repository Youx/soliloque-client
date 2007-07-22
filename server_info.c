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

  guint32 client_id[2];

  guint8 data2[256];
};


struct server_info * decode_server_info(void * respo) {
	struct message1a * resp = (struct message1a *)respo;
	struct server_info * r;
	r = (struct server_info *)calloc(sizeof(struct server_info), 1);
	
	r->client_id[0] = GINT32_FROM_LE(resp->client_id[0]);
	r->client_id[1] = GINT32_FROM_LE(resp->client_id[1]);
	
	strcpy(r->machine, resp->machine);
	strcpy(r->servername, resp->servername);
	
	return r;
}


void print_server_info(struct server_info * si){
	printf("Server Info\n");
	printf("  Client ID   : 0x%x%x\n", si->client_id[0], si->client_id[1]);
	printf("  Server name : %s\n", si->servername);
	printf("  Machine     : %s\n", si->machine);
}