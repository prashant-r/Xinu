/* myappA.c - myappA */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  myappA  -  myappA calls another function called myfuncA()
 *------------------------------------------------------------------------
 */
process myappA()
{
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	prptr = &proctab[(getppid())];
	kprintf("\Process main's pid is %d | Name is %s | ESP is 0x%x | EBP is 0x%x | State is %d |", getppid(), getpname(getppid()), prptr->prstkptr, prptr->prstkbase, prptr->prstate);
	unsigned long *topsp, *topbp;

	asm ("movl %%esp, %0;movl %%ebp, %1;"
						:"=r"(topsp)	/* y is output operand */
						,"=r"(topbp));
	kprintf("\n 3.|In func: myappA| PID is %d | ESP is 0x%x , its content is 0x%x and EBP is 0x%x \n",currpid,  topsp, *topsp, topbp);
	myfuncA(64);
	asm ("movl %%esp, %0;movl %%ebp, %1;"
							:"=r"(topsp)	/* y is output operand */
							,"=r"(topbp));
	kprintf("\n 5.|In func: myappA| PID is %d |  ESP is 0x%x , its content is 0x%x and EBP is 0x%x \n",currpid, topsp, *topsp, topbp);
	return OK;
}
