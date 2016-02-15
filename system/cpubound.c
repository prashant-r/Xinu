/*
 * cpubound.c
 *
 *  Created on: Feb 13, 2016
 *      Author: prashantravi
 */
/* cpubound.c - cpubound */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  cpubound - simulates a CPU hogging process
 *------------------------------------------------------------------------
 */
void cpubound(uint32 LOOP1, uint32 LOOP2)
{
	int i;
	int j;
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	prptr = &proctab[(getpid())];
	for (i=0; i<LOOP1; i++) {
	  for (j=0; j<LOOP2; j++) {
	    // Insert code that performs memory copy (slow) and/or
	    // ALU operations (fast).
	    // Note: this loop consumes significant CPU cycles.

		  // fast operations
		  int e = 10000;
		  int e2 = e * e ;

		  // slow operations
		  char src[200];
		  char dest[200];
		  memset(dest, '\0', sizeof(dest));
		  strcpy(src, "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod ur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
		  strcpy(dest, src);
	  }
	  // Using kprintf print the pid followed the outer loop count i,
	  // the process's priority and remaining time slice (preempt).
	  kprintf("\n In %s |The PID is %d | outer loop %d | process priority is %d | preempt is %d \n",prptr->prname, currpid, i, getprio(currpid), preempt);
	}
	// Print the CPU time consumed by the process that is recorded in the
	// prcpumsec field of the current process's process table entry.
	kprintf("\The CPU time occupied by %s| PID :%d  is %d",prptr->prname, currpid, prptr->prcpumsec );
}
