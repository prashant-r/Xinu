/* myvictim.c - myvictim
 * 				invokevictimsleep
 * 				makevictimsleep
 */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  myvictim  -  is the victimized process procedure that gets its stack smashed
 *  			 Note: before invoking invokevictimsleep ,the value for victimglobal was 0
 *  			 but after execution, the "hacker" changed the victimglobal's value to 1.
 *------------------------------------------------------------------------
 */
void myvictim(int x)
{

	kprintf("\n PID is %d | In Func : myvictim | Msg: starting invokevictimsleep | victimglobal val is %d \n ", currpid, victimglobal);
	invokevictimsleep(x);
	kprintf("\n PID is %d | In Func : myvictim | Msg: ended invokevictimsleep | victimglobal val is %d \n ", currpid, victimglobal);

}
/*------------------------------------------------------------------------
 *  invokevictimsleep  -  Mutltiplies two number 10,10 and invokes makevictimsleep.
 *------------------------------------------------------------------------
 */
void invokevictimsleep(int x)
{
	int a = 10;
	int b =10;
	makevictimsleep(x);
	kprintf("\n PID is %d | In Func : invokevictimsleep | Msg: calc 10*10 = %d | victimglobal val is %d \n ", currpid, a*b, victimglobal);


}
/*------------------------------------------------------------------------
 *  makevictimsleep  -  Adds two numbers 20,45 and makes the process go to sleep for 3 seconds
 *  					during this time myhacker runs and changes this method's return address to be
 *  					that of myhackermalware instead of invokevictimsleep.
 *------------------------------------------------------------------------
 */
void makevictimsleep(int x)
{
	int a = 20;
	int b =45;
	sleepms(x);
	kprintf("\n PID is %d | In Func : makevictimsleep | Msg: calc 20+45 = %d | victimglobal val is %d \n ", currpid, a+b, victimglobal);
}
