/*
 * MyNewTask.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Cursos
 */
/**/
#include "MyNewTask.h"
#include "fsl_os_abstraction.h"
#define gMyTaskPriority_c 3
#define gMyTaskStackSize_ 400
/*TimerID */
osaEventId_t mMyEvents;
/* Handler */
tmrTimerID_t gMyTaskHandler_ID;
/*current state LED*/
static uint8_t ledsState = 0;

OSA_TASK_DEFINE(My_Task, gMyTaskPriority_c, 1, gMyTaskStackSize_, FALSE);
static tmrTimerID_t myTimerID;

/* Main custom task */
void My_Task(osaTaskParam_t argument)
{
	osaEventFlags_t customEvent;
	myTimerID = TMR_AllocateTimer();

	while(1)
	{
		OSA_EventWait(mMyEvents, osaEventFlagsAll_c, FALSE, osaWaitForever_c, &customEvent);

		if( !gUseRtos_c && !customEvent)
		{
			break;
		}

		/* Depending on the received event */
		switch(customEvent)
		{
		case gMyNewTaskEvent1_c:
			TMR_StartIntervalTimer(myTimerID, /*myTimerID*/
					1000, /* Timer's Timeout */
					myTaskTimerCallback, /* pointer to myTaskTimerCallback function */
					NULL
					);
			TurnOffLeds(); /* Ensure all LEDs are turned off */
			break;
		case gMyNewTaskEvent2_c: /* Event called from myTaskTimerCallback */
			if(!ledsState) {
				TurnOnLeds();
				ledsState = 1;
			}
			else
			{
				TurnOffLeds();
				ledsState = 0;
			}
			break;
		case gMyNewTaskEvent3_c: /* Event to stop the timer */
				ledsState = 0;
				TurnOffLeds();
				TMR_StopTimer(myTimerID);
				break;
		default:
				break;
		}
	}
}

/* Function to init the task */
void MyTask_Init(void)
{
	mMyEvents = OSA_EventCreate(TRUE);
	/* The instance of the MAC is passed at task creaton*/
	gMyTaskHandler_ID = OSA_TaskCreate(OSA_TASK(My_Task), NULL);
}

/* This is the function called by the Timer each time it expires */
static void myTaskTimerCallback(void*param)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent2_c);
}

/* Public function to send an event to stop the timer */
void MyTaskTimer_Stop(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent3_c);
}


