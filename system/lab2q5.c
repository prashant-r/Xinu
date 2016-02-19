/*
 * lab2q5.c
 *
 *  Created on: Feb 18, 2016
 *      Author: ravi18
 */


/*
 * lab2q5.c
 *
 *  Created on: Feb 13, 2016
 *      Author: prashantravi
 */
/* lab2q5.c - lab2q5 */
#include <xinu.h>
#include <stdio.h>


void lab2q5t1()
{
	pid32 a,b,c,d,e,f;
				resume(a=create(cpubound, 1024, 1, "cpubound 1", 2, 1, 155000));
				sleepms(100);
				resume(b=create(cpubound, 1024, 1, "cpubound 2", 2, 1, 155000));
				sleepms(500);
				resume(c=create(cpubound, 1024, 1, "cpubound 3", 2, 1, 155000));
				sleepms(50);
				resume(d=create(cpubound, 1024, 1, "cpubound 4", 2, 1, 155000));
				sleepms(2000);
				resume(e=create(cpubound, 1024, 1, "cpubound 5", 2, 1, 155000));
				sleepms(100);
				resume(f=create(cpubound, 1024, 1, "cpubound 6", 2, 1, 155000));
				struct procent * prptr;
				int counter = 0;
				while(!(prptr = &proctab[a])->prstate == PR_FREE ||!(prptr = &proctab[b])->prstate == PR_FREE ||
			!(prptr = &proctab[c])->prstate == PR_FREE || !(prptr = &proctab[e])->prstate == PR_FREE || !(prptr = &proctab[d])->prstate == PR_FREE || !(prptr = &proctab[f])->prstate == PR_FREE)
				{
					if(counter++ >20000){
						counter =0;
						process_state();
					}
				}

}



