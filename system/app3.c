/* app3.c - app */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  app3  -  prints PID of current process
 *------------------------------------------------------------------------
 */
process app3()
{
		int a = 101*555;
		kprintf("\n The answer to 101 times 555 is %d , app3's PID is %d and priority is %d", a, getpid(), getprio(getpid()));
		kprintf("\n -------------");
		kprintf("PID of %s's parent is %d",getpname(getpid()), getppid());
		return OK;
}
