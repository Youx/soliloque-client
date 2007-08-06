#include "decoder.h"
#include "celp/celp.h"

#define FRAME_SIZE 160

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

void evenize_frame(unsigned char * frame, int framenb, int bitlen) {
  int i;

  /* if we are on an oddly aligned frame */
  if( (bitlen*framenb) % 8) {
    /* shift each byte 4 bits left */
    for(i=0 ; i < bitlen/8 ; i++) {
      frame[i] = frame[i] << 4;
      frame[i] |= (frame[i+1] >> 4);
    }
  }
}

void evenize_speex_26_4(unsigned char * frame) {
  int i;
  for(i=0 ; i < 492/8 ; i++) {
    frame[i] = frame[i] << 4;
    frame[i] |= (frame[i+1] >> 4);
  }
}

void evenize_speex_18_2(unsigned char * frame) {
  int i;
  for(i=0 ; i < 364/8 ; i++) {
    frame[i] = frame[i] << 4;
    frame[i] |= (frame[i+1] >> 4);
  }
}

static int16_t * decode_speex_18_2(void * input, uint8_t nbframes) {
  int16_t * out = (int16_t *)calloc(FRAME_SIZE * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  char * ptr = input;
  SpeexBits bits;
  void * state;
  int i;

  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);
  
  for(i=0 ; i<nbframes ; i++) {
    if(i%2 == 1) {
      ptr --;
      evenize_speex_18_2((unsigned char *)ptr);
    }

    speex_bits_read_from(&bits, ptr, 364/8);
    speex_decode_int(state, &bits, outptr);

    ptr+=46;
    outptr += FRAME_SIZE;
  }

  speex_decoder_destroy(state);
  speex_bits_destroy(&bits);

  return out;
}

static int16_t * decode_speex_26_4(void * input, uint8_t nbframes) {
  int16_t * out = (int16_t *)calloc(FRAME_SIZE * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  char * ptr = input;
  SpeexBits bits;
  void * state;
  int i;

  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);
  
  speex_bits_read_from(&bits, ptr, 492/8*5);

  for(i=0 ; i<nbframes ; i++) {
    /*if(i%2 == 1) {
      ptr --;
      evenize_speex_26_4((unsigned char *)ptr);
    }*/

    /* speex_bits_read_from(&bits, ptr, 492/8); */
    speex_decode_int(state, &bits, outptr);

    /* ptr+=62; */
    outptr += FRAME_SIZE;
  }

  speex_decoder_destroy(state);
  speex_bits_destroy(&bits);

  return out;
}

static int16_t * decode_junk(void * input, uint8_t nbframes) {
  return (int16_t *)calloc(sizeof(uint16_t), FRAME_SIZE * nbframes);
}



void evenize_speex_15(unsigned char * frame) {
  int i;
  for(i=0 ; i < 300/8 ; i++) {
    frame[i] = frame[i] << 4;
    frame[i] |= (frame[i+1] >> 4);
  }
}

static int16_t * decode_speex_15(void * input, uint8_t nbframes) {
  int16_t * out = (int16_t *)calloc(FRAME_SIZE * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  char * ptr = input;
  SpeexBits bits;
  void * state;
  int i;

  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);
  
  for(i=0 ; i<nbframes ; i++) {
    if(i%2 == 1) {
      ptr --;
      evenize_speex_15((unsigned char *)ptr);
    }

    speex_bits_read_from(&bits, ptr, 300/8);
    speex_decode_int(state, &bits, outptr);

    ptr+=38;
    outptr += FRAME_SIZE;
  }

  speex_decoder_destroy(state);
  speex_bits_destroy(&bits);

  return out;
}

void evenize_speex_11(unsigned char * frame) {
  int i;
  for(i=0 ; i < 220/8 ; i++) {
    frame[i] = frame[i] << 4;
    frame[i] |= (frame[i+1] >> 4);
  }
}

