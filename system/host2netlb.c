/* host2netlb.c - host2netlb */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  host2netlb  -  prints the big endian format of the argument provided
 *------------------------------------------------------------------------
 */
long host2netlb(long x)
{
	int y;
	asm ("movl %1, %%eax;bswap %%eax;movl %%eax, %0;"
			:"=r"(y)	/* y is output operand */
			:"r"(x)		/* x is input operand */
			:"%eax");	/* %eax is clobbered register */;
	return y;
}
