#include "decoder.h"
#include "celp/celp.h"
#include "gsm/gsm.h"
#include "sound.h"
#include "ringbuffer.h"

#define FRAME_SIZE 160

extern ringbuffer_t * speakers;

char outfiles2[5][11] = {
  "data/2out0",
  "data/2out1",
  "data/2out2",
  "data/2out3",
  "data/2out4"
};

char outfiles[5][10] = {
  "data/out0",
  "data/out1",
  "data/out2",
  "data/out3",
  "data/out4"
};


static int16_t * decode_speex(void * input, uint8_t nbframes, int datasize) {
  int16_t * out = (int16_t *)calloc(FRAME_SIZE * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  SpeexBits bits;
  void * state;
  int i;

  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);
  
  speex_bits_read_from(&bits, (char *)input, datasize*nbframes/8);

  for(i=0 ; i<nbframes ; i++) {
    speex_decode_int(state, &bits, outptr);
    outptr += FRAME_SIZE;
  }

  speex_decoder_destroy(state);
  speex_bits_destroy(&bits);

  return out;
}


static int16_t * decode_gsm(void * input, int nbframes) {
  int16_t * out = (int16_t *)calloc(FRAME_SIZE * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  unsigned char * ptr = (unsigned char *)input;
  int i;
  gsm handle;

  ptr+=6;

  handle = gsm_create();
  for(i=0 ; i<nbframes ; i++) {
    if(gsm_decode(handle, ptr, outptr)) {
      printf("GSM ERROR...\n");
    }

    ptr+=33;
    outptr += FRAME_SIZE;
  }

  gsm_destroy(handle);

  return out;
}

static int16_t * decode_celp(void * input, int nbframes) {
  int16_t * out = (int16_t *)calloc(240 * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  unsigned char * ptr = (unsigned char *)input;
  int i;
  celp_decoder_state * state;

  ptr+=6;

  state = create_celp_decoder_state();
  init_celp_decoder_state(state, CELP_4_5_FRAMESIZE);

  for(i=0 ; i<nbframes ; i++) {
    celp_decode(ptr, outptr, state);

    ptr+=17;
    outptr += 240;
  }

  destroy_celp_decoder_state(state);

  return out;
}


void decode_audio_packet(void * input) {
  uint8_t nbframes;
  int16_t * out;
  char * ptr = (char *)input;
  uint8_t codec;
	int i;
	
	
  ptr+=3;
  codec = *ptr;
  ptr+=19;
  nbframes = *ptr; 
  ptr++;

/*  printf(">>>> CODEC : 0x%x\n", *((char *)(&codec)));*/
  switch(codec) {
    case CODEC_SPEEX_25_9:
      out = decode_speex(ptr, nbframes, 492);
      break;
    case CODEC_SPEEX_19_6:
      out = decode_speex(ptr, nbframes, 364);
      break;
    case CODEC_SPEEX_16_3:
      out = decode_speex(ptr, nbframes, 300);
      break;
    case CODEC_SPEEX_12_3:
      out = decode_speex(ptr, nbframes, 220);
      break;
    case CODEC_SPEEX_9_3:
      out = decode_speex(ptr, nbframes, 160);
      break;
    case CODEC_SPEEX_7_2:
      out = decode_speex(ptr, nbframes, 119);
      break;
    case CODEC_SPEEX_5_2:
      out = decode_speex(ptr, nbframes, 79);
      break;
    case CODEC_SPEEX_3_4:
      out = decode_speex(ptr, nbframes, 43);
      break;
    case CODEC_GSM_14_8:
      nbframes = 5;
      out = decode_gsm(ptr,nbframes);
      break;
    case CODEC_GSM_16_4:
      nbframes = 3;
      out = decode_gsm(ptr,nbframes);
      break;
    case CODEC_CELP_6_3:
      nbframes = 3;
      out = decode_celp(ptr, nbframes);
      break;
    case CODEC_CELP_5_1:
      nbframes = 9;
      out = decode_celp(ptr, nbframes);
      break;
    default:
      nbframes = 0;
      out = NULL;
  }
  //append(out, sizeof(short) * FRAME_SIZE * nbframes, "data/decoded_audio.raw");
	//printf("Network to ringbuffer, nbframes = %i\n", nbframes);
	for(i=0;i<nbframes;i++) {
		//while(!
		ringbuffer_write(speakers, out+(FRAME_SIZE * i));
		//audio_to_speakers(out+(FRAME_SIZE*i), FRAME_SIZE);
		//);
	}
  free(out);
}
