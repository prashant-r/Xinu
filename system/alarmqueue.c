/* alarmqueue.c - alarmenqueue.c, alarmdequeue.c, alrminsertd.c, alarmgetfirst.c,alarmgetlast.c, alarmgetitem.c, alarmnewqueue.c  */

#include <xinu.h>

struct alarmqentry	alarmqueuetab[alarmNQENT];	/* Table of process queues	*/

/*------------------------------------------------------------------------
 *  alarmenqueue  -  Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
pid32	alarmenqueue(
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q		/* ID of queue to use		*/
	)
{
	int	tail, prev;		/* Tail & previous node indexes	*/

	if (alarmisbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	tail = alarmqueuetail(q);
	prev = alarmqueuetab[tail].qprev;

	alarmqueuetab[pid].qnext  = tail;	/* Insert just before tail node	*/
	alarmqueuetab[pid].qprev  = prev;
	alarmqueuetab[prev].qnext = pid;
	alarmqueuetab[tail].qprev = pid;
	return pid;
}

/*------------------------------------------------------------------------
 *  alarmdequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32	alarmdequeue(
	  qid16		q		/* ID queue to use		*/
	)
{
	pid32	pid;			/* ID of process removed	*/

	if (alarmisbadqid(q)) {
		return SYSERR;
	} else if (alarmisempty(q)) {
		return EMPTY;
	}

	pid = alarmgetfirst(q);
	alarmqueuetab[pid].qprev = EMPTY;
	alarmqueuetab[pid].qnext = EMPTY;
	return pid;
}


/*------------------------------------------------------------------------
 *  alarminsertd  -  Insert a process in delta list using delay as the key
 *------------------------------------------------------------------------
 */
status	alarminsertd(			/* Assumes interrupts disabled	*/
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Delay from "now" (in ms.)	*/
	)
{
	int32	next;			/* Runs through the delta list	*/
	int32	prev;			/* Follows next through the list*/

	if (alarmisbadqid(q) || isbadpid(pid)) {
		return SYSERR;
	}

	prev = alarmqueuehead(q);
	next = alarmqueuetab[alarmqueuehead(q)].qnext;
	while ((next != alarmqueuetail(q)) && (alarmqueuetab[next].qkey <= key)) {
		key -= alarmqueuetab[next].qkey;
		prev = next;
		next = alarmqueuetab[next].qnext;
	}

	/* Insert new node between prev and next nodes */

	alarmqueuetab[pid].qnext = next;
	alarmqueuetab[pid].qprev = prev;
	alarmqueuetab[pid].qkey = key;
	alarmqueuetab[prev].qnext = pid;
	alarmqueuetab[next].qprev = pid;
	if (next != alarmqueuetail(q)) {
		alarmqueuetab[next].qkey -= key;
	}

	return OK;
}



/*------------------------------------------------------------------------
 *  alarmgetfirst  -  Remove a process from the front of a queue
 *------------------------------------------------------------------------
 */
pid32	alarmgetfirst(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32	head;

	if (alarmisempty(q)) {
		return EMPTY;
	}

	head = alarmqueuehead(q);
	return alarmgetitem(alarmqueuetab[head].qnext);
}

/*------------------------------------------------------------------------
 *  alarmgetlast  -  Remove a process from end of queue
 *------------------------------------------------------------------------
 */
pid32	alarmgetlast(
	  qid16		q		/* ID of queue from which to	*/
	)				/* Remove a process (assumed	*/
					/*   valid with no check)	*/
{
	pid32 tail;

	if (alarmisempty(q)) {
		return EMPTY;
	}

	tail = alarmqueuetail(q);
	return alarmgetitem(alarmqueuetab[tail].qprev);
}

/*------------------------------------------------------------------------
 *  alarmgetitem  -  Remove a process from an arbitrary point in a queue
 *------------------------------------------------------------------------
 */
pid32	alarmgetitem(
	  pid32		pid		/* ID of process to remove	*/
	)
{
	pid32	prev, next;

	next = alarmqueuetab[pid].qnext;	/* Following node in list	*/
	prev = alarmqueuetab[pid].qprev;	/* Previous node in list	*/
	alarmqueuetab[prev].qnext = next;
	alarmqueuetab[next].qprev = prev;
	return pid;
}


/*------------------------------------------------------------------------
 *  alarmnewqueue  -  Allocate and initialize a queue in the global queue table
 *------------------------------------------------------------------------
 */
qid16	alarmnewqueue(void)
{
	static qid16	nextqid=NPROC;	/* Next list in queuetab to use	*/
	qid16		q;		/* ID of allocated queue 	*/

	q = nextqid;
	if (q > alarmNQENT) {		/* Check for table overflow	*/
		return SYSERR;
	}

	nextqid += 2;			/* Increment index for next call*/

	/* Initialize head and tail nodes to form an empty queue */

	alarmqueuetab[alarmqueuehead(q)].qnext = alarmqueuetail(q);
	alarmqueuetab[alarmqueuehead(q)].qprev = EMPTY;
	alarmqueuetab[alarmqueuehead(q)].qkey  = MAXKEY;
	alarmqueuetab[alarmqueuetail(q)].qnext = EMPTY;
	alarmqueuetab[alarmqueuetail(q)].qprev = alarmqueuehead(q);
	alarmqueuetab[alarmqueuetail(q)].qkey  = MINKEY;
	return q;
}


/* ----------------------------------------------------------
 * alarmprintQueue - prints the contents of the queue
 *----------------------------------------------------------
 */
pid32 alarmprintQueue(qid16 q)
{
	if (alarmisbadqid(q)) {
			return SYSERR;
		} else if (alarmisempty(q)) {
			return EMPTY;
		}
	qid16	curr = alarmqueuehead(q);
	int counter = 0;
	while (curr != alarmqueuetail(q)) {
			if(curr!=alarmqueuehead(q))
				kprintf("Element number %d is %d \n ",counter ++, curr);
			curr = alarmqueuetab[curr].qnext;
		}
	return OK;
}


/* ----------------------------------------------------------
 * alarmcontains - check if the process exists in the queue
 *----------------------------------------------------------
 */
int32 alarmcontains(qid16 q, pid32 pid)
{
	if (alarmisbadqid(q)) {
			return SYSERR;
		} else if (alarmisempty(q)) {
			return EMPTY;
		}
	int32 result = FALSE;
	qid16	curr = alarmqueuehead(q);
	int counter = 0;
	while (curr != alarmqueuetail(q)) {
			if(curr!=alarmqueuehead(q))
				kprintf("Element number %d is %d \n ",counter ++, curr);
			else if(curr == pid)
			{
				result = TRUE;
			}
			curr = alarmqueuetab[curr].qnext;
		}
	return result;
}
