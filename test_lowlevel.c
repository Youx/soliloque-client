#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <sys/uio.h>
#include <unistd.h>


/*
void check_structs() {
	printf("Starting check of structures size\n");
	if(sizeof(struct message1) == 180)
		printf("struct message1 : OK\n");
	else
		printf("struct message1 : ERROR (size = %li)\n", sizeof(struct message1));
		
	if(sizeof(struct message1a) == 436)
		printf("struct message1a : OK\n");
	else
		printf("struct message1a : ERROR (size = %li)\n", sizeof(struct message1a));
		
		
	if(sizeof(struct message2) == 112)
		printf("struct message2 : OK\n");
	else
		printf("struct message2 : ERROR (size = %li)\n", sizeof(struct message2));
		
		
	if(sizeof(struct keepalive) == 16)
		printf("struct keepalive : OK\n");
	else
		printf("struct keepalive : ERROR (size = %li)\n", sizeof(struct keepalive));
		
	if(sizeof(struct chanlist) == 555)
		printf("struct keepalive : OK\n");
	else
		printf("struct keepalive : ERROR (size = %li)\n", sizeof(struct chanlist));
}
*/













void dump(void * str, int len, char * filename) {
  int fd = open(filename, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
  write(fd, str, len); 
  close(fd);
}