static int16_t * decode_speex_11(void * input, uint8_t nbframes) {
  int16_t * out = (int16_t *)calloc(FRAME_SIZE * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  char * ptr = input;
  SpeexBits bits;
  void * state;
  int i;

  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);
  
  for(i=0 ; i<nbframes ; i++) {
    if(i%2 == 1) {
      ptr --;
      evenize_speex_11((unsigned char *)ptr);
    }

    speex_bits_read_from(&bits, ptr, 220/8);
    speex_decode_int(state, &bits, outptr);

    ptr+=28;
    outptr += FRAME_SIZE;
  }

  speex_decoder_destroy(state);
  speex_bits_destroy(&bits);

  return out;
}


static int16_t * decode_speex_8(void * input, uint8_t nbframes) {
  int16_t * out = (int16_t *)calloc(FRAME_SIZE * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  char * ptr = input;
  SpeexBits bits;
  void * state;
  int i;

  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);
  
  for(i=0 ; i<nbframes ; i++) {
    speex_bits_read_from(&bits, ptr, 160/8);
    speex_decode_int(state, &bits, outptr);

    ptr+=20;
    outptr += FRAME_SIZE;
  }

  speex_decoder_destroy(state);
  speex_bits_destroy(&bits);

  return out;
}

void evenize_speex_5_950(unsigned char * frame, int nb) {
  int i;
  for(i=0 ; i < 119/8 ; i++) {
    frame[i] = frame[i] << ((8-nb)%8);
    frame[i] |= (frame[i+1] >> ((nb)%8));
  }
}
/* FIXME!!!!! */
static int16_t * decode_speex_5_950(void * input, uint8_t nbframes) {
  int16_t * out = (int16_t *)calloc(FRAME_SIZE * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  char * ptr = input;
  SpeexBits bits;
  void * state;
  int i;

  state = speex_decoder_init(&speex_nb_mode);
  speex_bits_init(&bits);
  
  for(i=0 ; i<nbframes ; i++) {
    dump(ptr, 15, outfiles[i]);
    if(i!=0)
      evenize_speex_5_950((unsigned char *)ptr, i);
    
    dump(ptr, 15, outfiles2[i]);
    speex_bits_read_from(&bits, ptr, 14);
    speex_decode_int(state, &bits, outptr);

    ptr+=14;
    outptr += FRAME_SIZE;
  }

  speex_decoder_destroy(state);
  speex_bits_destroy(&bits);

  return out;
}

static int16_t * decode_gsm(void * input, int nbframes) {
  int16_t * out = (int16_t *)calloc(FRAME_SIZE * nbframes, sizeof(int16_t));
  int16_t * outptr = out;
  unsigned char * ptr = input;
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
  unsigned char * ptr = input;
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
  char * ptr = input;
  uint8_t codec;
  
  ptr+=3;
  codec = *ptr;
  ptr+=19;
  nbframes = *ptr; 
  ptr++;

/*  printf(">>>> CODEC : 0x%x\n", *((char *)(&codec)));*/
  switch(codec) {
    case CODEC_SPEEX_25_9:
      out = decode_speex_26_4(ptr, nbframes);
      break;
    case CODEC_SPEEX_19_6:
      out = decode_speex_18_2(ptr, nbframes);
      break;
    case CODEC_SPEEX_16_3:
      out = decode_speex_15(ptr, nbframes);
      break;
    case CODEC_SPEEX_12_3:
      out = decode_speex_11(ptr, nbframes);
      break;
    case CODEC_SPEEX_9_3:
      out = decode_speex_8(ptr, nbframes);
      break;
    case CODEC_SPEEX_7_2:
      out = decode_speex_5_950(ptr, nbframes);
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
      out = decode_junk(ptr, nbframes);
  }
  append(out, sizeof(short) * FRAME_SIZE * nbframes, "data/decoded_audio.raw");
  free(out);
}
