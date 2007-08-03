#include "crc.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <speex/speex.h>


#define FRAME_SIZE 8000

void decode(int header) {
  FILE * fin = fopen("audiopacket2.spx", "r");
  FILE * fout = fopen("decoded_audio.raw", "w");
  int i;
  short out[FRAME_SIZE];
  float output[FRAME_SIZE];
  char cbits[331-20];
  int nbBytes;

  SpeexBits bits;
  void * state;
  
  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);

  while(1) {
    if(feof(fin))
      break;

    /* on lit 307 octets (un paquet) vers cbits */
    fread(cbits, 1, 331-20, fin);
    /* on le copie vers une structure bit-stream */
    speex_bits_read_from(&bits, cbits+header, 331-20-header);
    /* on decode */
    speex_decode(state, &bits, output);

    for(i=0 ; i< FRAME_SIZE ; i++)
      out[i]= output[i];

    fwrite(out, sizeof(short), FRAME_SIZE, fout);
  }
}

int main(int argc, char ** argv){
  decode(atoi(argv[1]));
  return 0;
}
