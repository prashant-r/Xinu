/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/* global variable */

int32 lab = 3 ;
int lab2flag=0;

process testReceive(void) {
	while(TRUE) {
		kprintf("Receive");
		umsg32 testreceive = receivebt();
		kprintf("\nRECEIVED: %s  \n", testreceive);
		sleepms(200);
	}
	return OK;
}

void testASender(pid32 receiver, umsg32 msg, int32 delay) {

	int result = sendbt(receiver, msg,delay);
	if( result == SYSERR ) {
		kprintf("Message failed SYSERR for pid %d with message %s\r\n", currpid, msg);
	}
	else if(result == TIMEOUT){
		kprintf("Message failed TIMEOUT for pid %d with message %s\r\n",currpid, msg);
	}
	else if(result == OK) {
		kprintf("Send succeeded for pid %d with message %s\r\n",currpid, msg);
	}
	else
	{
		kprintf("Unknown response for pid %d with message %s \r\n", currpid, msg);
	}
	return;
}

process	main(void)
{

	//LAB 2.4.2
	//lab2q4t3();


	int testAReceive = create(testReceive, 2048, 20, "testAsynchronousReceive", 0);
	int testASend1 = create(testASender, 2048, 20, "testAsynchronousSend", 3, testAReceive, "hello", 1000);
	int testASend2 = create(testASender, 2048, 20, "testAsynchronousSend", 3, testAReceive, "how", 500);
	int testASend3 = create(testASender, 2048, 20, "testAsynchronousSend", 3, testAReceive, "are", 400);
	int testASend4 = create(testASender, 2048, 20, "testAsynchronousSend", 3, testAReceive, "you?", 2000);
	resume(testASend1);
	resume(testASend2);
	resume(testASend3);
	resume(testASend4);
	resume(testAReceive);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	/* Wait for shell to exit and recreate it */
	while(TRUE)
	{

	}
	return OK;
}
