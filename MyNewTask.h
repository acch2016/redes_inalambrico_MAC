/*
 * MyNewTask.h
 *
 *  Created on: Apr 9, 2019
 *      Author: Cursos
 */

#ifndef MYNEWTASK_H_
#define MYNEWTASK_H_

/* Fwk*/
#include "TimersManager.h"
#include "FunctionLib.h"
#include "LED.h"
/* KSDK */
#include "fsl_common.h"
#include "EmbeddedTypes.h"
#include "fsl_os_abstraction.h"
#include "SerialManager.h"
//#include <stdint.h>
#include "mwa_end_device.h"
/* Define the available Task's Events */
#define gMyNewTaskEvent1_c (1 << 0)
#define gMyNewTaskEvent2_c (1 << 1)
#define gMyNewTaskEvent3_c (1 << 2)

#define gMyNewTaskEvent4_c (1 << 3)
#define gMyNewTaskEvent5_c (1 << 4)
#define gMyNewTaskEvent6_c (1 << 5)
#define gMyNewTaskEvent7_c (1 << 6)

//c.Define a TASK PRIORITY and TASK SIZE for your new task
#define gMyTaskPriority_c 3
#define gMyTaskStackSize_c 400
//d.Prototype definition
void MyTaskTimer_Start(void);
void MyTaskTimer_Stop(void);
void MyTask_Init(void);

void My_Task(osaTaskParam_t argument);
void myTaskTimerCallback(void*param);
//static void App_TransmitData(void);
osaEventId_t get_myEvents(void);

#endif /* MYNEWTASK_H_ */
