#pragma once

enum MY_MESSAGES
{
	MY_MESS_MEM_ALOC_ERROR,					 //0
	MY_MESS_WRONG_ENTERED_DATA_WARN,		 //1	
	MY_MESS_FILE_NOT_OPENED_WARN,			 //2
	MY_MESS_FILE_NOT_CREATED_ERROR,			 //3
	MY_MESS_STACK_PUSH_WARNING,				 //4
	MY_MESS_WRITE_TO_FILE,					 //5
	MY_MESS_READ_FROM_FILE,					 //6
	MY_MESS_TOTAL						     //ZAWSZE OSTATNI !!!
};

enum MY_DECISION
{
	MY_DECISION_BREAK,			//Przerywamy wykonanie programu
	MY_DECISION_CONTINUE        //Kontynujemy wykonanie
};

enum MY_DECISION my_mess_fun(enum MY_MESSAGES mess);

//bool my_mess_realloc_malloc_char_tab_error(char *t);
//bool my_mess_realloc_malloc_MY_STUDENT_error(struct MY_STUDENT *t);
void my_mess_ERROR(struct MY_STUDENT *st, char *t, __int64 *inti, FILE *fil);