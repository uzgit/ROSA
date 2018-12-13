/*****************************************************************************

                 ,//////,   ,////    ,///' /////,
                ///' ./// ///'///  ///,    ,, //
               ///////,  ///,///   '/// //;''//,
             ,///' '///,'/////',/////'  /////'/;,

    Copyright 2010 Marcus Jansson <mjansson256@yahoo.se>

    This file is part of ROSA - Realtime Operating System for AVR32.

    ROSA is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ROSA is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ROSA.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/
/* Tab size: 4 */

#ifndef _ROSA_KER_H_
#define _ROSA_KER_H_

#include "rosa_def.h"
#include <stdint.h>

/***********************************************************
 * Global variables
 ***********************************************************/
//extern tcb * TCBLIST;
extern tcb * EXECTASK;
tcb * TCBLIST;
tcb * TCBLIST_end;

tcb * SUSPENDEDLIST;
tcb * SUSPENDEDLIST_end;

ROSA_taskHandle_t idle_task_handle;

//Variable that defines whether critical section should end at the end of critical API functions
extern int endCritical;


/***********************************************************
 * Kernel low level context switch functions
 ***********************************************************/
extern void ROSA_contextInit(tcb * tcbTask);
extern void ROSA_yield(void);


/***********************************************************
 * Other kernel functions
 ***********************************************************/
//None

/***********************************************************
 * General kernel API
 *
 * Comment:
 *	No comments available.
 *
 **********************************************************/

//Define the initial value of the satus register
#define ROSA_INITIALSR 0x1c0000

//Timer interrupt service routine
__attribute__((__interrupt__)) extern void timerISR(void);

//Initialize the kernel
void ROSA_init(void);
void ROSA_tcbCreate(tcb * tcbTask, char tcbName[NAMESIZE], void *tcbFunction, int * tcbStack, int tcbStackSize);

//Install a new task TCB into ROSA
extern void ROSA_tcbInstall(tcb * tcbTask); //used to be 'task' instead of 'tcbTask'
void ROSA_tcbUninstall(tcb * tcbTask);

void ROSA_tcbSuspend(tcb * tcbTask);
void ROSA_tcbUnsuspend(tcb * tcbTask);

int16_t ROSA_taskCreate(ROSA_taskHandle_t * th, char * id, void * taskFunc, uint32_t stackSize, uint8_t priority);
int16_t ROSA_taskDelete(ROSA_taskHandle_t th);

//delay functions
int16_t ROSA_delay(uint64_t ticks);
int16_t ROSA_delayUntil(uint64_t* lastWakeTime, uint64_t ticks);
int16_t ROSA_delayAbsolute(uint64_t ticks);

//Start running the ROSA kernel
//This start running the created and installed tasks.
extern void ROSA_start(void);

#endif /* _ROSA_KER_H_ */
