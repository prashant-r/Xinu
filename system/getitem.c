/* getitem.c - getfirst, getlast, getitem */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getfirst  -  Remove a process from the front of a queue
 *------------------------------------------------------------------------
 */
pid32	getfirst(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32	head;

	if (isempty(q)) {
		return EMPTY;
	}

	head = queuehead(q);
	return getitem(queuetab[head].qnext);
}

/*------------------------------------------------------------------------
 *  getlast  -  Remove a process from end of queue
 *------------------------------------------------------------------------
 */
pid32	getlast(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32 tail;

	if (isempty(q)) {
		return EMPTY;
	}

	tail = queuetail(q);
	return getitem(queuetab[tail].qprev);
}

/*------------------------------------------------------------------------
 *  getitem  -  Remove a process from an arbitrary point in a queue
 *------------------------------------------------------------------------
 */
pid32	getitem(
	  pid32		pid		/* ID of process to remove	*/
	)
{
	pid32	prev, next;

	next = queuetab[pid].qnext;	/* Following node in list	*/
	prev = queuetab[pid].qprev;	/* Previous node in list	*/
	queuetab[prev].qnext = next;
	queuetab[next].qprev = prev;
	return pid;
}

/*------------------------------------------------------------------------
 *  mygetfirst  -  Remove a process from the front of a myqueue
 *------------------------------------------------------------------------
 */
pid32	mygetfirst(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32	head;

	if (myisempty(q)) {
		return EMPTY;
	}

	head = myqueuehead(q);
	return mygetitem(myqueuetab[head].qnext);
}

/*------------------------------------------------------------------------
 *  mygetlast  -  Remove a process from end of myqueue
 *------------------------------------------------------------------------
 */
pid32	mygetlast(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32 tail;

	if (myisempty(q)) {
		return EMPTY;
	}

	tail = myqueuetail(q);
	return mygetitem(myqueuetab[tail].qprev);
}

/*------------------------------------------------------------------------
 *  mygetitem  -  Remove a process from an arbitrary point in a myqueue
 *------------------------------------------------------------------------
 */
pid32	mygetitem(
	  pid32		pid		/* ID of process to remove	*/
	)
{
	pid32	prev, next;

	next = myqueuetab[pid].qnext;	/* Following node in list	*/
	prev = myqueuetab[pid].qprev;	/* Previous node in list	*/
	myqueuetab[prev].qnext = next;
	myqueuetab[next].qprev = prev;
	return pid;
}







