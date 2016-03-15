/*
 * lab3q4.c
 *
 *  Created on: Feb 13, 2016
 *      Author: prashantravi
 */
/* lab3q4.c - lab3q4_AllTests, testReceiver, testSender , AsynchronousSendTest1, AsynchronousSendTest2, AsynchronousSendTest3, AsynchronousSendTest4*/
#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  lab3q4_AllTests - Runs four test cases for lab 3 q4 as required by problem spec.
 *------------------------------------------------------------------------
*/
void lab3q4_AllTests(){
	kprintf("\n------------ASYNCH SEND TEST 1------------ \n");
	AsynchronousSendTest1();
	sleepms(3000);
	kprintf("\n------------ASYNCH SEND TEST 2------------\n ");
	AsynchronousSendTest2();
	sleepms(3000);
	kprintf("\n------------ASYNCH SEND TEST 3------------ \n");
	AsynchronousSendTest3();
	sleepms(3000);
	kprintf("\n------------ASYNCH SEND TEST 4------------\n");
	AsynchronousSendTest4();
	sleepms(2000);
}

/*------------------------------------------------------------------------
 *  testReceiverer - Analogous to the testSender in that it receives the messages and spits them out to console
 *  				 for visual verification purposes.
 *------------------------------------------------------------------------
*/
process testReceiver(void) {
	while(TRUE) {
		umsg32 testreceive = receivebt();
		kprintf("\nRECEIVED: %s  \n", testreceive);
		sleepms(200);
	}
	return OK;
}
/*------------------------------------------------------------------------
 *  testSender - Sending process for this test execution
 *  			 also prints the result of the send request
 *------------------------------------------------------------------------
*/
void testSender(pid32 receiver, umsg32 msg, int32 delay) {
	uint32 startTime = clktimemsec;
	int result = sendbt(receiver, msg,delay);
	uint32 endTime =clktimemsec;
	uint32 diff = endTime - startTime;
	if( result == SYSERR ) {
		kprintf("Message failed SYSERR for PID: %d with MSG: %s STARTTIME: %d ENDTIME: %d DIFF: %d \r\n ", currpid, msg, startTime, endTime, diff);
	}
	else if(result == TIMEOUT){
		kprintf("Message failed TIMEOUT for PID: %d with MSG %s STARTTIME: %d ENDTIME: %d DIFF: %d \r\n",currpid, msg, startTime, endTime, diff);
	}
	else if(result == OK) {
		kprintf("Send succeeded for PID: %d with MSG: %s STARTTIME: %d ENDTIME: %d DIFF: %d\r\n",currpid, msg, startTime, endTime, diff);
	}
	else
	{
		kprintf("Unknown response for PID: %d with MSG: %s STARTTIME: %d ENDTIME: %d DIFF: %d \r\n", currpid, msg, startTime, endTime, diff);
	}
	return;
}

/*------------------------------------------------------------------------
 *  AsynchronousSendTest1 - tests the receive of one word by the sending process. Basic test really.
 *------------------------------------------------------------------------
*/
void AsynchronousSendTest1()
{

	int testReceive = create(testReceiver, 2048, 20, "AsynchronousReceiveTest1", 0);
	int testSend1 = create(testSender, 2048, 20, "Sender1Test1", 3, testReceive, "Works!", 1000);
	resume(testReceive);
	resume(testSend1);
}
/*------------------------------------------------------------------------
 *  AsynchronousSendTest2 - tests the receive of multiple senders. Here the receive process is the first to
 *  						be resumed so there's no chance that the messages can get dropped unless of course
 *  						the message copy of currently receive execution takes longer than one of the process's
 *  						timeout. But in our setting one-word message copy cannot take that long.
 *------------------------------------------------------------------------
*/
void AsynchronousSendTest2()
{
	int testReceive = create(testReceiver, 2048, 20, "AsynchronousReceiveTest2", 0);
	int testSend1 = create(testSender, 2048, 20, "Sender1Test2", 3, testReceive, "how", 1000);
	int testSend2 = create(testSender, 2048, 20, "Sender2Test2", 3, testReceive, "are", 500);
	int testSend3 = create(testSender, 2048, 20, "Sender3Test2", 3, testReceive, "you?", 400);
	resume(testReceive);
	resume(testSend1);
	sleepms(250);
	resume(testSend2);
	sleepms(250);
	resume(testSend3);
	sleepms(250);
}
/*------------------------------------------------------------------------
 *  AsynchronousSendTest3 - tests the dropping of messages. Here testSend 2 and testSend 3 processes
 *  						have timeouts of 500 and 400 respectively. So by invoking 100 ms sleep
 *  						and then 400 ms ensures that both processes have timed out and must exit the receiving processes's
 *  						sleeperq while at the same time also exit with a failure message signifying the
 *  						dropping of the "are" and "you?" messages.
 *------------------------------------------------------------------------
 */
void AsynchronousSendTest3()
{
	int testReceive = create(testReceiver, 2048, 20, "AsynchronousReceiveTest3", 0);
	int testSend1 = create(testSender, 2048, 20, "Sender1Test3", 3, testReceive, "how", 1000);
	int testSend2 = create(testSender, 2048, 20, "Sender2Test3", 3, testReceive, "are", 500);
	int testSend3 = create(testSender, 2048, 20, "Sender3Test3", 3, testReceive, "you?", 400);
	resume(testSend1);
	sleepms(250);
	resume(testSend2);
	sleepms(100);
	resume(testSend3);
	sleepms(400);
	resume(testReceive);
}

/*------------------------------------------------------------------------
 *  AsynchronousSendTest4 - tests the FIFO ordering of the senders in the receiver's senderq
 *  						First resume all the senders and then when they are all ready and have
 *  						entered the PR_SEND state and have entered the sleeperq then check
 *  						call start the receiver to check the results are dequeued in a FIFO manner
 *  						and the message is received correctly. Set large enough timer for the sending processes
 *  						to ensure the messages don't get dropped.
 *
 *------------------------------------------------------------------------
 */
void AsynchronousSendTest4()
{
	int testReceive = create(testReceiver, 2048, 20, "AsynchronousReceiveTest3", 0);
	int testSend1 = create(testSender, 2048, 20, "Sender1Test4", 3, testReceive, "how", 1500);
	int testSend2 = create(testSender, 2048, 20, "Sender2Test4", 3, testReceive, "are", 1500);
	int testSend3 = create(testSender, 2048, 20, "Sender3Test4", 3, testReceive, "you?", 1500);
	resume(testSend1);
	resume(testSend2);
	resume(testSend3);
	sleepms(1250);
	resume(testReceive);

}
