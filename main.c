#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "compat.h"
#include "sound.h"
#include "highlevel.h"
#include "connection_request.h"
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>


int sockfd;
struct sockaddr_in * pservaddr;
sem_t * sem_microphone;
void * encode_thread(void * args);

#ifdef __cplusplus
extern "C" {
#endif
int main2() {
  struct sockaddr_in servaddr;
	pthread_t encoder;
	sem_t micro;
  int err;

  struct connection_request connectme = {
    "Machine Youx",
    "",
    "sllm",
    "Client test!",
    0
  };

  audio_init();

  err = sem_unlink("microphone");
  if(err != 0) {
    printf(strerror(errno));
    //exit(0);
  }

  sem_microphone = sem_open("microphone", O_CREAT | O_EXCL, S_IRWXU, 0);

  if(sem_microphone == SEM_FAILED) {
    printf(strerror(errno));
    exit(0);
  }
	pthread_create(&encoder, NULL, encode_thread, NULL);

  connect_to(&connectme, &sockfd, &servaddr);
  pservaddr = &servaddr;
  //printf("main : sockfd == %i\n", sockfd);
  receive(sockfd, &servaddr);

	return 0;
}

#ifdef __cplusplus
}
#endif
