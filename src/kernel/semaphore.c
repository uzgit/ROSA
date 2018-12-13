#include "include/kernel/semaphore.h"

int16_t ROSA_semaphoreCreate(ROSA_semaphoreHandle_t * handle, uint8_t ceiling)
{
	int16_t result = -1;
	
	(*handle) = calloc(1, sizeof(semaphore));
	(*handle)->flag = 0;		// 0 when semaphore is not locked, 1 when semaphore is locked
	(*handle)->ceiling = ceiling;
	(*handle)->current_task = NULL;
	(*handle)->task_priority = 15;
	result = 0;
	return result;
}

int16_t ROSA_semaphoreDelete(ROSA_semaphoreHandle_t handle)
{
	int16_t result = -1;
	if(handle && handle->BLOCKEDLIST == NULL && handle->flag == 0 && handle->current_task == NULL)
	{
		free(handle);
		result = 0;
	}
	return result;
}

int16_t ROSA_semaphorePeek(ROSA_semaphoreHandle_t handle)
{
	return handle->flag;
}

int16_t ROSA_semaphoreLock(ROSA_semaphoreHandle_t handle)
{
	int16_t result = -1;
	if(handle->flag == 0)
	{
		// If the semaphore is not locked, executing task can lock it
		// Task inherits the priority ceiling of the semaphore
		// Dynamic priority of the task is changed if priority of the task is lower than the ceiling of the semaphore
		
		handle->flag = 1;
		handle->current_task = EXECTASK;
		handle->task_priority = EXECTASK->effective_priority;
		if(EXECTASK->effective_priority > handle->ceiling)
		{
			endCritical=0;
			//Reinstalling task because it has higher priority, so the ready list should be rearranged
			ROSA_tcbUninstall(EXECTASK);
			endCritical=1;
			EXECTASK->effective_priority = handle->ceiling; 
			ROSA_tcbInstall(EXECTASK);
		}
		result = 0;
	}
	else if(handle->flag == 1 && !(EXECTASK == handle->current_task))
	{
		// If the semaphore is locked, executing task cannot lock it
		// Task is put into the waiting queue for the specific semaphore
		// Task is also removed from the ready list
		
		//enqueue(& handle->waiting_tasks, EXECTASK);
		endCritical=0;
		ROSA_tcbUninstall(EXECTASK);
		endCritical=1;
		if(handle->BLOCKEDLIST == NULL)
		{
			handle->BLOCKEDLIST=EXECTASK;
			handle->BLOCKEDLIST_end=EXECTASK;
		}
		else
		{
			insert_after(handle->BLOCKEDLIST_end, EXECTASK);
			handle->BLOCKEDLIST_end=EXECTASK;
		}
		result = 0;
		interruptEnable();
		
	}
	else if(handle->flag == 1 && EXECTASK == handle->current_task)
	{
		result = 0;
	}
	ROSA_yield();
	return result;
}

int16_t ROSA_semaphoreUnlock(ROSA_semaphoreHandle_t handle)
{
	int16_t result = -1;
	if(handle->flag == 1)
	{
		// If the semaphore is locked, unlock it, change the priority of the task to the last effective priority
		// Set the pointer to the current task to NULL 
		handle->flag = 0;
		//ROSA_tcbUninstall(EXECTASK);
		handle->current_task->effective_priority = handle->task_priority;
		//ROSA_tcbInstall(EXECTASK);
		handle->current_task = NULL;
		result = 0;	
	}
	else
	{
		// If the semaphore is not locked, do nothing
		result = 0;
	}
	
	if(handle->BLOCKEDLIST!=NULL)
	{
		// If there are still some task waiting to take the semaphore, take the first one from the waiting queue
		// Put the task back to ready list
		
		tcb * temp; 
		//dequeue(& handle->waiting_tasks, &temp);
		temp=handle->BLOCKEDLIST;
		if(handle->BLOCKEDLIST==handle->BLOCKEDLIST_end)
		{
			handle->BLOCKEDLIST=NULL;
			handle->BLOCKEDLIST_end=NULL;
		}
		else
		{
			handle->BLOCKEDLIST=handle->BLOCKEDLIST->nexttcb;
		}
		
		handle->flag = 1;
		handle->current_task = temp;
		handle->task_priority = temp->effective_priority;
		if(temp->effective_priority > handle->ceiling)
		{
			temp->effective_priority = handle->ceiling; 
		}
		ROSA_tcbInstall(temp);
		result = 0;
		ROSA_yield();
	}
	return result;

}