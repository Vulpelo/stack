// Stos.cpp : Defines the entry point for the console application.
/*==================================================================================
Zadanie projektowe: Stwórz obs³ugê struktury danych "stos".
Autor:	Damian Praski, I Rok 2 Semestr Studiów na Politechnice Krakowskiej
		Wydzia³ Fizyki Matematyki i Informatyki, Kierunek Informatyka
====================================================================================
*/
#include "stdafx.h"

//moje pliki
#include "my_stack.h"
#include "my_interface.h"


int main()
{
	My_Stack_Init();

	MY_INTERFACE_Menu();

	My_Stack_Free();
    return 0;
}