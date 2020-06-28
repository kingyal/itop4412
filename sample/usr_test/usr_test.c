#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int usr_test(void){
	int fd;
	char *test_node = "/dev/test_ky";
	
/*O_RDWR???¨¢¡ä¨°?a,O_NDELAY¡¤?¡Á¨¨¨¨?¡¤?¨º?*/	
	if((fd = open(test_node,O_RDWR|O_NDELAY))<0){
		printf("APP open %s failed",test_node);
	}
	else{
		printf("app: APP open %s success!\n", test_node);

		ioctl(fd ,1 ,1);
		sleep(3);
		ioctl(fd ,0 ,1);
		sleep(3);
		ioctl(fd ,1 ,1);
	}
	close(fd);
	
	return 0;
	
}


