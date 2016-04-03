/* alarm.c - alarm alarmms */

#include <xinu.h>

#define	MAXSECONDS	4294967		/* Max seconds per 32-bit msec	*/

/*------------------------------------------------------------------------
 *  alarm  -  Delay the calling process n seconds
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
 *  alarmms  -  Delay the calling process n milliseconds
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
	if(prptr->alarmfunc == NULL)
	{
		restore(mask);
		return SYSERR;
	}

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
	alarmgetitem(currpid);
	if (alarminsertd(currpid, alarmq, delay) == SYSERR) {
		restore(mask);
		return SYSERR;
	}
	restore(mask);
	return OK;
}
