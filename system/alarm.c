/* alarm.c - alarm alarmms */

#include <xinu.h>

#define	MAXSECONDS	4294967		/* Max seconds per 32-bit msec	*/

/*------------------------------------------------------------------------
 *  alarm  -  LAB 4Q3 Delay the calling process's callback function invocation n seconds
 *------------------------------------------------------------------------
 */
syscall	alarm(
	  uint32	delay		/* Time to delay in seconds	*/
	)
{
	if (delay > MAXSECONDS) {
		return SYSERR;
	}
	alarmms(1000*delay);
	return OK;
}

/*------------------------------------------------------------------------
 *  alarmms  - LAB 4Q3 Delay the calling process's callback function invocation by n milliseconds
 *------------------------------------------------------------------------
 */
syscall	alarmms(
	  uint32	delay		/* Time to delay in msec.	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	kprintf(" Alarm for process %d started at %d \n", currpid, clktimemsec);
	struct procent *prptr = &proctab[currpid];
	mask = disable();
	// LAB 4Q3: Check if the call back function has been registered else
	// return SYSERR
	if(prptr->alarmfunc == NULL)
	{
		restore(mask);
		return SYSERR;
	}
	// If thee delay sepecified was 0 then just execute the callback function immediatly without
	// inserting into the alarmq
	if (delay == 0) {
		struct procent *prptr = &proctab[currpid];
		void (*alarmFunction) () = prptr->alarmfunc;
		prptr->alarmfunc = NULL;
		// unnecessary to set the following really do it anyway
		prptr->alarmtime = 0;
		prptr->alarmTimeOut = FALSE;
		alarmFunction();
		restore(mask);
		return OK;
	}
	// First remove the process from the queue if it already exists
	alarmgetitem(currpid);
	// Reinsert if process was already on queue or just plain insert if not.
	if (alarminsertd(currpid, alarmq, delay) == SYSERR) {
		restore(mask);
		return SYSERR;
	}
	restore(mask);
	return OK;
}
