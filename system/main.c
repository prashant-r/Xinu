/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/* global variable */

bool8 lab2 = FALSE;
int lab2flag=0;

process	main(void)
{

	//LAB 2.4.2
	lab2q4t3();
	sleepms(7000);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	/* Wait for shell to exit and recreate it */
	return OK;
}
