/* teststackdepth.c - teststackdepth */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  teststackdepth  -  testsstackdepth tests the case provided on design spec for lab1
 *------------------------------------------------------------------------
 */
process teststackdepth()
{
	if(1==stackdepth())
	    kprintf("OK TEST STACK DEPTH PASSED!");
	 return OK;
}
