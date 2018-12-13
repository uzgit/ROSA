#include <stdio.h>
#include <stdint.h>
#include "rosa_def.h"

#ifndef LISTS_H_
#define LISTS_H_

#define taskHandle node

typedef struct
{
	tcb * head;
	tcb * tail;
} linked_list;

int16_t insert_at_head( linked_list *, tcb *);
int16_t insert_by_priority( tcb *, tcb *);			//insert_by_priority(TCBLIST, new_task);
int16_t insert_by_back_online_time(tcb *, tcb*);	//insert_by_back_online_time(SUSPENDEDLIST, new_task);
int16_t insert_after( tcb *, tcb *);
int16_t remove_tcb(tcb *,  tcb *);

void print_list(linked_list *);



#endif /* LISTS_H_ */