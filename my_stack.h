#pragma once

#include "my_struct.h"

typedef void(*freeObject)(void *); //definicja funkcji do której mo¿e byæ zapisany adres innej funkcji

struct MY_STACK
{
	void *data;
	MY_STACK *Next;

	//funkcja do której mo¿e byæ zapisana inna funkcja (W tym programie to MY_STUDENT_Free)
	//to miejsce na funkcjê do czyszczenia objektu void *data.
	freeObject Free_Object; 
};


void My_Stack_Init();
void My_Stack_deleteFirst();


void My_Stack_Free();
MY_STACK * My_Stack_Add(void *stud, void (*freefunction)(void *));

void *My_Stack_GetOne(int nr);
void *My_Stack_GetNext();

int My_Stack_NumberOfElements();
