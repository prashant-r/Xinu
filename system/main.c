/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/* global variable */

int32 lab = 2;
int lab2flag=0;
process	main(void)
{
	kprintf("\n------------LAB 4 Q 2 ASYNC-CALLBACK ALL TESTS------------ \n");
	lab4q2_AllTests();
	kprintf("\n------------LAB 4 Q 3 SIGTESTS ------------ \n");
	lab4q3_AllTests();
	//resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	while(TRUE)
	{
	}
	return OK;
}
