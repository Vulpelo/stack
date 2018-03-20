#include "stdafx.h"
#include <string.h>
#include <stdlib.h>

//moje pliki
#include "my_struct.h"
#include "my_stack.h"
#include "my_interface.h"

static MY_STACK *POINTER;
static MY_STACK *NEXT;


void My_Stack_Init()
{
	POINTER = NULL;
	NEXT = NULL;
}
void My_Stack_deleteFirst()
{
	MY_STACK *st;
	NEXT = POINTER;
	if (NEXT != NULL)
	{
		st = NEXT;
		if (st->data)
		{		
			NEXT->Free_Object(NEXT->data); //Przekierowanie do funkcji, która zosta³a zapisana w tej funkcji
		}
		NEXT = NEXT->Next;
		st->Free_Object=NULL;
		free(st);
		POINTER = NEXT;
	}
	else
		printf("--stack is empty--\n");
}

void My_Stack_Free()
{
	NEXT = POINTER;
	while (NEXT != NULL)
		My_Stack_deleteFirst();
}


MY_STACK * My_Stack_Add(void *stud, void (*freefunction)(void *))
{
	NEXT = POINTER;
	POINTER = (MY_STACK *)malloc(sizeof(MY_STACK));
	POINTER->data = stud;
	POINTER->Next = NEXT;
	POINTER->Free_Object = freefunction;

	return POINTER;
}

void *My_Stack_GetOne(int nr)
{
	NEXT = POINTER;
	int j = 1;
	while (j != nr && NEXT != NULL)
	{
		NEXT = NEXT->Next;
		j++;
	}
	if (NEXT != NULL)
		return NEXT->data;
	else
		return NULL;
}

void *My_Stack_GetNext() 
//zwraca dane nastêpnego elementu stosu po elemencie NEXT
//zaczyna siê od zakoñczenia funkcji My_Stack_GetOne() 
//czyli od ostatniej pozycji wskaŸnika NEXT
{
	NEXT = NEXT->Next;
	if (NEXT != NULL)
		return NEXT->data;
	else
		return NULL;
}
int My_Stack_NumberOfElements()
{
	NEXT = POINTER;
	int nr = 0;
	while (NEXT != NULL)
	{
		nr++;
		NEXT = NEXT->Next;
	}
	return nr;
}
