#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int usr_cnode_fops(void){
	int fd;
	char *test_node0 = "/dev/chr_node0";
	char *test_node1 = "/dev/chr_node1";
		
	if((fd = open(test_node0,O_RDWR|O_NDELAY))<0){
		printf("APP open %s failed\n",test_node0);
	}
	else{
		printf("app: APP open %s success!\n", test_node0);

	}
	close(fd);

	if((fd = open(test_node1,O_RDWR|O_NDELAY))<0){
		printf("APP open %s failed\n",test_node1);
	}
	else{
		printf("app: APP open %s success!\n", test_node1);
	}
	close(fd);	
	return 0;
	
}


