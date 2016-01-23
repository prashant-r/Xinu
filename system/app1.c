/* app1.c - app */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  app1  -  prints PID of current process
 *------------------------------------------------------------------------
 */
process app1()
{
		kprintf("\n The PID for %s is %d",getpname(getpid()), getpid());

		return OK;
}
