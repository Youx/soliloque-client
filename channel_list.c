#include "channel_list.h"


char codecs[13][12] = {
  "CELP 5.1",
  "CELP 6.3",
  "GSM 14.8",
  "GSM 16.4",
  "CELPWin 5.2",
  "Speex 3.4",
  "Speex 5.2",
  "Speex 7.2",
  "Speex 9.3",
  "Speex 12.3",
  "Speex 16.3",
  "Speex 19.6",
  "Speex 25.9"
};

static void print_channel(struct channel * ch) {
  printf("  id: %i\n", ch->id);
  printf("    name: %s\n", ch->name);
  printf("    flags: ");
  if(ch->flags & CHANNEL_FLAG_UNREGISTERED)
    printf("U");
  else
    printf("R");

  if(ch->flags & CHANNEL_FLAG_MODERATED)
    printf("M");
  if(ch->flags & CHANNEL_FLAG_PASSWORD)
    printf("P");
  if(ch->flags & CHANNEL_FLAG_SUBCHANNELS)
    printf("S");
  if(ch->flags & CHANNEL_FLAG_DEFAULT)
    printf("D");
  printf("\n");

  printf("    codec: %s\n", codecs[ch->codec]);
  printf("    max users : %i\n", ch->max_users);
  printf("    topic: %s\n", ch->topic);
  printf("    desc: %s\n", ch->desc);
}

void print_channel_list(struct channel_list * chl) {
  int i;

  printf("Channel list : (%i channels)\n", chl->size);
  for(i = 0 ; i<chl->size ; i++) {
    print_channel(& (chl->channels[i]));
  }
}

static void destroy_channel(struct channel * ch) {
  free(ch->name);
  free(ch->topic);
  free(ch->desc);
  free(ch);
}

void destroy_channel_list(struct channel_list * ch) {
  int i;
  for(i=0 ; i < ch->size ; i++) {
    destroy_channel(& ch->channels[i]);
  }
  free(ch);
}

void * decode_channel(void * data, struct channel * ch) {
  void * ptr = data;
  int len;

  ch->id = GUINT32_FROM_LE(* (uint32_t *)ptr);
  ptr = (uint32_t *)ptr +1;

  ch->flags = GUINT16_FROM_LE(* (uint16_t *)ptr);
  ptr = (uint16_t *)ptr +1;

  ch->codec = GUINT16_FROM_LE(* (uint16_t *)ptr);
  ptr = (uint16_t *)ptr +1;
  ptr = (uint32_t *)ptr +1; /* jump over ffffffff */
  ch->sort_order = GUINT16_FROM_LE(* (uint16_t *)ptr);
  ptr = (uint16_t *)ptr +1;
  ch->max_users = GUINT16_FROM_LE(* (uint16_t *)ptr);
  ptr = (uint16_t *)ptr +1;
  
  len = strlen((char *)ptr);
  ch->name = (char *)calloc(len+1, 1);
  strcpy(ch->name, ptr);
  ptr = (char *)ptr + len+1;

  len = strlen((char *)ptr);
  ch->topic = (char *)calloc(len+1, 1);
  strcpy(ch->topic, ptr);
  ptr = (char *)ptr + len+1;

  len = strlen((char *)ptr);
  ch->desc = (char *)calloc(len+1, 1);
  strcpy(ch->desc, ptr);
  ptr = (char *)ptr + len+1;

  return ptr;
}


struct channel_list * decode_channel_list(void * data) {
  void * ptr = data;
  struct channel_list * chl;
  int i;

  chl = (struct channel_list *)calloc(sizeof(struct channel_list), 1);

  /* skip the header */
  ptr = (uint32_t *) ptr + 6;

  chl->size = GUINT32_FROM_LE(* ((uint32_t *) ptr));
  ptr = (uint32_t *) ptr +1;
  
  chl->channels = calloc(sizeof(struct channel), chl->size);

  for(i=0 ; i < chl->size ; i++) {
    ptr = decode_channel(ptr, chl->channels+i);
  }

/*  print_channel_list(chl);*/
  return chl;
}
