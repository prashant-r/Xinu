/* alarmqueue.h - firstid, firstkey, isempty, lastkey, nonempty		*/

/* Queue structure declarations, constants, and inline functions	*/

/* Default # of queue entries: 1 per process plus 2 for ready list plus	*/
/*			2 for sleep list plus 2 per semaphore		*/
#ifndef alarmNQENT
#define alarmNQENT	(3* NPROC)
#endif

#define	EMPTY	(-1)		/* Null value for qnext or qprev index	*/
#define	MAXKEY	0x7FFFFFFF	/* Max key that can be stored in queue	*/
#define	MINKEY	0x80000000	/* Min key that can be stored in queue	*/

struct	alarmqentry	{		/* One per process plus two per list	*/
	int32	qkey;		/* Key on which the queue is ordered	*/
	qid16	qnext;		/* Index of next process or tail	*/
	qid16	qprev;		/* Index of previous process or head	*/
};

extern	struct alarmqentry	alarmqueuetab[];

/* Inline queue manipulation functions */

#define	alarmqueuehead(q)	(q)
#define	alarmqueuetail(q)	((q) + 1)
#define	alarmfirstid(q)	(alarmqueuetab[alarmqueuehead(q)].qnext)
#define	alarmlastid(q)	(alarmqueuetab[alarmqueuetail(q)].qprev)
#define	alarmisempty(q)	(alarmfirstid(q) >= NPROC)
#define	alarmnonempty(q)	(alarmfirstid(q) <  NPROC)
#define	alarmfirstkey(q)	(alarmqueuetab[alarmfirstid(q)].qkey)
#define	alarmlastkey(q)	(alarmqueuetab[alarmlastid(q)].qkey)

/* Inline to check queue id assumes interrupts are disabled */

#define	alarmisbadqid(x)	(((int32)(x) < 0) || (int32)(x) >= alarmNQENT-1)
