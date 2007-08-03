#include "decoder.h"

#define FRAME_SIZE 160


void decode_audio_packet(void * input) {
  uint8_t * ptr = input;
  short out[FRAME_SIZE];
  float output[FRAME_SIZE];

  uint8_t codec, size;

  SpeexBits bits;
  void * state;
  int j;

  /* bypass header */
  ptr+=22;
  codec = *ptr; /* 05 */
  ptr++;
  size = *ptr; /* size of frame */
/*  ptr++;
  ptr+=15; */

  size = 62;
  printf("Encoded frame : %i bytes\n", size);
  dump(input, 331, "data/input_packet.dat");
  dump(ptr, size, "data/input_speexframe.dat");

  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);
  
  /* PART I */
  speex_bits_read_from(&bits, (char *)ptr, size);
  speex_decode(state, &bits, output);

  for(j=0 ; j < FRAME_SIZE ; j++)
    out[j] = output[j];

  append(out, sizeof(short) * FRAME_SIZE, "data/decoded_audio.raw");

  /* PART II */
  ptr = input + 0x8C;
  speex_bits_read_from(&bits, (char *)ptr, size);
  speex_decode(state, &bits, output);

  for(j=0 ; j < FRAME_SIZE ; j++)
    out[j] = output[j];

  append(out, sizeof(short) * FRAME_SIZE, "data/decoded_audio.raw");

  /* PART III */
/*  ptr = input + 0x107;
  speex_bits_read_from(&bits, (char *)ptr, size);
  speex_decode(state, &bits, output);

  for(j=0 ; j < FRAME_SIZE ; j++)
    out[j] = output[j];

  append(out, sizeof(short) * FRAME_SIZE, "data/decoded_audio.raw");*/
}

