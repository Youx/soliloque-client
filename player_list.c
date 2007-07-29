#include "player_list.h"

static void * decode_player(void * data, struct player * pl) {
  void * ptr = data;
  guint8 len;

  /* Retreive the public ID */
  pl->public_id = GUINT32_FROM_LE(*(guint32 *) ptr);
  ptr = (guint32 *)ptr + 1;
  /* Retreive the channel ID */
  pl->channel_id = GUINT32_FROM_LE(*(guint32 *) ptr);
  ptr = (guint32 *)ptr + 1;
  /* Retreive the channel privileges */
  pl->chan_privileges = GUINT16_FROM_LE(*(guint16 *) ptr);
  ptr = (guint16 *)ptr + 1;
  /* Retreive the channel privileges */
  pl->global_flags = GUINT16_FROM_LE(*(guint16 *) ptr);
  ptr = (guint16 *)ptr + 1;
  /* Retreive the player attributes */
  pl->player_attributes = GUINT16_FROM_LE(*(guint16 *) ptr);
  ptr = (guint16 *)ptr + 1;

  len = *(guint8 *)ptr;
  ptr = (guint8 *)ptr +1;

  strncpy(pl->name, ptr, len);
  ptr = (char*)ptr + 29;

  return ptr;
}

void print_player(struct player * pl) {
  printf("  id: %i\n", pl->public_id);
  printf("    name: %s\n", pl->name);

  printf("    global flags: ");
  if(pl->global_flags & GLOBAL_FLAG_SERVERADMIN)
    printf("SA, ");
  if(pl->global_flags & GLOBAL_FLAG_ALLOWREG)
    printf("reg allowed, ");

  if(pl->global_flags & GLOBAL_FLAG_REGISTERED) {
    printf("R\n");
  }
  else {
    printf("U\n");
  }

  printf("    channel privileges: ");
  if(pl->chan_privileges & CHANNEL_PRIV_CHANADMIN)
    printf("CA ");
  if(pl->chan_privileges & CHANNEL_PRIV_OP)
    printf("OP ");
  if(pl->chan_privileges & CHANNEL_PRIV_VOICE)
    printf("V ");
  if(pl->chan_privileges & CHANNEL_PRIV_AUTOOP)
    printf("AOP ");
  if(pl->chan_privileges & CHANNEL_PRIV_AUTOVOICE)
    printf("AV ");
  printf("\n");

  printf("    player attributes: ");
  if(pl->player_attributes & PL_ATTR_BLOCK_WHISPER)
    printf("block whispers ");
  if(pl->player_attributes & PL_ATTR_AWAY)
    printf("away ");
  if(pl->player_attributes & PL_ATTR_MUTE_MIC)
    printf("mic muted ");
  if(pl->player_attributes & PL_ATTR_MUTE_SPK)
    printf("speaker muted ");
  printf("\n");
}

void print_player_list(struct player_list * pll) {
  int i;

  printf("Player list : (%i players)\n", pll->size);
  for(i=0 ; i<pll->size ; i++) {
    print_player(& pll->players[i]);
  }
}


struct player_list * decode_player_list(void * data) {
  int i;
  void * ptr = data;
  struct player_list * pll = (struct player_list *)calloc(sizeof(struct player_list), 1);

  ptr = (guint32 *)ptr + 6;

  pll->size = GUINT32_FROM_LE(*(guint32 *)ptr);
  pll->players = (struct player *)calloc(sizeof(struct player), pll->size);
  ptr = (guint32 *)ptr +1;

  for(i=0 ; i<pll->size ; i++) {
    ptr = decode_player(ptr, & pll->players[i]);
  }

  return pll;
}


