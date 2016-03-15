/*
 * iobound.c
 *
 *  Created on: Feb 13, 2016
 *      Author: prashantravi
 */
/* iobound.c - iobound */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  iobound - simulates a IO hogging process
 *------------------------------------------------------------------------
 */
void iobound(uint32 LOOP1, uint32 LOOP2)
{
	int i;
	int j;
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	prptr = &proctab[(getpid())];
	for (i=0; i<LOOP1; i++) {
	  for (j=0; j<LOOP2; j++) {

		  sleepms(28);

	  }
	  // Using kprintf print the pid followed the outer loop count i,
	  // the process's priority and remaining time slice (preempt).
	  kprintf("\n In %s |The PID is %d | outer loop %d | process priority is %d | preempt is %d \n",prptr->prname, currpid, i, getprio(currpid), preempt);
	}
	// Print the CPU time consumed by the process that is recorded in the
	// prcpumsec field of the current process's process table entry.
	kprintf("\The CPU time occupied by %s| PID :%d  is %d",prptr->prname, currpid, prptr->prcpumsec );
}
