/* queue.c - enqueue, dequeue */

#include <xinu.h>

struct qentry	queuetab[NQENT];	/* Table of process queues	*/

/*------------------------------------------------------------------------
 *  enqueue  -  Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
pid32	enqueue(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q		/* ID of queue to use		*/
	)
{
	int	tail, prev;		/* Tail & previous node indexes	*/

	if (isbadqid(q) || isbadpid(pid)) {
		if(isbadqid(q))
			kprintf("BAD QID \n");
		if(isbadpid(pid))
			kprintf("BAD PID \n");
		return SYSERR;
	}

	tail = queuetail(q);
	prev = queuetab[tail].qprev;

	queuetab[pid].qnext  = tail;	/* Insert just before tail node	*/
	queuetab[pid].qprev  = prev;
	queuetab[prev].qnext = pid;
	queuetab[tail].qprev = pid;
	return pid;
}

/*------------------------------------------------------------------------
 *  dequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	dequeue(
	  qid16		q		/* ID queue to use		*/
	)
{
	pid32	pid;			/* ID of process removed	*/

	if (isbadqid(q)) {
		return SYSERR;
	} else if (isempty(q)) {
		return EMPTY;
	}

	pid = getfirst(q);
	queuetab[pid].qprev = EMPTY;
	queuetab[pid].qnext = EMPTY;
	return pid;
}


/* ----------------------------------------------------------
 * printQueue - prints the contents of the queue
 *----------------------------------------------------------
 */
pid32 printQueue(qid16 q)
{
	if (isbadqid(q)) {
			return SYSERR;
		} else if (isempty(q)) {
			return EMPTY;
		}
	qid16	curr = queuehead(q);
	int counter = 0;
	while (curr != queuetail(q)) {
			if(curr!=queuehead(q))
				kprintf("Element number %d is %d \n ",counter ++,queuetab[curr].qkey);
			curr = queuetab[curr].qnext;
		}
	return OK;
}

