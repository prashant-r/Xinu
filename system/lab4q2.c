/*
 * lab4q2.c
 *
 *  Created on: Feb 13, 2016
 *      Author: prashantravi
 */
/* lab4q2.c - lab4q2_AllTests, testReceiver, testSender , AsynchronousSendTest1, AsynchronousSendTest2, AsynchronousSendTest3, AsynchronousSendTest4*/
#include <xinu.h>
#include <stdio.h>

umsg32 msgglob;
bool8 useSigRecv;
/*------------------------------------------------------------------------
 *  lab4q2_AllTests - LAB 4Q2 :  Runs four test cases for lab 3 q4 as required by problem spec.
 *------------------------------------------------------------------------
*/
void lab4q2_AllTests(){
	// global variable useSigRecv determines if the registercb is
	useSigRecv = FALSE;
	kprintf("\n // TEST 1 //\n");
	AsynchronousTest1();
	kprintf("\n // TEST 2 //\n");
	AsynchronousTest2();
	kprintf("\n // TEST 3 //\n");
	AsynchronousTest3();
}

/*------------------------------------------------------------------------
 *  AsynchronousSender -  LAB 4Q2 sends a message to the receiver
 *------------------------------------------------------------------------
*/
int32 AsynchronousSender(pid32 receiver, umsg32 msg)
{

	if( send(receiver, msg) == SYSERR ) {
		kprintf("Message %d failed to send to %d\r\n", msg, receiver);
		return SYSERR;
	} else {
		//kprintf("Message %d was sent successfully to %d ! %d\r\n", msg, receiver);
	}
	return OK;
}

/*------------------------------------------------------------------------
 *  AsynchronousReceiver -  LAB 4Q2 using registercbsig and registercb are identical and they
 *  					   register the callback function for the when the message does arrive
 *  					   that which needs to be executed.
 *------------------------------------------------------------------------
*/
int AsynchronousReceiver()
{
	if(useSigRecv)
	{
		if (registercbsig(MYSIGRECV, &myrecvhandler) != OK) {
					   			kprintf("recv handler registration failed\n");
					   	    	return 1;
					   		}
	}
	else{
		if (registercb(&myrecvhandler) != OK) {
			kprintf("recv handler registration failed\n");
			return 1;
		}
	}
	while(TRUE)
	{

	}
}
/*------------------------------------------------------------------------
 *  AsynchronousReceiver_NoReceive - LAB 4Q2 Similar to Asynchronous Receive but registers a handler that doesn't actually recieve() the
 *  								 message so it simulates an app programmer who just doesn't care about the message
 *  								 buffer being cleared or not. We as kernel developers must ensure the message becomes stale after the
 *  								 callback function has executed so new messages can be received.
 *------------------------------------------------------------------------
*/

int AsynchronousReceiver_NoReceive()
{
	if (registercb(&myrecvhandler_NoReceive) != OK) {
	      kprintf("recv handler registration failed\n");
	      return 1;
	}
	while(TRUE)
	{

	}
}
/*------------------------------------------------------------------------
 *  myrecvhandler_NoReceive :  LAB 4Q2 A handler that doesn't actually invoke receive() to retrieve messages.   -
 *------------------------------------------------------------------------
*/

int myrecvhandler_NoReceive(void) {
	//kprintf("In myrecvhandler_NoReceive: pid: %d time: %d\n", currpid, clktimemsec);
	return(OK);
}
/*------------------------------------------------------------------------
 *  myrecvhandler :  LAB 4Q2 Typical handler that does actually invoke receive() to retrieve messages.   -
 *------------------------------------------------------------------------
*/

int myrecvhandler(void) {
	msgglob = receive();  // use global to return value
	kprintf(" In myrecvhandler: pid: %d time: %d msg: %d\n", currpid, clktimemsec, msgglob);
	return(OK);
}


/*------------------------------------------------------------------------
 *  AsynchronousTest1 : LAB 4Q2 This test is to check that  a simple one word message get's delivered timely
 *  					and that the callback function executes correcty.
 *------------------------------------------------------------------------
*/

void AsynchronousTest1() // asynchronous message test 1
{
	pid32 asyncRec1 = create(AsynchronousReceiver,1024,20,"Receiver1Test1",0,NULL);
	resume(asyncRec1);
	recvclr();
	int32 result = AsynchronousSender(asyncRec1, 40);
	sleepms(25);
	if(result == OK && msgglob == 40 )
		kprintf("Test1 passed!\n");
	else
		kprintf("Test1 failed! result %d \n", msgglob);
}

/*------------------------------------------------------------------------
 *  AsynchronousTest2 :  LAB 4Q2 This test is to check the influence of having process invoke receive()
 *  				    in the call back handler. To make sure that we clear the message buffer flag correctly
 *  				    after each callback function execution.
 *------------------------------------------------------------------------
*/

void AsynchronousTest2() // asynchronous message test 2
{
	pid32 asyncRec1 = create(AsynchronousReceiver_NoReceive,1024,20,"Receiver1Test2",0,NULL);
	resume(asyncRec1);
	bool8 check = TRUE;
	recvclr();
	int32 result = AsynchronousSender(asyncRec1, NULL);
	sleepms(25);
	if(result != OK)
		check = FALSE;
	result = AsynchronousSender(asyncRec1, NULL);
	sleepms(25);
	if(result != OK )
		check = FALSE;
	if(check == TRUE)
		kprintf("Test2 passed!\n");
	else
		kprintf("Test2 failed! \n", msgglob);
}

/*------------------------------------------------------------------------
 *  AsynchronousTest3 :  LAB 4Q2 This test is to check that once registered a callback for a process,
 *  					we won't need to re register the callback and multiple senders can send
 *  					the process messages and each time it would execute the callback function
 *  					accordingly.
 *------------------------------------------------------------------------
*/
void AsynchronousTest3() // asynchronous message test 3
{
	pid32 asyncRec1 =  create(AsynchronousReceiver,1024,20,"Reeiver1Test3",0,NULL);
	pid32 asyncSend1 = create(AsynchronousSender,1024,20,"Sender1Test3",2,asyncRec1,13);
	pid32 asyncSend2 = create(AsynchronousSender,1024,20,"Sender2Test3",2,asyncRec1,14);
	pid32 asyncSend3 = create(AsynchronousSender,1024,20,"Sender3Test3",2,asyncRec1,15);
	pid32 asyncSend4 = create(AsynchronousSender,1024,20,"Sender4Test3",2,asyncRec1,16);

	bool8 test = TRUE;
	resume(asyncRec1);
	sleepms(25);
	resume(asyncSend1);
	sleepms(25);
	if(msgglob != 13 ){
		test = FALSE;
	}
	resume(asyncSend2);
	sleepms(25);
	if(msgglob != 14 ){
		test = FALSE;
	}
	resume(asyncSend3);
	sleepms(25);
	if(msgglob != 15 ){
		test = FALSE;
	}
	resume(asyncSend4);
	sleepms(25);
	if(msgglob != 16 ){
		test = FALSE;
	}
	if(test)
		kprintf("Test3 passed!\n");
	else
		kprintf("Test3 failed!\n");
}














