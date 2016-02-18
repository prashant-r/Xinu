/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;
/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	uint32 currTime = clktimemsec;
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/
	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}


	uint32 addToTotalTime =0;
	/* Point to process table entry for the current (old) process */
	ptold = &proctab[currpid];
	//Update the total processing time for context switched out process
	// Handle the case where the counter overflows then get the absolute value of difference
	addToTotalTime = (currTime)-(ptold->prctxswintime);

	// if the old process id is not of null user then update its total CPU time
	// else ignore this step because prcpumsec of null user is already set to max to
	// force it to only execute if no other process is ready
	if(currpid != 0)
		ptold->prcpumsec = ptold->prcpumsec +  addToTotalTime;
	int32 totest = ptold->prprio;

	if(lab2flag == 4 || lab2flag == 5)
		totest =-(int32)ptold->prcpumsec;

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (totest > firstkey(readylist)) {
				ptold->prctxswintime = currTime;
				if(lab2flag ==5)
					reward_ready_waiting();
				return;
			}

			/* Old process will no longer remain current */
			if(lab2flag == 5)
				reward_ready_waiting();
			ptold->prstate = PR_READY;
			insert(currpid, readylist, totest);
			currpid = dequeue(readylist);
		}
	else
	{
		if(lab2flag ==5)
			reward_ready_waiting();
		currpid = dequeue(readylist);
	}
	/* Force context switch to highest priority ready process */
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	//Update the context switch in time for new process
	ptnew->prctxswintime = currTime;
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
	/* Old process returns here when resumed */
	return;
}

void reward_ready_waiting()
{
	qid16	curr;			/* Runs through items in a queue*/
	qid16	prev;			/* Holds previous node index	*/

	struct procent * prptr;
	curr = firstid(readylist);
	while (curr != queuetail(readylist)) {
			prptr = &proctab[curr];
			if(curr!=0)
				queuetab[curr].qkey +=6;
			curr = queuetab[curr].qnext;
		}
}



/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}
