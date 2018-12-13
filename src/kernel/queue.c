#include "include/kernel/queue.h"
#include <stdio.h>

uint16_t init_queue( queue * queue_pointer )
{
	uint16_t result = -1;

	if( queue_pointer == NULL )
	{
		queue_pointer->head = 0;
		queue_pointer->tail = 0;
		queue_pointer->size = 0;

		result = 0;
	}

	return result;
}

uint16_t is_empty(queue * queue_pointer)
{ return (( queue_pointer != NULL ) && (queue_pointer->size == 0)); }

uint16_t enqueue( queue * queue_pointer, tcb * task )
{
	uint16_t result = -1;

	if( queue_pointer != NULL && !( queue_pointer->size == CAPACITY ) && task != NULL)
	{
		queue_pointer->tasks[queue_pointer->tail] = task;
		queue_pointer->tail = (queue_pointer->tail + 1) % CAPACITY;
		queue_pointer->size ++;

		result = 0;
	}

	return result;
}

uint16_t dequeue( queue * queue_pointer, tcb ** task )
{
	uint16_t result = -1;

	if( queue_pointer != NULL && !( queue_pointer->size == 0 ) )
	{
		task = &queue_pointer->tasks[queue_pointer->head];
		queue_pointer->head = (queue_pointer->head + 1) % CAPACITY;
		queue_pointer->size --;

		result = 0;
	}

	return result;
}

void print_queue(queue * queue_pointer)
{

	tcb * iterator;
	int effective_index;
	
	int index;
	for(index = 0; index < queue_pointer->size; index ++)
	{
		effective_index = (queue_pointer->head + index) % CAPACITY;
		iterator = queue_pointer->tasks[effective_index];
		printf("%d ", iterator->priority);
	}
	printf("\n");
}