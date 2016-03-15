/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/* global variable */

int32 lab = 3 ;
int lab2flag=0;

process	main(void)
{

	// NOTE: to test out either lab make sure to set lab variable
	// Comment out the lab code corresponding to lab 3.3 / 3.4 for easy viewing on console to test
	// lab results for each part of the lab separately. Thanks!

//*************************************************************************************
	//LAB 3.3.3-3.3.4
	kprintf("\n -- LAB 3.3 --- \n");

	kprintf("ALL CPU BOUND PROCESSES! \n");
	sleepms(2000);
	lab3q3t1();
	kprintf("ALL IO BOUND PROCESSES! \n");
	sleepms(5000);
	lab3q3t2();
	kprintf("MIX BOUND PROCESSES! \n");
	sleepms(5000);
	lab3q3t3();


	sleepms(2000);
//*************************************************************************************
	// LAB 3.4


	kprintf("\n -- LAB 3.4 --- \n");



	lab3q4_AllTests();


//*************************************************************************************
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	/* Wait for shell to exit and recreate it */

	while(TRUE)
	{

	}
	return OK;
}
