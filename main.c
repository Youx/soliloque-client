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

extern "C" int main2() {
  int sockfd;
  struct sockaddr_in servaddr;

  struct connection_request connectme = {
    "Machine Youx",
    "",
    "sllm",
    "Client test!",
    0
  };

	audio_init();
  connect_to(&connectme, &sockfd, &servaddr);
  receive(sockfd, &servaddr);
  return 0;
}

