/* myfuncA.c - myfuncA */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  myfuncA  -  myfuncA is called by myAppA
 *------------------------------------------------------------------------
 */
char myfuncA(int a)
{
	unsigned long * topsp, * topbp;
	char c;
	c = (char) a;
	asm ("movl %%esp, %0;movl %%ebp, %1;"
						:"=r"(topsp)	/* y is output operand */
						,"=r"(topbp));
	kprintf("\n 4.|In func: myfuncA| PID is %d | ESP is 0x%x , its content is 0x%x and EBP is 0x%x \n",currpid, topsp, *topsp, topbp);
	return c;
}
