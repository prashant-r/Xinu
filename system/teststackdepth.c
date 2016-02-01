/* teststackdepth.c - teststackdepth */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  teststackdepth  -  testsstackdepth
 *------------------------------------------------------------------------
 */
process teststackdepth()
{
	if(1==stackdepth())
	    kprintf("OK TEST STACK DEPTH PASSED!");
	 return OK;
}
