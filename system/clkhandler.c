/* clkhandler.c - clkhandler */

#include <xinu.h>

/*
 * define constant for max for clktimemsec counter
 */
const uint32 MAX_UINT32 = 0xFFFFFFFF;
/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	// increment the clktimemsec since it has
	clktimemsec++;

	// LAB 4Q3 : The xcpu time being decremented on each clock interrupt that a process also found itself
	// to be the current process.
	struct procent *prptr = &proctab[currpid];
	if (prptr->xcpufunc!= NULL) {
			prptr->xcputime--;
			//kprintf(" XCPU pid %d, xcputime %d", currpid, prptr->xcputime);
			if (prptr->xcputime == 0) {
				void (*xcpuFunction) () = prptr->xcpufunc;
				prptr->xcputime = 0;
				xcpuFunction();
				prptr->xcpufunc = NULL;
		}
	}
	// wrap-around clktimemsec if it has reached its maximum;
	if(clktimemsec == MAX_UINT32)
		clktimemsec = 0;
	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}

	/* LAB 4Q3: Handle alarmq processes if any exist */

	if(!alarmisempty(alarmq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--alarmqueuetab[alarmfirstid(alarmq)].qkey) <= 0) {
			alarmwakeup();
		}
	}
	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
}
