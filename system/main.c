/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	/* Wait for shell to exit and recreate it */
	return OK;
}
