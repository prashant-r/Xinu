#include <xinu.h>

syscall registercbsig(uint16 asig, int (*func)(void),uint32 optarg){

	intmask mask;
	mask = disable();
	if(func == NULL)
	{
		restore(mask);
		return SYSERR;
	}
	switch(asig) {
	   case MYSIGRECV :{
		   struct procent *prptr = &proctab[currpid];
		   prptr->callback = func; //point to the callback function
		   break; /* optional */}
	   case MYSIGALRM :{
		   struct procent *prptr = &proctab[currpid];
		   if(prptr->alarmfunc == NULL){
			   prptr->alarmfunc = func;	// point to the callback function
			   if(optarg != NULL){
			   prptr->alarmtime = optarg;
		   	   alarminsertd(currpid, alarmq, optarg); // inserted the process into the delta list that stores all the alarms
			   }
		   	}
		   else
		   {
			   prptr->alarmfunc = func;	// point to the callback function
			   if(optarg != NULL){
			   	prptr->alarmtime = optarg;
			   	alarmgetitem(currpid);
			   	alarminsertd(currpid, alarmq, optarg); // overwrite existing alarm
			   }
		   }
	       break; /* optional */}
	   case MYSIGXCPU:{
		   struct procent *prptr = &proctab[currpid];
		   if(prptr->xcpufunc == NULL)
		   {
			   kprintf(" XCPU Signal for process %d CPU time consumed so far: %d\n", currpid, prptr->prcpumsec);
		   }
		   else
		   {
			   kprintf("Overwriting XCPU Signal for process %d CPU time consumed so far: %d\n", currpid, prptr->prcpumsec);
		   }
		   prptr->xcpufunc = func; //sets pointer sigxcpu function callback
		   prptr->xcputime = optarg;

		   break;}
	   /* you can have any number of case statements */
	   default : /* Optional */
		   kprintf("In registercbsig: Invalid Signal");
	}
	restore(mask);	//restore the mask
	return OK;
}
