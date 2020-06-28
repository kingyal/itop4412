#include <stdio.h>

/*对值进行偶检验*/
int even_parity(int value, int n_bits)
{
	int parity = 0;

	while(n_bits > 0) {
		parity += value & 1;
		value>>1;
		n_bits--;
	}

	return (parity%2) == 0;
}

























