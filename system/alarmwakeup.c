/* alarmwakeup.c - alarmwakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  alarmwakeup  -  Called by clock interrupt handler to awaken processes to call alarm handler
 *------------------------------------------------------------------------
 */
void	alarmwakeup(void)
{
	/* Awaken all processes that have no more time to sleep */
	resched_cntl(DEFER_START);
	while (alarmnonempty(alarmq) && (alarmfirstkey(alarmq) <= 0)) {
		pid32 timeoutProcess = alarmdequeue(alarmq);
		if (timeoutProcess == currpid) {

			struct procent *prptr = &proctab[currpid];
			void (*alarmFunction) () = prptr->alarmfunc;
			prptr->alarmtime = 0;
			prptr->alarmTimeOut = FALSE;
			alarmFunction();
			prptr->alarmfunc = NULL;

		} else {
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
