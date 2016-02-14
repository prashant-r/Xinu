/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/* global variable */
int victimglobal =0;
unsigned int victimsRetAddress;

process	main(void)
{
	resume(create(lab2q3t1, 1024, 51, "clockmstest", 0, NULL));
	sleepms(6000);
	resume(create(lab2q3t2,1024,52, "cputimetest1",0, NULL));
	sleepms(4000);
	resume(create(lab2q3t3,1024,52, "cputimetest2",0, NULL));
	sleepms(3000);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	/* Wait for shell to exit and recreate it */
	return OK;
}
