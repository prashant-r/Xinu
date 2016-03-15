/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receivebt  -  Wait for a message and return the message to the caller
 *  			  maintain a sender queue FIFO order attention given to
 *  			  queued sender processes.
 *------------------------------------------------------------------------
 */
umsg32	receivebt(void)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	umsg32	msg;			/* Message to return		*/
	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}

	/* Choose next process to unblock */
	if(!myisempty(prptr->senderq))
	{
		pid32 processChosen = mydequeue(prptr->senderq);
		struct procent * prchosenptr = &proctab[processChosen];
		while(!prchosenptr->sndflag){

			processChosen  = mydequeue(prptr->senderq);
			prchosenptr = &proctab[processChosen];
		}
		// ensure that chosen process has a valid message
		if(prchosenptr->sndflag){
			unsleep(prchosenptr);
			prptr->prhasmsg = FALSE;	/* Reset message flag		*/
			ready(prchosenptr);
		}
	}
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/
	restore(mask);
	return msg;
}
