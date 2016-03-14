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
	msg = prptr->prmsg;		/* Retrieve message		*/
	prptr->prhasmsg = FALSE;	/* Reset message flag		*/

	kprintf("testing the senderq\n");
	kprintf(" Is the senderq empty %d", isempty(prptr->senderq));
	kprintf("testing done \n");
	/* Choose next process to unblock */
	if(!isempty(prptr->senderq))
	{
		pid32 processChosen = mydequeue(prptr->senderq);
		struct procent * prchosenptr = &proctab[processChosen];
		while(!prchosenptr->sndflag){

			processChosen  = mydequeue(prptr->senderq);
			prchosenptr = &proctab[processChosen];
		}
		kprintf(" process chosen %d ", processChosen);
		unsleep(prchosenptr);
		ready(prchosenptr);
	}
	restore(mask);
	return msg;
}
