/*
 * lab4q3.c
 *
 *  Created on: Feb 13, 2016
 *      Author: prashantravi
 */
/* lab4q3.c - lab4q3_AllTests, testReceiver, testSender , AsynchronousSendTest1, AsynchronousSendTest2, AsynchronousSendTest3, AsynchronousSendTest4*/
#include <xinu.h>
#include <stdio.h>

umsg32 msgglob;
bool8 useSigRecv;
/*------------------------------------------------------------------------
 *  lab4q3_AllTests - Runs four test cases for lab 3 q4 as required by problem spec.
 *------------------------------------------------------------------------
*/
void lab4q3_AllTests(){
	kprintf("\n // SIGRECV TESTS //\n");
	useSigRecv = TRUE;
	lab4q2_AllTests();
	kprintf("\n // ALARM TEST 1 //\n");
	pid32 alarmTest1 = create(AlarmTest1,1024,20,"AlarmTest1",0);
	resume(alarmTest1);
	sleepms(2000);
	kprintf("\n // ALARM TEST 2 //\n");
	pid32 alarmTest2 = create(AlarmTest2,1024,20,"AlarmTest2",0);
	resume(alarmTest2);
	sleepms(2000);
	kprintf("\n // XCPUTEST 1 //\n");
	pid32 xcpuTest1 = create(XCputest1,1024,20,"XCputest1",0);
	resume(xcpuTest1);
	sleepms(1000);
	kprintf("\n // XCPUTEST 2 //\n");
	pid32 xcpuTest2 = create(XCputest2,1024,20,"XCputest2",0);
	resume(xcpuTest2);
	sleepms(1000);
	kprintf("\n // MIXEDTEST 1 //\n");
	pid32 mixedTest1 = create(mixedTest,1024,20,"MixedTest1",0);
	resume(mixedTest1);
}


void myalarmhandler()
{
	kprintf(" Alarm handler called on process %d at time: %d\n", currpid, clktimemsec);
}

void myxcpuhandler()
{
	struct	procent *prptr = &proctab[currpid];
	kprintf(" XCPU handler called on process %d CPU time consumed so far: %d\n", currpid, (prptr->prcpumsec + (clktimemsec- prptr->prctxswintime)));
}

void myxcpuhandler_alternate()
{
	struct	procent *prptr = &proctab[currpid];
	kprintf(" XCPU handler alternate called on process %d CPU time consumed so far: %d\n", currpid, (prptr->prcpumsec + (clktimemsec- prptr->prctxswintime)));
}

int registerSignal(uint16 asig, int16 time)
{
	switch(asig) {
		   case MYSIGRECV :{
			   if (registercbsig(MYSIGRECV, &myrecvhandler) != OK) {
			   			kprintf("recv handler registration failed\n");
			   	    	return 1;
			   		}
			   break; /* optional */}
		   case MYSIGALRM :{
			   if(time == NULL){
			   if (registercbsig(MYSIGALRM, &myalarmhandler) != OK) {
			   			kprintf("alarm handler registration failed\n");
			   	    	return 1;
			   		}
			   }
			   else
			   {
				   if (registercbsig(MYSIGALRM, &myalarmhandler, time) != OK) {
				   			   			kprintf("alarm handler registration failed\n");
				   			   	    	return 1;
				   			   		}
			   }
		       break; /* optional */}
		   case MYSIGXCPU:{
			   if (registercbsig(MYSIGXCPU, &myxcpuhandler, time) != OK) {
			   			kprintf("xcpu handler registration failed\n");
			   	    	return 1;
			   		}
			   break;
			  }
		   /* you can have any number of case statements */
		   default : /* Optional */
			   kprintf("In registercbsig: Invalid Signal");
		}
		return OK;

}


void AlarmTest1()
{
	registerSignal(MYSIGALRM, NULL);
	alarmms(1000);
	while(TRUE)
	{
		sleepms(20);
	}

}

void AlarmTest2()
{
	registerSignal(MYSIGALRM, NULL);
	alarmms(200);
	alarmms(100);
	while(TRUE)
	{
		sleepms(20);
	}

}

void XCputest1()
{
	registerSignal(MYSIGXCPU, 200);
	while(TRUE)
	{
	}
}


void XCputest2()
{
	registerSignal(MYSIGXCPU, 300);
	if (registercbsig(MYSIGXCPU, &myxcpuhandler_alternate, 120) != OK) {
			kprintf("xcpu handler alternate registration failed\n");
			return;
	}
	while(TRUE)
	{

	}
}


void mixedProcess(int xcpu, int alarm)
{
	registerSignal(MYSIGRECV, NULL);
	registerSignal(MYSIGXCPU, xcpu);
	registerSignal(MYSIGALRM, NULL);
	alarmms(alarm);
	while(TRUE)
	{

	}
}

void mixedTest()
{

	pid32 asyncMixed1 = create(mixedProcess,1024,20,"mixed1Test",2,300,250);
	pid32 asyncMixed2 = create(mixedProcess,1024,20,"mixed2Test",2,200,280);
	pid32 asyncSend1  = create(AsynchronousSender,1024,20,"Sender4Test3",2,asyncMixed1,13);
	pid32 asyncSend2  = create(AsynchronousSender,1024,20,"Sender4Test3",2,asyncMixed2,14);
	resume(asyncMixed1);
	resume(asyncMixed2);
	sleepms(500);
	resume(asyncSend1);
	resume(asyncSend2);

}








