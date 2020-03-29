#include <stdio.h>
#include "common.h"

int main()
{
	int a = 3, b = 4, c = 5, d= 6, e = 7;
	
	HI_LOG_FATAL("a = %d", a);

	HI_LOG_ERROR("b = %d", b);

	HI_LOG_WARN("c = %d", c);

	HI_LOG_INFO("d = %d", d);

	HI_LOG_DEBUG("e = %d", e);

	return 0;
}











