/* getppid.c - getppid */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getppid  -  Return the ID of the currently executing process's parent
 *------------------------------------------------------------------------
 */
pid32	getppid(void)
{
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	prptr = &proctab[(currpid)];
	return prptr->prparent;
}
