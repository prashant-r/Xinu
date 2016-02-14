/*
 * lab2q3.c
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
		resume(create(monitorProcess, 1024, 55, "Monitor Proc", 5, wp1,wp2,wp3,wp4,245));
		return;
}

void lab2q3t3()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q3t3 test | Note: 3 (workerProcessTypeA) equal CPU usage and 1 sleeper workerProcessTypeB");
		kprintf("\n (Monitor process will have higher priority than workerProcessTypeA) ");
		kprintf("\n -------------------------\n");
		pid32 wp1 = create(workerProcessTypeA, 1024, 54, "Worker Proc1", 0, NULL);
		pid32 wp2 = create(workerProcessTypeA, 1024, 54, "Worker Proc2", 0, NULL);
		pid32 wp3 = create(workerProcessTypeA, 1024, 54, "Worker Proc3", 0, NULL);
		pid32 wp4 = create(workerProcessTypeB, 1024, 54, "Worker Proc4", 0, NULL);
		resume(create(monitorProcess, 1024, 55, "Monitor Proc", 5, wp1,wp2,wp3,wp4,375));
		return;
}

process workerProcessTypeA()
{
	while(TRUE)
	{

	}
}

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
}

process monitorProcess(pid32 wp1,pid32 wp2, pid32 wp3, pid32 wp4, int time)
{
	resume(wp1);
	resume(wp2);
	resume(wp3);
	resume(wp4);
	sleepms(time);
	xsh_ps(0,NULL);
	kill(wp1);
	kill(wp2);
	kill(wp3);
	kill(wp4);
	return OK;
}


