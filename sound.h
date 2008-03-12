#ifndef __SOUND_H__
#define __SOUND_H__

#include "compat.h"

#ifdef __cpluspluc
extern "C" {
#endif

void audio_init();
int audio_to_speakers(int16_t * data, int size);
void audio_close();

#ifdef __cpluspluc
}
#endif


#endif
