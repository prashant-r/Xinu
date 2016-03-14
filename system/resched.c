/* resched.c - resched, resched_cntl, reward_ready_waiting */

#include <xinu.h>

struct	defer	Defer;
/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{
	if(lab == 2)
	{
		resched_lab2();
	}
	else if (lab == 3)
	{
		resched_lab3();
	}
	else
	{
		resched_lab1();
	}
}
/* ------------------------------------------------------------------------
 * resched_lab3 -  Multi-feedback queue will now be the default scheduler going forward
 *				   This is the scheduler from lab3 that achieves constant time dequeue
 *				   since the size of the levels in the dispatch table is a fixed number
 *-------------------------------------------------------------------------
 */
void resched_lab3(void)
{
	uint32 currTime = clktimemsec;
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */
	uint32 addToTotalTime =0;
	/* Point to process table entry for the current (old) process */
	ptold = &proctab[currpid];
	//Update the total processing time for context switched out process
	// Handle the case where the counter overflows then get the absolute value of difference
	addToTotalTime = (currTime)-(ptold->prctxswintime);


	ptold->prcpumsec = ptold->prcpumsec +  addToTotalTime;

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {

		// update the priority based on TS dispatch table values for active process's time quantum expiration scenario

		if(currpid != 0)
			ptold->prprio = tsdtab[ptold->prprio].ts_tqexp;

		// cpu- intensive process
		if(currproc_eligible()) // check eligibility of current process to get another quantum
			{
				ptold->prctxswintime = currTime;
				return;
			}
		else
		{
			// current process will be switched out
			// enqueu at correct location for when next time it may be selected
			// by scheduler it will be at correct level on multi-level feedback queue.
			ptold->prstate = PR_READY;
			enqueue(currpid, queueArr[ptold->prprio]);
		}

	}
	else if (ptold->prstate == PR_SLEEP)
	{
		// io- intensive process

		// update the priority based on TS dispatch table values for sleep return
		if(currpid != 0)
			ptold->prprio = tsdtab[ptold->prprio].ts_slpret;

	}

	/* Force context switch to highest priority ready process */

	currpid = multifeedbackDQ();
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	ptnew->prctxswintime = currTime;
	preempt = tsdtab[ptnew->prprio].ts_quantum;		/* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}
/*--------------------------------------------------------------
 * currproc_eligible -  checks if the current process is still eligible
 * 						for another time quantum or if it's time for a new process to
 * 						be elected
 *--------------------------------------------------------------
 */

bool8 currproc_eligible()
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	ptold = &proctab[currpid];
	int highestLevel;
	for (highestLevel = 19; highestLevel>=0; highestLevel --)
	{
		if(!isempty(queueArr[highestLevel]))
		{
			if(ptold->prprio> highestLevel)
				return TRUE;
			else
				return FALSE;
		}
	}
	return FALSE;
}

/*------------------------------------------------------------------------
 *  resched_lab2  -  fair scheduler from lab2, need to set lab2flag according to specs
 *  				 given in lab2 documentation on 503 course website.
 *------------------------------------------------------------------------
 */
void resched_lab2(void)
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

	// totest switches the key for the readylist queue to be tested based on the lab we are running.
	// For the lab3, its the priority of the process
	// and for lab 4 and 5 it's the prcpumsec, the cpu time given to the process
	int32 totest = ptold->prprio;


	// Here the totest will be set to the negation of prcpumsec
	// because we wan't to maintain using the insert function that
	// inserts elements in decreasing order. By this negation of prcpumsec would
	// cause the element with the least prcpumsec to be the first to be dequeud at the head.
	// Hence, we are followin the rules of the dynamic priority scheduling algorithm
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
			// The only other place an insert happens is at the ready method
			// even there we have chosen to implement a similar strategy of choosing the value
			// of key based on the lab that we are dealing with. That is, either to insert
			// based on priority or the negation of the prcpumsec spent.
			insert(currpid, readylist, totest);
			currpid = dequeue(readylist);
		}
	else
	{
		//even if the process is in sleep state and calling a reschedule
		// we must reward the other processes
		// of course, as soon as the process that is dequeued is removed its key value
		// would also
		if(lab2flag ==5)
			reward_ready_waiting();
		currpid = dequeue(readylist);
	}
	/* Force context switch to highest priority ready process */
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	//Update the context switch-in time for new process
	ptnew->prctxswintime = currTime;
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);
	/* Old process returns here when resumed */
	return;

}


/*------------------------------------------------------------------------
 *  resched_lab1  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched_lab1(void)		/* Assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* Reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}


/*------------------------------------------------------------------------
 *  reward_ready_waiting  -  this method promotes all the processes on the readylist by giving them each an
 *  						 increment of 6ms to their keys. We do this so that a process that has been waiting for a long time
 *  						 would at least get a chance to execute if it had executed the cpu for a long time.
 *							 All processes in this ready list are processes that were not selected in this run of resched
 *							 as the next process to execute, despite being ready. Hence, this loss of opportunity is
 *							 defined as waiting in our context.
 *
 *------------------------------------------------------------------------
 */
void reward_ready_waiting()
{
	qid16	curr;			/* Runs through items in a queue*/
	qid16	prev;			/* Holds previous node index	*/

	struct procent * prptr;
	curr = firstid(readylist);
	while (curr != queuetail(readylist)) {
			prptr = &proctab[curr];
			// don't promote prnull process
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
