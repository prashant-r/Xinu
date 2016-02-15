/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/* global variable */

int lab2flag=4;
process	main(void)
{
	resume(create(cpubound, 1024, 1, "cpubound 1", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 2", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 3", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 4", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 5", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 6", 2, 1, 755000));
	sleepms(10000);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	/* Wait for shell to exit and recreate it */
	return OK;
}
