#include "cfs/cfs.h"
#include "contiki.h"
#include <stdio.h>

PROCESS(coffee_test_process, "coffee test process");
AUTOSTART_PROCESSES(&coffee_test_process);
PROCESS_THREAD(coffee_test_process, ev, data){
	PROCESS_BEGIN();
	char message[32];
	char buf[100];
	strcpy(message, "#1. Hello world");
	strcpy(buf, message);
	printf("step 1: %s\n", buf);
	char *filename = "msg_file";
	int fd_write, fd_read, n;
	fd_write = cfs_open(filename, CFS_WRITE);
	if(fd_write != -1){
		n = cfs_write(fd_write, message, sizeof(message));
		cfs_close(fd_write);
		printf("Write %i bytes successful!\n", n);
	}else{
		printf("Write fail\n");
	}
	strcpy(buf, "empty string");
	fd_read = cfs_open(filename, CFS_READ);
	if(fd_read != -1){
		cfs_read(fd_read, buf, sizeof(message));
		printf("Reading successful:\n%s\n", buf);
		cfs_close(fd_read);
	}else{
		printf("Read fail\n");
	}
	PROCESS_END();
}

