#include <stdio.h>
#include "common.h"
#include "usr_led.h"
#include "usr_test.h"
#include "usr_cnode_fops.h"
#include "usr_chr_driver_leds.h"

int main(int argc, char **argv[])
{
	int a = 3, b = 4, c = 5, d= 6, e = 7;
	
	HI_LOG_FATAL("a = %d", a);

	HI_LOG_ERROR("b = %d", b);

	HI_LOG_WARN("c = %d", c);

	HI_LOG_INFO("d = %d", d);

	HI_LOG_DEBUG("e = %d", e);

	//usr_led();

	//usr_test();
	
	//usr_cnode_fops();
	
	//usr_chr_driver_leds();
	
	usr_chr_driver_leds(argc, argv);

	return 0;
}











