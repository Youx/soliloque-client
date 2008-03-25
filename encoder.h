#ifndef __ENCODER_H__
#define __ENCODER_H__


#include <speex/speex.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "compat.h"
#include "toolbox.h"
#include "channel_list.h"

#include <stdlib.h>

//void * encode_audio_packet(int16_t * input);
char encode_speex(int16_t * input_frame, uint8_t nbframes, char * output);
void send_audio(int32_t public_id, int32_t private_id, int32_t counter, char * data, char data_size, int s, const struct sockaddr * to);

#endif
