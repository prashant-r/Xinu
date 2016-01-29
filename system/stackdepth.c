/* stackdepth.c - stackdepth */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  stackdepth  -  returns the depth of the runtime stack in the case of nested function cals
 *------------------------------------------------------------------------
 */
int stackdepth()
{
		unsigned long *topsp, *topbp;
		asm ("movl %%esp, %0;movl %%ebp, %1;"
					:"=r"(topsp)	/* y is output operand */
					,"=r"(topbp));
		struct	procent *prptr;		/* Ptr to process' table entry	*/
		prptr = &proctab[(getpid())];
		unsigned long * processBase = (unsigned long *) prptr->prstkbase;
		int depth = 0;

		kprintf("\n ---------------------------------- \n");
		while(topbp!=processBase){
			kprintf("%10d bytes is size of stack frame at depth %d.\n",
					(uint32)topbp - (uint32)topsp, depth);
			kprintf("\n 0x%x ebp at depth %d ", topbp, depth );
			kprintf("\n ");
			topsp = topbp;
			topbp = *topbp;
			++depth;
		}
		kprintf("\n ---------------------------------- \n");
		return depth;
}
