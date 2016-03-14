/* myqueue.h - firstid, firstkey, isempty, lastkey, nonempty		*/

/* Queue structure declarations, constants, and inline functions	*/

/* Default # of queue entries: 1 per process plus 2 for ready list plus	*/
/*			2 for sleep list plus 2 per semaphore		*/
#ifndef NQENT
#define NQENT	(NPROC + 4)
#endif

#define	EMPTY	(-1)		/* Null value for qnext or qprev index	*/
#define	MAXKEY	0x7FFFFFFF	/* Max key that can be stored in queue	*/
#define	MINKEY	0x80000000	/* Min key that can be stored in queue	*/

struct	myqentry	{		/* One per process plus two per list	*/
	int32	qkey;		/* Key on which the queue is ordered	*/
	qid16	qnext;		/* Index of next process or tail	*/
	qid16	qprev;		/* Index of previous process or head	*/
};

extern	struct myqentry	myqueuetab[];

/* Inline queue manipulation functions */

#define	myqueuehead(q)	(q)
#define	myqueuetail(q)	((q) + 1)
#define	myfirstid(q)	(myqueuetab[myqueuehead(q)].qnext)
#define	mylastid(q)	(myqueuetab[myqueuetail(q)].qprev)
#define	myisempty(q)	(myfirstid(q) >= NPROC)
#define	mynonempty(q)	(myfirstid(q) <  NPROC)
#define	myfirstkey(q)	(myqueuetab[myfirstid(q)].qkey)
#define	mylastkey(q)	(myqueuetab[mylastid(q)].qkey)

/* Inline to check queue id assumes interrupts are disabled */

#define	myisbadqid(x)	(((int32)(x) < 0) || (int32)(x) >= NQENT-1)
