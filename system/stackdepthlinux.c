/* stackdepthlinux.c - stackdepthlinux */
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <execinfo.h>
/*------------------------------------------------------------------------
 *  stackdepthlinux  -  returns the depth of the runtime stack in LINUX(!XINU) in the case of nested function cals
 * USAGE INSTRUCTIONS: type gcc -m32 stackdepthlinux.c followed by ./a.out in LINUX shell
 *------------------------------------------------------------------------
 */

int main()
{
	printf("\n Factorial of 9 is %d \n", factorial(9));

	// Expected stack depth is 10.
}
/*------------------------------------------------------------------------
 *  factorial  -  is a recursive function to compute the factorial of the argument
 *------------------------------------------------------------------------
 */
int factorial(int a)
{
		if(a == 1)
			return 1;
		else
		{
			stackdepth();
			return a*factorial(a-1);
		}
}

/*------------------------------------------------------------------------
 *  stackdepth  -  finds the depth of the curr function executing wrt to the base process, in Linux systems
 *
 * Changes needed to be made w.r.t Unix version :
 * 1. processBase which is the base address of process would need to be set to (0x0/NULL).
 * 2. uint32 not defined.
 *------------------------------------------------------------------------
 */
int stackdepth()
{
		unsigned long *topsp, *topbp;
		asm ("movl %%esp, %0;movl %%ebp, %1;"
					:"=r"(topsp)	// y is output operand
					,"=r"(topbp));
		unsigned long * processBase = 0x0;
		int depth = 0;

		printf("\n ---------------------------------- \n");
		while(topbp!=processBase){
			//printf("%10d bytes is size of stack frame at depth %d.\n",
			//		(uint32_t)topbp - (uint32_t)topsp, depth);
			printf("\n 0x%x ebp at depth %d ", topbp, depth );
			printf("\n ");
			topsp = topbp;
			topbp = *topbp;
			++depth;
		}
		if(depth > 0)
				depth = depth -1;
		return depth;
}
