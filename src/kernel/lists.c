#include "include/kernel/lists.h"



int16_t insert_after( tcb * position_tcb, tcb * new_tcb )
{
	int16_t result = -1;

	//	printf("position tcb: %d\n", position_tcb);

	if(position_tcb != NULL && new_tcb != NULL)
	{
		new_tcb->nexttcb = position_tcb->nexttcb;
		new_tcb->prevtcb = position_tcb;
		position_tcb->nexttcb = new_tcb;
		new_tcb->nexttcb->prevtcb = new_tcb;
		
		result = 0;
	}

	return result;
}


int16_t insert_by_priority( tcb * list_head, tcb * new_tcb )
{
	int16_t result = -1;
	tcb * iterator = list_head;

	//	printf("position tcb: %d\n", position_tcb);
	
	if(list_head != NULL && new_tcb != NULL)
	{
		
		while(iterator && iterator->effective_priority <= new_tcb->effective_priority)
		{
			iterator = iterator->nexttcb;
		}

		insert_after(iterator->prevtcb, new_tcb);
		result = 0;
	}

	return result;
}

int16_t insert_by_back_online_time( tcb * list_head, tcb * new_tcb )
{
	int16_t result = -1;
	tcb * iterator = list_head;

	//	printf("position tcb: %d\n", position_tcb);
	
	if(list_head != NULL && new_tcb != NULL)
	{
		
		while(iterator && iterator->back_online_time <= new_tcb->back_online_time)
		{
			iterator = iterator->nexttcb;
		}

		insert_after(iterator->prevtcb, new_tcb);
		result = 0;
	}

	return result;
}