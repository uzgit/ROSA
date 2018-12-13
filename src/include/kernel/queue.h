#include <stdlib.h>
#include "kernel/rosa_def.h"

#ifndef QUEUE_H
#define QUEUE_H

#define CAPACITY 10

typedef struct
{
	tcb * tasks[CAPACITY];
	unsigned int head;
	unsigned int tail;
	unsigned int size;
} queue;

uint16_t init_queue(queue *);
uint16_t is_empty(queue * queue_pointer);
uint16_t enqueue(queue *, tcb *);
uint16_t dequeue(queue *, tcb **);
void print_queue(queue *);

#endif