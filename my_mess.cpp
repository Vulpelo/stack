#include "stdafx.h"
#include <stdlib.h>

//moje pliki
#include "my_mess.h"
#include "my_stack.h"

static char *my_message_str_tab[] = {
	"E--memory allocation error--",			//MY_MESS_MEM_ALOC_ERROR
	"W--wrong data entered--",				//MY_MESS_WRONG_ENTERED_DATA_WARN
	"W--file couldn't be opened--",			//MY_MESS_FILE_NOT_OPENED_WARN
	"E--file couldn't be created--",		//MY_MESS_FILE_NOT_CREATED_ERROR
	"W--data couldn't be pushed to stack--",//MY_MESS_STACK_PUSH_WARNING
	"E--data not written to file--",		//MY_MESS_WRITE_TO_FILE
	"E--data not read from file--"			//MY_MESS_READ_FROM_FILE
};

MY_DECISION my_mess_fun(enum MY_MESSAGES mess)
{
	MY_DECISION retval = MY_DECISION_CONTINUE;

	puts(my_message_str_tab[mess] + 1);

	if (my_message_str_tab[mess][0] == 'E')
		retval = MY_DECISION_BREAK;

	return retval;
}

void my_mess_ERROR(struct MY_STUDENT *st, char *t, __int64 *inti, FILE *fil)
{
	if (fil)
	{
		fclose(fil);
	}
	if (t)
	{
		free(t);
		t = NULL;
	}
	if (st)
	{
		if (st->nazwisko)
			free(st->nazwisko);
		st->nazwisko = NULL;
		free(st);
		st = NULL;
	}
	if (inti)
	{
		free(inti);
		inti = NULL;
	}

	My_Stack_Free();
	system("pause");
	exit(1);
}
