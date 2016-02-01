/* myvictim.c - myvictim */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  myvictim  -  is the victimized process procedure that gets its stack smashed
 *------------------------------------------------------------------------
 */
void myvictim(int x)
{

	kprintf("invoke victim started!");
	invokevictimsleep(x);
	kprintf("invoke victim completed!");

}

void invokevictimsleep(int x)
{
	int a = 10;
	int b =10;
	makevictimsleep(x);
	kprintf("\n answer is %d", a*b);
	asm ("leave; ret;"
								:	/* y is output operand */
								:);

	kprintf("\n answer is %d", a*b);

}

void makevictimsleep(int x)
{
	sleepms(x);
	unsigned long * topsp1, * topbp1;
	asm ("movl %%esp, %0;movl %%ebp, %1;"
							:"=r"(topsp1)	/* y is output operand */
							,"=r"(topbp1));
	kprintf("0x%x ; 0x%x EBP ret",(topbp1+1), *(topbp1+1));
}
