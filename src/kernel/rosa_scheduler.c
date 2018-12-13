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

#include "kernel/rosa_scheduler.h"
#include "kernel/rosa_ker.h"
#include "kernel/rosa_tim.h"

uint64_t roundRobinTicks = 10;
uint64_t roundRobinCounter = 0;

tcb * ROUNDROBINEND = NULL;

/***********************************************************
 * scheduler
 *
 * Comment:
 * 	Minimalistic scheduler for round robin task switch.
 * 	This scheduler choose the next task to execute by looking
 * 	at the nexttcb of the current running task.
 **********************************************************/
void scheduler(void)
{
	endCritical = 0;
	//interruptDisable();
	
	if(roundRobinTicks != 0 && ROUNDROBINEND != NULL && EXECTASK->effective_priority == ROUNDROBINEND->effective_priority && (idle_task_handle != EXECTASK))
	{
		roundRobinCounter++;
		if(roundRobinCounter >= roundRobinTicks)
		{
			roundRobinCounter = 0;
			insert_after(ROUNDROBINEND, EXECTASK);
			ROUNDROBINEND = EXECTASK;
		}
	}
	
	tcb * iterator = SUSPENDEDLIST;
	uint64_t current_time = ROSA_getTickCount();
	while( iterator != NULL && iterator->back_online_time <= current_time ) //for every suspended task that is now ready
	{
		ROSA_tcbUnsuspend(iterator);
		ROSA_tcbInstall(iterator);
		iterator = SUSPENDEDLIST;
	}

	//Find the next task to execute
	//EXECTASK = EXECTASK->nexttcb;
	
	EXECTASK=TCBLIST;
	endCritical = 1;
	//interruptEnable();
}
