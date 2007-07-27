#ifndef __PLAYER_LIST_H__
#define __PLAYER_LIST_H__

#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define TYPE_PLAYER_LIST GINT32_TO_LE(0x0007bef0)



struct player {
  guint32 public_id;
  guint32 channel_id;
  guint16 flags[3];
  char name[29];
};

struct player_list {
  struct channel * channels;
  guint32 size;
};

struct player_list * decode_player_list(void * data);
void print_player_list(struct player_list * pll);

#endif
