/*
 * lab2q3.c - lab2q3t1, lab2q3t2, lab2q3t3, lab2q3t4
 *
 *  Created on: Feb 13, 2016
 *      Author: prashantravi
 */
/* lab2q3.c - lab2q3 */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  lab2q3t1 - tests the clk functionality such as printing and validating
 *  		   clktimemsec global variable.
 *------------------------------------------------------------------------
 */
void lab2q3t1()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q3t1 test | Note: sleeping for 5 seconds .. zzzzz ... ");
		kprintf("\n -------------------------");
		sleepms(5000);
		kprintf("\n Clock time in seconds since boot is %d", clktime);
		kprintf("\n Clock time in milliseconds since boot is %d", clktimemsec);
		return;
}
/*------------------------------------------------------------------------
 *  lab2q3t2 - tests if all the processes share the cpu if the priorities are the same.
 *------------------------------------------------------------------------
 */
void lab2q3t2()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q3t2 test | Note: 4 (workerProcessTypeA) equal CPU usage seen by  monitorProcess");
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
 *  lab2q3t3 - tests if a process that sleeps often, in other word, iobound,  gets equal time share as ones that don't and are classified as cpubound.
 *------------------------------------------------------------------------
 */
void lab2q3t3()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q3t3 test | Note: 3 (workerProcessTypeA) and 1 sleeper workerProcessTypeB");
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
 *  lab2q3t4 - tests if higher priority process hogs the cpu over the lower priority ones.
 *
 *
 *------------------------------------------------------------------------
 */
void lab2q3t4()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q3t4 test | Note: 3 (workerProcessTypeA) and 1 higher priority workerProcessTypeA");
		kprintf("\n (Monitor process will have higher priority than workerProcessTypeA) ");
		kprintf("\n -------------------------\n");
		pid32 wp1 = create(workerProcessTypeA, 1024, 54, "Worker Proc1", 0, NULL);
		pid32 wp2 = create(workerProcessTypeA, 1024, 54, "Worker Proc2", 0, NULL);
		pid32 wp3 = create(workerProcessTypeA, 1024, 54, "Worker Proc3", 0, NULL);
		pid32 wp4 = create(workerProcessTypeA, 1024, 55, "Worker Proc4", 0, NULL);
		resume(create(monitorProcess, 1024, 57, "Monitor Proc", 5, wp1,wp2,wp3,wp4,375));
		return;
}
/*------------------------------------------------------------------------
 *  workerProcessType - dispatched by the monitor process who has a higher priority than
 *  					any other worker process. Runs in an infinite loop.
 *------------------------------------------------------------------------
 */
process workerProcessTypeA()
{
	while(TRUE)
	{

	}
	return OK;
}
/*------------------------------------------------------------------------
 *  workerProcessTypeB - this worker process is also dispatched by the monitor process and simulates
 *  					 a process that sleeps often and in turn relinquishes the processor often.
 *------------------------------------------------------------------------
 */
process workerProcessTypeB()
{

	int counter = 0;
	while(TRUE)
	{
		if(++counter>=2000000)
		{
			counter =0;
			sleepms(20);
		}
	}
	return OK;
}

/*------------------------------------------------------------------------
 *  monitorProcess - this process dispatches worker processes and has higher priority than any of the workers.
 *  				 So after a time interval during which it sleeps, it will gain complete access of the CPU and meanwhile
 *  				 the worker processes get an opportunity to execute. Prints the process status on waking up
 *  				 and then is responsible for killing the dispatched worker processes after the output from
 *  				 process state is visible to tester.
 *------------------------------------------------------------------------
 */
process monitorProcess(pid32 wp1,pid32 wp2, pid32 wp3, pid32 wp4, int time)
{
	resume(wp1);
	resume(wp2);
	resume(wp3);
	resume(wp4);
	sleepms(time);
	process_state();
	kill(wp1);
	kill(wp2);
	kill(wp3);
	kill(wp4);
	return OK;
}


