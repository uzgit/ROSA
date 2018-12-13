#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include "include/kernel/queue.h"
#include "include/kernel/rosa_ker.h"

typedef struct
{
	int16_t flag;
	uint8_t ceiling;
	tcb * current_task;
	uint8_t task_priority;
	tcb * BLOCKEDLIST;
	tcb * BLOCKEDLIST_end;
} semaphore;

#define ROSA_semaphoreHandle_t semaphore*

int16_t ROSA_semaphoreCreate(ROSA_semaphoreHandle_t * handle, uint8_t ceiling);
int16_t ROSA_semaphoreDelete(ROSA_semaphoreHandle_t handle);
int16_t ROSA_semaphorePeek(ROSA_semaphoreHandle_t handle);
int16_t ROSA_semaphoreLock(ROSA_semaphoreHandle_t handle);
int16_t ROSA_semaphoreUnlock(ROSA_semaphoreHandle_t handle);




#endif /* SEMAPHORES_H_ */