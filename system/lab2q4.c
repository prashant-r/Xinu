/*
 * lab2q4.c
 *
 *  Created on: Feb 13, 2016
 *      Author: prashantravi
 */
/* lab2q4.c - lab2q4 */
#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  lab2q4t1 - tests with 6 cpubound processes of same loop1 and loop2 values
 *  			Intermittently prints process state.
 *
 *------------------------------------------------------------------------
 */
void lab2q4t1()
{

		pid32 a,b,c,d,e,f;
		kprintf("\n -------------------------");
		kprintf("\n In lab2q4t1 test | Note: 6 cpubound processes spawned by main process");
		kprintf("\n -------------------------\n");
		resume(a= create(cpubound, 1024, 1, "cpubound 1", 2, 1, 75500));
		resume(b =create(cpubound, 1024, 1, "cpubound 2", 2, 1, 75500));
		resume(c = create(cpubound, 1024, 1, "cpubound 3", 2, 1, 75500));
		resume(d = create(cpubound, 1024, 1, "cpubound 4", 2, 1, 75500));
		resume(e = create(cpubound, 1024, 1, "cpubound 5", 2, 1, 75500));
		resume(f = create(cpubound, 1024, 1, "cpubound 6", 2, 1, 75500));
		struct procent * prptr;
		int counter = 0;
		while(!(prptr = &proctab[a])->prstate == PR_FREE ||!(prptr = &proctab[b])->prstate == PR_FREE ||
		!(prptr = &proctab[c])->prstate == PR_FREE || !(prptr = &proctab[e])->prstate == PR_FREE || !(prptr = &proctab[d])->prstate == PR_FREE || !(prptr = &proctab[f])->prstate == PR_FREE)
		{
				if(counter++ >2000000){
						counter =0;
						process_state();
					}
		}

}
/*------------------------------------------------------------------------
 *  lab2q4t2 - tests with 6 iobound processes of varying loop1 and loop2 values
 *  		   Intermittently prints process state.
 *
 *------------------------------------------------------------------------
 */
void lab2q4t2()
{
		pid32 a,b,c,d,e,f;
		kprintf("\n -------------------------");
		kprintf("\n In lab2q4t2 test | Note: 6 iobound processes spawned by main process");
		kprintf("\n -------------------------\n");
		resume(a = create(iobound, 1024, 1, "iobound 1", 2, 10, 20));
		resume(b = create(iobound, 1024, 1, "iobound 2", 2, 20, 30));
		resume(c = create(iobound, 1024, 1, "iobound 3", 2, 30, 20));
		resume(d = create(iobound, 1024, 1, "iobound 4", 2, 30, 10));
		resume(e = create(iobound, 1024, 1, "iobound 5", 2, 40, 30));
		resume(f = create(iobound, 1024, 1, "iobound 6", 2, 20, 10));
		struct procent * prptr;
		int counter = 0;
			while(!(prptr = &proctab[a])->prstate == PR_FREE ||!(prptr = &proctab[b])->prstate == PR_FREE ||
		!(prptr = &proctab[c])->prstate == PR_FREE || !(prptr = &proctab[e])->prstate == PR_FREE || !(prptr = &proctab[d])->prstate == PR_FREE || !(prptr = &proctab[f])->prstate == PR_FREE)
			{
					if(counter++ >21474830){
							counter =0;
							process_state();
						}
			}
}

/*------------------------------------------------------------------------
 *  lab2q4t3 - tests with 3 iobound processes of varying loop1 and loop2 values
 *  		   along with 3 cpubound processes.
 *  		   Intermittently prints process state.
 *
 *------------------------------------------------------------------------
 */
