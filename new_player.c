#include "new_player.h"


struct player * decode_new_player(void * data) {
  char * ptr = data;
  struct player * pl = (struct player *)calloc(sizeof(struct player), 1);

  ptr += 24;
  printf("New player arrived : \n");
  decode_player(ptr, pl);
  print_player(pl);

  return pl;
}
