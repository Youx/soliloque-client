#include "decoder.h"

#define FRAME_SIZE 160

char outfiles[5][14] = {
  "data/out1.dat",
  "data/out2.dat", 
  "data/out3.dat",
  "data/out4.dat",
  "data/out5.dat"
};

void odd_frame_to_even(unsigned char * frame, int len) {
  int i;

  for(i=0 ; i < len ; i++) {
    frame[i] = frame[i] << 4;
    frame[i] |= (frame[i+1] >> 4);
  }
}


void decode_audio_packet(void * input) {
  char * ptr = input;
  short out[FRAME_SIZE];
  float output[FRAME_SIZE];

  uint8_t nbframes;

  SpeexBits bits;
  void * state;
  int j, i;

  /* bypass header */
  ptr+=22;
  nbframes = *ptr; 
  ptr++;

  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);
  
  for(i=0 ; i<nbframes ; i++) {
    if(i%2 == 1)
      odd_frame_to_even((unsigned char *)ptr, 62);

    dump(ptr, 62, outfiles[i]);
    speex_bits_read_from(&bits, ptr, 62);
    speex_decode(state, &bits, output);

    for(j=0 ; j < FRAME_SIZE ; j++)
      out[j] = output[j];

    append(out, sizeof(short) * FRAME_SIZE, "data/decoded_audio.raw");

    if(i%2 == 1)
      ptr+=1;

    ptr+=61;
  }
}

