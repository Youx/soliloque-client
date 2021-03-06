#ifndef __CHANNEL_LIST_H__
#define __CHANNEL_LIST_H__

#include "compat.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



#define CODEC_CELP_5_1	  0
#define CODEC_CELP_6_3	  1
#define CODEC_GSM_14_8	  2
#define CODEC_GSM_16_4	  3
#define CODEC_CELPWin_5_2 4
#define CODEC_SPEEX_3_4	  5
#define CODEC_SPEEX_5_2	  6
#define CODEC_SPEEX_7_2	  7
#define CODEC_SPEEX_9_3	  8
#define CODEC_SPEEX_12_3  9
#define CODEC_SPEEX_16_3  10
#define CODEC_SPEEX_19_6  11
#define CODEC_SPEEX_25_9  12



#define CHANNEL_FLAG_REGISTERED	  0
#define CHANNEL_FLAG_UNREGISTERED 1
#define CHANNEL_FLAG_MODERATED	  2
#define CHANNEL_FLAG_PASSWORD	  4
#define CHANNEL_FLAG_SUBCHANNELS  8
#define CHANNEL_FLAG_DEFAULT	  16


struct channel {
  uint32_t id;
  uint16_t flags;
  uint16_t codec;
  uint16_t sort_order;
  uint16_t max_users;
  char * name;
  char * topic;
  char * desc;
};

struct channel_list {
  struct channel * channels;
  uint32_t size;
};

struct channel_list * decode_channel_list(void * data);
void print_channel_list(struct channel_list * chl);
#endif
