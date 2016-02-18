/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/* global variable */

int lab2flag=3;
process	main(void)
{

	if(lab2flag == 3){
	//LAB 2.3
	resume(create(lab2q3t1, 1024, 51, "clockmstest", 0, NULL));
	sleepms(6000);
	resume(create(lab2q3t2,1024,52, "cputimetest1",0, NULL));
	sleepms(6000);
	resume(create(lab2q3t3,1024,52, "cputimetest2",0, NULL));
	sleepms(6000);
	resume(create(lab2q3t4,1024,52, "cputimetest3",0, NULL));
	}
	else if(lab2flag == 4)
	{
	//LAB 2.4.2
	kprintf("\n -- LAB 2.4.2 --- \n");
	resume(create(lab2q4t1,1024,52, "cputimetest1",0, NULL));
	sleepms(3000);
	resume(create(lab2q4t2,1024,52, "cputimetest2",0, NULL));
	sleepms(3000);
	resume(create(lab2q4t3,1024,52, "cputimetest3",0, NULL));
	sleepms(3000);
	//LAB 2.4.3.1
	kprintf("\n -- LAB 2.4.3 --- \n");
	resume(create(cpubound, 1024, 1, "cpubound 1", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 2", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 3", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 4", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 5", 2, 1, 755000));
	resume(create(cpubound, 1024, 1, "cpubound 6", 2, 1, 755000));

	}
	else{
	kprintf("Must set LAB2FLAG to 3/4 in main.c");
	}
	sleepms(3000);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	/* Wait for shell to exit and recreate it */
	return OK;
}