void lab2q4t3()
{
		pid32 a,b,c,d,e,f;
		kprintf("\n -------------------------");
		kprintf("\n In lab2q4t3 test | Note: 3 cpubound processes and 3 iobound processes spawned by main process");
		kprintf("\n -------------------------\n");
		resume(a= create(iobound, 1024, 1, "iobound 4", 2, 20, 10));
		resume(b =create(iobound, 1024, 1, "iobound 5", 2, 10, 15));
		resume(c =create(iobound, 1024, 1, "iobound 6", 2, 20, 10));
		resume(d =create(cpubound, 1024, 1, "cpubound 4", 2, 1, 75500));
		resume(e =create(cpubound, 1024, 1, "cpubound 5", 2, 1, 75500));
		resume(f =create(cpubound, 1024, 1, "cpubound 6", 2, 1, 75500));
		struct procent * prptr;
		int counter = 0;
		while(!(prptr = &proctab[a])->prstate == PR_FREE ||!(prptr = &proctab[b])->prstate == PR_FREE ||
		!(prptr = &proctab[c])->prstate == PR_FREE || !(prptr = &proctab[e])->prstate == PR_FREE || !(prptr = &proctab[d])->prstate == PR_FREE || !(prptr = &proctab[f])->prstate == PR_FREE)
		{
			if(counter++ >21474830){
					counter =0;
					process_state();
			}
		}
}
/*------------------------------------------------------------------------
 *  lab2q4t4 - tests if all the processes share the cpu if the priorities are the same.
 *------------------------------------------------------------------------
 */
void lab2q4t4()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q4t3 test | Note: 4 (workerProcessTypeA) equal CPU usage seen by  monitorProcess");
		kprintf("\n (Monitor process will have higher priority than workerProcessTypeA) ");
		kprintf("\n -------------------------\n");
		pid32 wp1 = create(workerProcessTypeA, 1024, 54, "Worker Proc1", 0, NULL);
		pid32 wp2 = create(workerProcessTypeA, 1024, 54, "Worker Proc2", 0, NULL);
		pid32 wp3 = create(workerProcessTypeA, 1024, 54, "Worker Proc3", 0, NULL);
		pid32 wp4 = create(workerProcessTypeA, 1024, 54, "Worker Proc4", 0, NULL);
		resume(create(monitorProcess, 1024, 57, "Monitor Proc", 5, wp1,wp2,wp3,wp4,245));
		return;
}
/*------------------------------------------------------------------------
 *  lab2q4t5 - tests if a process that sleeps often, in other word, iobound,  gets equal time share as ones that don't and are classified as cpubound.
 *------------------------------------------------------------------------
 */
void lab2q4t5()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q4t4 test | Note: 3 (workerProcessTypeA) and 1 sleeper workerProcessTypeB");
		kprintf("\n (Monitor process will have higher priority than workerProcessTypeA/B) ");
		kprintf("\n -------------------------\n");
		pid32 wp1 = create(workerProcessTypeA, 1024, 54, "Worker Proc1", 0, NULL);
		pid32 wp2 = create(workerProcessTypeA, 1024, 54, "Worker Proc2", 0, NULL);
		pid32 wp3 = create(workerProcessTypeA, 1024, 54, "Worker Proc3", 0, NULL);
		pid32 wp4 = create(workerProcessTypeB, 1024, 54, "Worker Proc4", 0, NULL);
		resume(create(monitorProcess, 1024, 57, "Monitor Proc", 5, wp1,wp2,wp3,wp4,375));
		return;
}
/*------------------------------------------------------------------------
 *  lab2q4t6 - tests if higher priority process hogs the cpu over the lower priority ones.
 *
 *------------------------------------------------------------------------
 */
void lab2q4t6()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q4t5 test | Note: 3 (workerProcessTypeA) and 1 higher priority workerProcessTypeA");
		kprintf("\n (Monitor process will have higher priority than workerProcessTypeA) ");
		kprintf("\n -------------------------\n");
		pid32 wp1 = create(workerProcessTypeA, 1024, 54, "Worker Proc1", 0, NULL);
		pid32 wp2 = create(workerProcessTypeA, 1024, 54, "Worker Proc2", 0, NULL);
		pid32 wp3 = create(workerProcessTypeA, 1024, 54, "Worker Proc3", 0, NULL);
		pid32 wp4 = create(workerProcessTypeA, 1024, 55, "Worker Proc4", 0, NULL);
		resume(create(monitorProcess, 1024, 57, "Monitor Proc", 5, wp1,wp2,wp3,wp4,375));
		return;
}
