/* alarmwakeup.c - alarmwakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  alarmwakeup  -  Called by clock interrupt handler to awaken processes to call alarm handler
 *------------------------------------------------------------------------
 */
void	alarmwakeup(void)
{
	/* LAB 4Q3 Awaken all processes that have no more time to sleep */
	resched_cntl(DEFER_START);
	while (alarmnonempty(alarmq) && (alarmfirstkey(alarmq) <= 0)) {
		pid32 timeoutProcess = alarmdequeue(alarmq);
		//  LAB 4Q3 If current process then just invoke the callback function
		if (timeoutProcess == currpid) {

			struct procent *prptr = &proctab[currpid];
			void (*alarmFunction) () = prptr->alarmfunc;
			prptr->alarmtime = 0;
			prptr->alarmTimeOut = FALSE;
			alarmFunction();
			prptr->alarmfunc = NULL;

		} else {

			//  LAB 4Q3 if not the current process then ready the process frocibly in order to run the
			// alarm callback function context switch in.
			struct procent *prptr = &proctab[timeoutProcess];
			prptr->alarmTimeOut = TRUE;
			if (prptr->prstate == PR_SLEEP) {
				unsleep(timeoutProcess);
				ready(timeoutProcess);
			}
		}
	}

	resched_cntl(DEFER_STOP);
	return;
}
