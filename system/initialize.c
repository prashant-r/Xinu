/* initialize.c - nulluser, sysinit, sizmem */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/


/*
 * Definition of constant - Max of int32 type
 */
const int32 MAX_INT32 = 0x7FFFFFFF;
/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
extern	void xdone(void);	/* System "shutdown" procedure		*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/

/* ts queue array */
qid16 queueArr[INITSIZE];


/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/

/* Active system status */

int	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/

/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */

void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/
	/* Initialize the system */

	sysinit();

	kprintf("\n\r%s\n\n\r", VERSION);

	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
			memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
		kprintf("           [0x%08X to 0x%08X]\r\n",
				(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of Xinu code.\n",
			(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
			(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
			(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
			(uint32)&data, (uint32)&ebss - 1);




	/*
	 * Print the welcome message
	 */

	resume(create(mywelcomemsg,1024,49,"welcome",0,NULL));

	/* Enable interrupts */

	enable();


	/* Create a process to execute function main() */

	resume (
			create((void *)main, INITSTK, INITPRIO, "Main process", 0,
					NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/
	idle();

}

/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */
static	void	sysinit()
{
	int32	i;
	struct	procent	*prptr;		/* Ptr to process table entry	*/
	struct	sentry	*semptr;	/* Ptr to semaphore table entry	*/

	/* Platform Specific Initialization */

	platinit();

	/* Initialize the interrupt vectors */

	initevec();

	/* Initialize free memory list */

	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
		prptr->prcpumsec = MAX_UINT32;
	}

	/* Initialize the Null process entry */	

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	if(lab2flag == 4 || lab2flag == 5)
		prptr->prcpumsec = MAX_INT32;
	else
		prptr->prcpumsec = 0;
	prptr->prctxswintime = 0;
	currpid = NULLPROC;

	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}


	/* Initialize buffer pools */

	bufinit();

	/* Create a ready list for processes */

	readylist = newqueue();

	/* Initialize the real time clock */


	/* Display the dispatch table */
	int row = 0;
	kprintf("--------------------------Dispatch Table Looks Like------------------------------\n");
	for(row = 0;row < 20;row++){
		kprintf("Level no. %d is| tqexp is %d | slpret is %d | quantum is %d \n",row, tsdtab[row].ts_tqexp,tsdtab[row].ts_slpret,tsdtab[row].ts_quantum);//printed out table
	}

	// Initialize the queue array structure that maintains the queue at each level
	for (row =0 ; row <20; row++)
		queueArr[row] = newqueue();
	clkinit();
	for (i = 0; i < NDEVS; i++) {
		init(i);
	}


	return;
}

int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
