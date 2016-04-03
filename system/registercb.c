#include <xinu.h>
/* registercb.c - registercb */
/*------------------------------------------------------------------------
 *  registercb - LAB 4Q2 registers the callback for the wait-on-message arrival type of callback function signal
 *------------------------------------------------------------------------
*/
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
