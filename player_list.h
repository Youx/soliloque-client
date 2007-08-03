#ifndef __PLAYER_LIST_H__
#define __PLAYER_LIST_H__

#include "compat.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define TYPE_PLAYER_LIST GINT32_TO_LE(0x0007bef0)

/* Channel privileges */
#define CHANNEL_PRIV_CHANADMIN	1
#define CHANNEL_PRIV_OP		2
#define CHANNEL_PRIV_VOICE	4
#define CHANNEL_PRIV_AUTOOP	8
#define CHANNEL_PRIV_AUTOVOICE	16

/* Global flags */
#define GLOBAL_FLAG_SERVERADMIN	1
#define GLOBAL_FLAG_ALLOWREG	2
#define GLOBAL_FLAG_REGISTERED	4

/* Player attributes */
/* TODO: what are 1 and 2 ??? */
#define PL_ATTR_BLOCK_WHISPER 4
#define PL_ATTR_AWAY	      8
#define PL_ATTR_MUTE_MIC      16
#define PL_ATTR_MUTE_SPK      32


struct player {
  uint32_t public_id;
  uint32_t channel_id;

  uint16_t chan_privileges;
  uint16_t global_flags;
  uint16_t player_attributes;

  char name[29];
};

struct player_list {
  struct player * players;
  uint32_t size;
};

struct player_list * decode_player_list(void * data);
void print_player_list(struct player_list * pll);

#endif
