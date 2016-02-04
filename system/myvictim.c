/* myvictim.c - myvictim */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  myvictim  -  is the victimized process procedure that gets its stack smashed
 *------------------------------------------------------------------------
 */
void myvictim(int x)
{

	kprintf("\n invoke victim started! victimglobal is %d \n", victimglobal);
	invokevictimsleep(x);
	kprintf("\n Location of victimGlobal 0x%x, its value is %d ", &victimglobal, victimglobal);
	kprintf("\n invoke victim completed! victimglobal is %d \n", victimglobal);

}

void invokevictimsleep(int x)
{
	int a = 10;
	int b =10;
	makevictimsleep(x);
	kprintf("\n answer is %d", a*b);

}

void makevictimsleep(int x)
{
	kprintf(" Sleep amount %d ", x);
	sleepms(x);
	unsigned long * topsp1, * topbp1;
		asm ("movl %%esp, %0;movl %%ebp, %1;"
								:"=r"(topsp1)	/* y is output operand */
								,"=r"(topbp1));
		kprintf("\n ######## 0x%x ; 0x%x EBP ret #########\n",(topbp1+1), *(topbp1+1));
}
