#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"

#include "OS_interface.h"
#include "OS_private.h"
#include "OS_config.h"

#define NULL     ( (void*)0 )
/* array of tasks (array of struct) it is better to put tasks in linked list */
static Task OS_Task[MAX_NUM_OF_TASKS] = { NULL };

volatile u16 tickCount = 0;

u8 OS_u8TasksNum = 0;

void OS_voidCreateTask(u8 copy_u8Proirity,u16 copy_periodicity,void(*copy_ptr)(void),u8 copy_u8FD)
{
	if(OS_u8TasksNum == MAX_NUM_OF_TASKS)
	{}
	else
	{
	  	OS_Task[copy_u8Proirity].periodicity = copy_periodicity ;
	    OS_Task[copy_u8Proirity].f_ptr = copy_ptr ;
	    OS_Task[copy_u8Proirity].firstDelay = copy_u8FD;
	    OS_Task[copy_u8Proirity].State  = READY;
	    OS_u8TasksNum++;
	}

}

void OS_voidStart(void)
{
	/* initialization */
	STK_voidInit();
	/* Tick = 1 msec */
	STK_voidSetIntervalPeriodic(1000,OS_voidScheduler);

}

void OS_voidScheduler(void)
{
	for(u8 i=0 ; i<OS_u8TasksNum ;i++)
	{
		if( (OS_Task[i].f_ptr != NULL) && (OS_Task[i].State == READY) )
		{
			if(OS_Task[i].firstDelay == 0)
			{
				OS_Task[i].firstDelay = OS_Task[i].periodicity-1 ;
			    OS_Task[i].f_ptr();
			}

			else
				OS_Task[i].firstDelay--;
		}
    }
    tickCount++;
}

void OS_voidSuspend(u8 copy_u8TaskId)
{
	OS_Task[copy_u8TaskId].State = SUSPEND ;
}

void OS_voidResume (u8 copy_u8TaskId)
{
	OS_Task[copy_u8TaskId].State = READY ;
}

void OS_voidDelete (u8 copy_u8TaskId)
{
	OS_Task[copy_u8TaskId].State = DELETE ;
	while(copy_u8TaskId == OS_u8TasksNum-1)
	{
		OS_Task[copy_u8TaskId] = OS_Task[copy_u8TaskId+1];
		copy_u8TaskId++;
	}
}
