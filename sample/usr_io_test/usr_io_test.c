#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int usr_led(void){
	int fd;
	char *hello_node = "/dev/hello_ky";
	
/*O_RDWR???���䨰?a,O_NDELAY��?������?��?��?*/	
	if((fd = open(hello_node,O_RDWR|O_NDELAY))<0){
		printf("APP open %s failed",hello_node);
	}
	else{
		printf("app: APP open %s success!\n", hello_node);

		ioctl(fd ,1 ,1);
		sleep(3);
		ioctl(fd ,0 ,1);
		sleep(3);
		ioctl(fd ,1 ,1);
	}
	close(fd);
	
	return 0;
	
}


