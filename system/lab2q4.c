/*
 * lab2q4.c
 *
 *  Created on: Feb 13, 2016
 *      Author: prashantravi
 */
/* lab2q4.c - lab2q4 */
#include <xinu.h>
#include <stdio.h>
void lab2q4t1()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q4t1 test | Note: 4 (workerProcessTypeA) equal CPU usage seen by  monitorProcess");
		kprintf("\n (Monitor process will have higher priority than workerProcessTypeA) ");
		kprintf("\n -------------------------\n");
		pid32 wp1 = create(workerProcessTypeA, 1024, 54, "Worker Proc1", 0, NULL);
		pid32 wp2 = create(workerProcessTypeA, 1024, 54, "Worker Proc2", 0, NULL);
		pid32 wp3 = create(workerProcessTypeA, 1024, 54, "Worker Proc3", 0, NULL);
		pid32 wp4 = create(workerProcessTypeA, 1024, 54, "Worker Proc4", 0, NULL);
		resume(create(monitorProcess, 1024, 57, "Monitor Proc", 5, wp1,wp2,wp3,wp4,245));
		return;
}

void lab2q4t2()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q4t2 test | Note: 3 (workerProcessTypeA) and 1 sleeper workerProcessTypeB");
		kprintf("\n (Monitor process will have higher priority than workerProcessTypeA/B) ");
		kprintf("\n -------------------------\n");
		pid32 wp1 = create(workerProcessTypeA, 1024, 54, "Worker Proc1", 0, NULL);
		pid32 wp2 = create(workerProcessTypeA, 1024, 54, "Worker Proc2", 0, NULL);
		pid32 wp3 = create(workerProcessTypeA, 1024, 54, "Worker Proc3", 0, NULL);
		pid32 wp4 = create(workerProcessTypeB, 1024, 54, "Worker Proc4", 0, NULL);
		resume(create(monitorProcess, 1024, 57, "Monitor Proc", 5, wp1,wp2,wp3,wp4,375));
		return;
}

void lab2q4t3()
{
		kprintf("\n -------------------------");
		kprintf("\n In lab2q4t3 test | Note: 3 (workerProcessTypeA) and 1 higher priority workerProcessTypeA");
		kprintf("\n (Monitor process will have higher priority than workerProcessTypeA) ");
		kprintf("\n -------------------------\n");
		pid32 wp1 = create(workerProcessTypeA, 1024, 54, "Worker Proc1", 0, NULL);
		pid32 wp2 = create(workerProcessTypeA, 1024, 54, "Worker Proc2", 0, NULL);
		pid32 wp3 = create(workerProcessTypeA, 1024, 54, "Worker Proc3", 0, NULL);
		pid32 wp4 = create(workerProcessTypeA, 1024, 55, "Worker Proc4", 0, NULL);
		resume(create(monitorProcess, 1024, 57, "Monitor Proc", 5, wp1,wp2,wp3,wp4,375));
		return;
}

