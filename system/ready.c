/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/
/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	// if process is ready then it must have woken up from sleep
	// or have been just resumed. Hence we add it to the ready list based  on
	// the scheduling strategies that we have implemented in this lab
	if(lab == 2){
	if(lab2flag == 4 || lab2flag == 5)
		insert(pid, readylist, -(int32)prptr->prcpumsec);
	else
		insert(pid, readylist, prptr->prprio);
	}
	else if(lab == 3)
	{
		//printMFQ();
		enqueue(pid, queueArr[prptr->prprio]);
	}
	else{
		insert(pid, readylist, prptr->prprio);
	}
	resched();

	return OK;
}
