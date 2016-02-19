/* process_state.c - process_state */

#include <xinu.h>
#include <stdio.h>
#include <string.h>
/*------------------------------------------------------------------------
 *  process_state  -  prints the process state just like shell command ps
 *------------------------------------------------------------------------
 */
void process_state()
{
struct	procent	*prptr;		/* pointer to process		*/
	int32	i;			/* index into proctabl		*/
	char *pstate[]	= {		/* names for process states	*/
		"free ", "curr ", "ready", "recv ", "sleep", "susp ",
		"wait ", "rtime"};

	/* Print header for items from the process table */

	kprintf("%3s %-16s %5s %4s %4s %10s %-10s %10s %6s %11s %8s\n",
		   "Pid", "Name", "State", "Prio", "Ppid", "Stack Base",
		   "Stack Ptr", "Stack Size", "CPU time", "ReadyQ Posn", "ReadyQ Key");

	kprintf("%3s %-16s %5s %4s %4s %10s %-10s %10s %10s %12s %8s\n",
		   "---", "----------------", "-----", "----", "----",
		   "----------", "----------", "----------", "----------", "------------","------------");

	/* Output information for each process */

	int32 readyListPosition[NPROC]= {[0 ... NPROC-1] = -1};
	int32 readyListKey[NPROC]= {[0 ... NPROC-1] = MAX_INT32};
	qid16	curr;			/* Runs through items in a queue*/
	qid16	prev;			/* Holds previous node index	*/

	curr = firstid(readylist);
	int counter =0;
	while (curr != queuetail(readylist)) {
		prptr = &proctab[curr];
		readyListPosition[curr] = counter++;
		readyListKey[curr] = queuetab[curr].qkey;
		curr = queuetab[curr].qnext;
	}

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		if (prptr->prstate == PR_FREE) {  /* skip unused slots	*/
			continue;
		}
		kprintf("%3d %-16s %s %4d %4d 0x%08X 0x%08X %8d %8d",
			i, prptr->prname, pstate[(int)prptr->prstate],
			prptr->prprio, prptr->prparent, prptr->prstkbase,
			prptr->prstkptr, prptr->prstklen, prptr->prcpumsec);
		if(readyListPosition[i] ==-1)
			kprintf("\n");
		else
			kprintf("%12d  %8d\n", readyListPosition[i], readyListKey[i]);

	}
	return 0;
}
