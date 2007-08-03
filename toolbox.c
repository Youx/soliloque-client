#include "toolbox.h"


void dump(void * str, int len, char * filename) {
  int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  write(fd, str, len);
  close(fd);
}

void append(void * str, int len, char * filename) {
  int fd = open(filename, O_APPEND|O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  write(fd, str, len);
  close(fd);
}
