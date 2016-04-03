#include <xinu.h>

syscall registercb(int (* func) (void)){
	intmask	mask;
	mask = disable(); // disable interrupts
	if(func == NULL)
	{
		restore(mask);
		return SYSERR;
	}
	struct	procent *prptr = &proctab[currpid];
	prptr->callback = func; // point to the callback function
	restore(mask); // restore interrupts
	return OK;
}
