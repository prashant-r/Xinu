/* factorial.c - factorial */
#include <xinu.h>
#include <stdio.h>
/*------------------------------------------------------------------------
 *  factorial  -  is a recursive function to compute the factorial of the argument
 *------------------------------------------------------------------------
 */
int factorial(int a)
{
		if(a == 1)
			return 1;
		else
		{
			stackdepth();
			return a*factorial(a-1);
		}
}
