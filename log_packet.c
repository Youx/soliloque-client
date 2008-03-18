#include <time.h>
#include <fcntl.h>
#include <unistd.h>


void log_packet(char * data, int size) {
  time_t t;
  char * filename;
  int fd;
  t = time(0);
  filename = ctime(&t);
  fd = open(filename, O_RDWR | O_CREAT);
  write(fd, data, size);
  close(fd);
}
