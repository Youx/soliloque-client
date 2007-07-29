#include <stdio.h>
#include <sys/types.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "compat.h"


void crc32_table(guint32 poly, guint32 * table) {
  int i, j;

  for(i = 0; i < 256; i++) {
    table[i] = i;
    for(j = 8; j > 0; j--) {
      if(table[i] & 1)
        table[i] = (table[i] >> 1) ^ poly;
      else
        table[i] >>= 1;
    }
  }     
}

guint32 crc_32(void * str, int length, guint32 poly) {
  guint32 table[256];
  int i;
  crc32_table(poly, table);
  guint32 crc = 0xFFFFFFFF;

  for(i = 0 ; i < length ; i++) {
    crc = ( crc >> 8) ^ table[(((guint8 *)str)[i] ^ crc) & 0x000000FF];
  }
  return ~crc;
}
