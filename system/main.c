/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{
	/*
	 * Moved the welcome message to nulluser() method in initialize.c
	 */
	long a =10;
	unsigned long *topsp1, *topbp1;
	unsigned long *topsp2, *topbp2;
	pid32 myappA1;
	kprintf("10 in hexadecimal little endian is 0x%04x",a);
	kprintf("\n");
	kprintf("\n");
	kprintf("Big endian format as follows:");
	kprintf("\n");
	kprintf("1.Result of host2netla is 0x%04x", host2netla(a));
	kprintf("\n");
	kprintf("2.Result of host2netlb is 0x%04x", host2netlb(a));
	kprintf("\n");
	kprintf("2.Result of host2netlc is 0x%04x", host2netlc(a));
	kprintf("\n");
	printsegaddr();
	//kprintf("\n Factorial of 9 is %d", factorial(9));
	kprintf("\n Main process stack depth shown below: \n ");
	stackdepth();
	asm ("movl %%esp, %0;movl %%ebp, %1;"
						:"=r"(topsp1)	/* y is output operand */
						,"=r"(topbp1));
	kprintf("\n 1. ESP is 0x%x , its content is 0x%x and EBP is 0x%x \n", topsp1, *topsp1, topbp1);
	myappA1 = create(myappA, 1024, 20, "myAppA", 1, currpid);
	asm ("movl %%esp, %0;movl %%ebp, %1;"
						:"=r"(topsp2)	/* y is output operand */
						,"=r"(topbp2));
	kprintf("\n 2. ESP is 0x%x , its content is 0x%x and EBP is 0x%x \n", topsp2, *(topsp2), topbp2);
	resume(myappA1);
	sleepms(2000);

	create(myappA, 1024, 20, "myAppA", 1, currpid);
	create(myappA, 1024, 20, "myAppA", 1, currpid);

	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));


	/* Wait for shell to exit and recreate it */
	return OK;
}
