/* getpname.c - getpname */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getpname  -  Return the name of the given process
 *------------------------------------------------------------------------
 */
extern	char	*getpname(int32 pid)
{
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	prptr = &proctab[(pid)];
	return prptr->prname;
}



