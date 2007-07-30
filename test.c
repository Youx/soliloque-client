#include "crc.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <speex/speex.h>


#define FRAME_SIZE 500



int main(){
  FILE * fin = fopen("audiopacket2.spx", "r");
  FILE * fout = fopen("decoded_audio.raw", "w");
  int i;
  short out[FRAME_SIZE];
  float output[FRAME_SIZE];
  char cbits[331-24];
  int nbBytes;

  SpeexBits bits;
  void * state;
  
  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);

  while(1) {
    if(feof(fin))
      break;

    /* on lit 307 octets (un paquet) vers cbits */
    fread(cbits, 1, 331-24, fin);
    /* on le copie vers une structure bit-stream */
    speex_bits_read_from(&bits, cbits, 331-24);
    /* on decode */
    speex_decode(state, &bits, output);

    for(i=0 ; i< FRAME_SIZE ; i++)
      out[i]= output[i];

    fwrite(out, sizeof(short), FRAME_SIZE, fout);
  }

  return 0;
}
