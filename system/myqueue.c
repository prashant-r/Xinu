/* queue.c - enqueue, dequeue */

#include <xinu.h>

struct myqentry	myqueuetab[NQENT];	/* Table of process queues	*/

/*------------------------------------------------------------------------
 *  myenqueue  -  Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
pid32	myenqueue(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q		/* ID of queue to use		*/
	)
{
	int	tail, prev;		/* Tail & previous node indexes	*/

	if (myisbadqid(q) || isbadpid(pid)) {
		if(myisbadqid(q))
			kprintf("BAD QID \n");
		if(isbadpid(pid))
			kprintf("BAD PID \n");
		return SYSERR;
	}

	tail = myqueuetail(q);
	prev = myqueuetab[tail].qprev;

	myqueuetab[pid].qnext  = tail;	/* Insert just before tail node	*/
	myqueuetab[pid].qprev  = prev;
	myqueuetab[prev].qnext = pid;
	myqueuetab[tail].qprev = pid;
	return pid;
}


/*------------------------------------------------------------------------
 *  mydequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	mydequeue(
	  qid16		q		/* ID queue to use		*/
	)
{
	pid32	pid;			/* ID of process removed	*/

	if (myisbadqid(q)) {
		return SYSERR;
	} else if (myisempty(q)) {
		return EMPTY;
	}

	pid = mygetfirst(q);
	myqueuetab[pid].qprev = EMPTY;
	myqueuetab[pid].qnext = EMPTY;
	return pid;
}


/* ----------------------------------------------------------
 * myprintQueue - prints the contents of the queue
 *----------------------------------------------------------
 */
pid32 myprintQueue(qid16 q)
{
	if (myisbadqid(q)) {
			return SYSERR;
		} else if (myisempty(q)) {
			return EMPTY;
		}
	qid16	curr = myqueuehead(q);
	int counter = 0;
	while (curr != myqueuetail(q)) {
			if(curr!=myqueuehead(q))
				kprintf("Element number %d is %d \n ",counter ++, curr);
			curr = myqueuetab[curr].qnext;
		}
	return OK;
}

