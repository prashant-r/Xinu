/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{
	/*
	 * Moved the welcome message to nulluser() method in initialize.c
	 */

	resume(create(app1, 1024, 48, "app1", 0, NULL));
	resume(create(app2, 1024, 48, "app2", 0, NULL));
	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));

	/* Wait for shell to exit and recreate it */
	return OK;
}
