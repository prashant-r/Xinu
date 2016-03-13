/* multilevelfbq.c- implements the dequeue operation for the multilevel feedback queue*/
#include <xinu.h>

/*------------------------------------------------------------------------
 * multifeedbackDQ - dequeue the first process on the highest level queue that is not empty for datastructure defined in
 * 					 multilevelfbq.h that maintains a queue for each level between 0 and 20. Returns the pid32 that is on the highest level list.
 *------------------------------------------------------------------------
 */
pid32 multifeedbackDQ()
{
	int highestLevel;
	for(highestLevel = 19; highestLevel>=0; highestLevel--)
	{
		if(!isempty(queueArr[highestLevel]))
		{
			pid32 processSelected = dequeue(queueArr[highestLevel]);
			return processSelected;
		}
	}
	return -1;

}

void printMFQ()
{
	int highestLevel;
	for(highestLevel = 0; highestLevel<=19; highestLevel++)
		{
			if(!isempty(queueArr[highestLevel]))
			{
				kprintf("Non-Empty Queue at Level %d \n ", highestLevel);
				printQueue(queueArr[highestLevel]);
			}

		}
}
