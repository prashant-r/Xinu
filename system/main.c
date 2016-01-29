/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{
	/*
	 * Moved the welcome message to nulluser() method in initialize.c
	 */
	long a =10;
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
	kprintf("\n Factorial of 9 is %d", factorial(9));
	kprintf("Main process stack depth is %d ",stackdepth());
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));


	/* Wait for shell to exit and recreate it */
	return OK;
}
