/* app2.c - app */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  app2  -  prints PID of current process
 *------------------------------------------------------------------------
 */
process app2()
{

		kprintf("\n The PID for %s is %d",getpname(getpid()), getpid());
		resume(create(app3, 1024, 48, "app3", 0, NULL));
		sleep(5);
		kprintf("\n The PID for %s is %d and it's parent is %d",getpname(getpid()), getpid(), getppid());
		return OK;
}
