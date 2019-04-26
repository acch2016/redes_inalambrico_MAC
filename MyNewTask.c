/*
 * MyNewTask.c
 *
 *  Created on: Apr 9, 2019
 *      Author: Cursos
 */
/**/
#include "MyNewTask.h"

#define gMyTaskPriority_c 3
#define gMyTaskStackSize_c 400
#define TIMEOUT 3000
static uint8_t interfaceId;
osaEventId_t mMyEvents;
/* Global Variable to store our TimerID */
tmrTimerID_t myTimerID = gTmrInvalidTimerID_c;
/** Handler  ID for task **/
osaTaskId_t gMyTaskHandler_ID;
/** Local variable to store the current state of the LEDs **/
static uint8_t ledsState = 1;
/* OSA Task Definition*/
OSA_TASK_DEFINE(My_Task, gMyTaskPriority_c, 1, gMyTaskStackSize_c, FALSE);

/* Main custom task */
void My_Task(osaTaskParam_t argument)
{
	osaEventFlags_t customEvent;
	myTimerID = TMR_AllocateTimer();
	uint8_t counti[] = "\rCounter: ";

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
					TIMEOUT, /* Timer's Timeout */
					myTaskTimerCallback, /* pointer to myTaskTimerCallback function */
					NULL
					);
			TurnOffLeds(); /* Ensure all LEDs are turned off */
			break;
		case gMyNewTaskEvent2_c: /* Event called from myTaskTimerCallback */
			switch(ledsState)
			{
			case 1:
				TurnOffLeds();
//				Led4Off();
				Led1On();
				App_TransmitData(ledsState);
//				Serial_PrintDec(interfaceId, sizeof(counti));
				break;
			case 2:
				TurnOffLeds();
//				Led1Off();
				Led2On();
				App_TransmitData(ledsState);
				break;
			case 3:
				TurnOffLeds();
//				Led2Off();
				Led3On();
				App_TransmitData(ledsState);
				break;
			case 4:
				TurnOffLeds();
//				Led3Off();
				Led4On();
				App_TransmitData(ledsState);
				ledsState = 0;
				break;
			default:
				break;
			}
			ledsState ++;
			break;
		case gMyNewTaskEvent3_c: /* Event to stop the timer */
				ledsState = 0;
				TurnOffLeds();
				TMR_StopTimer(myTimerID);
				break;

		case gMyNewTaskEvent4_c:
				TMR_StopTimer(myTimerID);
				ledsState = 1;
				TurnOffLeds();
				Led1On();
				App_TransmitData(ledsState);
				ledsState = 2;
				TMR_StartIntervalTimer(myTimerID, /*myTimerID*/
						TIMEOUT, /* Timer's Timeout */
						myTaskTimerCallback, /* pointer to myTaskTimerCallback function */
						NULL
						);
				break;
		case gMyNewTaskEvent5_c:
				TMR_StopTimer(myTimerID);
				ledsState = 2;
				TurnOffLeds();
				Led2On();
				App_TransmitData(ledsState);
				ledsState = 3;
				TMR_StartIntervalTimer(myTimerID, /*myTimerID*/
						TIMEOUT, /* Timer's Timeout */
						myTaskTimerCallback, /* pointer to myTaskTimerCallback function */
						NULL
						);
				break;
		case gMyNewTaskEvent6_c:
				TMR_StopTimer(myTimerID);
				ledsState = 3;
				TurnOffLeds();
				Led3On();
				App_TransmitData(ledsState);
				ledsState = 4;
				TMR_StartIntervalTimer(myTimerID, /*myTimerID*/
						TIMEOUT, /* Timer's Timeout */
						myTaskTimerCallback, /* pointer to myTaskTimerCallback function */
						NULL
						);
				break;
		case gMyNewTaskEvent7_c:
				TMR_StopTimer(myTimerID);
				ledsState = 4;
				TurnOffLeds();
				Led4On();
				App_TransmitData(ledsState);
				ledsState = 1;
				TMR_StartIntervalTimer(myTimerID, /*myTimerID*/
						TIMEOUT, /* Timer's Timeout */
						myTaskTimerCallback, /* pointer to myTaskTimerCallback function */
						NULL
						);
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
void myTaskTimerCallback(void*param)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent2_c);
}

void MyTaskTimer_Start(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent1_c);
}
/* Public function to send an event to stop the timer */
void MyTaskTimer_Stop(void)
{
	OSA_EventSet(mMyEvents, gMyNewTaskEvent3_c);
}


osaEventId_t get_myEvents(void)
{
	return  mMyEvents;
}


