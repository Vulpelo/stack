#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

//moje pliki
#include "my_mess.h"
#include "my_struct.h"
#include "my_stack.h"

#pragma warning (disable : 4996)

static char *Kierunek_Stud_name_tab[] = {
	"Informatyka",
	"Matematyka",
	"Fizyka",
	"Chemia",
	"-!-ERROR-!-"
};
static KIERUNEK_STUD Kierunek(int nr)
{
	switch (nr)
	{
	case KIERUNEK_INFORMATYKA:
		return KIERUNEK_INFORMATYKA;
	case KIERUNEK_MATEMATYKA:
		return KIERUNEK_MATEMATYKA;
	case KIERUNEK_FIZYKA:
		return KIERUNEK_FIZYKA;
	case KIERUNEK_CHEMIA:
		return KIERUNEK_CHEMIA;
	default:
		return ERROR;
	}
}

int KIERUNEK_STUD_NumberOfElements()
{
	return sizeof(Kierunek_Stud_name_tab)/sizeof(*Kierunek_Stud_name_tab);
}
// Drukuje nazwe kierunku (w postaci tekstu)
void Kierunek_String_Name_Print(int kier)
{
	for (size_t i = 0; i < strlen(Kierunek_Stud_name_tab[kier]); i++)
		printf("%c", Kierunek_Stud_name_tab[kier][i]);
}

void *MY_STUDENT_Init(char *surname, int year, int kier)
{
	KIERUNEK_STUD kierun = Kierunek(kier);

	MY_STUDENT *stud = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));
	if (!stud)
	{
		if(my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_ERROR(stud, NULL, NULL, NULL);
	}
	else
	{
		stud->nazwisko = surname;
		stud->rok_urodzenia = year;
		stud->kierunek = kierun;
		stud->nazwiskoLen = strlen(stud->nazwisko) + 1;
	}
	return (void *)(stud);
}

void MY_STUDENT_WriteToBinaryFile(void * tmp, FILE *out)
{
	if (out)
	{
		MY_STUDENT *stud = (MY_STUDENT *)tmp;

		if(fwrite(stud, sizeof(MY_STUDENT), 1, out) < 1)
			if (my_mess_fun(MY_MESS_WRITE_TO_FILE) == MY_DECISION_BREAK)
				my_mess_ERROR(NULL, NULL, NULL, out);

		if(fwrite(stud->nazwisko, (size_t)(stud->nazwiskoLen), 1, out) < 1)
			if (my_mess_fun(MY_MESS_WRITE_TO_FILE) == MY_DECISION_BREAK)
				my_mess_ERROR(NULL, NULL, NULL, out);
	
	}
}

MY_STUDENT *MY_STUDENT_ReadFromBinaryFile(FILE *in, __int64 *fileDesc)
{
	MY_STUDENT *tmp = (MY_STUDENT *)malloc(sizeof(MY_STUDENT));
	if (!tmp)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_ERROR(tmp, NULL, fileDesc, in);


	if(fread(tmp, sizeof(MY_STUDENT), 1, in) < 1)
		if (my_mess_fun(MY_MESS_READ_FROM_FILE) == MY_DECISION_BREAK)
			my_mess_ERROR(tmp, NULL, fileDesc, in);

	tmp->nazwisko = (char *)malloc(tmp->nazwiskoLen * sizeof(char));
	if (!tmp->nazwisko)
	{
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_ERROR(tmp, NULL, fileDesc, in);
	}

	if(fread(tmp->nazwisko, tmp->nazwiskoLen, 1, in) < 1)
		if (my_mess_fun(MY_MESS_READ_FROM_FILE) == MY_DECISION_BREAK)
			my_mess_ERROR(tmp, NULL, fileDesc, in);

	return tmp;
}

void MY_STUDENT_Print(void *data, int j) //Wyúwietla tytu≥ jeøeli j>=0
{
	MY_STUDENT *stud = (MY_STUDENT *)data;
	if(j >= 0)
		printf("\n-=Element nr %d=-\n", j);
	printf("Nazwisko: %s", stud->nazwisko);
	printf("\nRok urodzenia: %d\n", stud->rok_urodzenia);
	printf("Kierunek: ");
	Kierunek_String_Name_Print(stud->kierunek);
	printf("\n\n");
}

bool MY_STUDENT_Compare(void *data, char *Tsurname, int TbirthYear, int TfieldOfStudy, short typ_szukania)
{
	/*short typ_szukania :
	0-Po nazwisku, roku, kierunku === 1-Po nazwisku, roku === 2-Po nazwisku, kierunku ===
	3-Po Nazwisku === 4-Po roku, kierunku === 5-Po Roku === 6-Po Kierunku === 7--brak-

	typ_szukania < 4		-Po Nazwisku
	typ_szukania%4 <2 		-Po Roku
	typ_szukania%2 == 0 	-Po Kierunku
	*/
	bool foundSurname = false;
	bool foundYear = false;
	bool foundKier = false;
	
	MY_STUDENT *stud = (MY_STUDENT *)data;
	//sprawdzanie nazwiska
	if (typ_szukania < 4)
	{
		foundSurname = true;
		for (size_t i = 0; i < strlen(stud->nazwisko); i++)
			if (Tsurname[i] != stud->nazwisko[i])
			{
				foundSurname = false;
				break;
			}
	}

	//sprawdzanie roku
	if (typ_szukania % 4 <2)
		if (stud->rok_urodzenia == TbirthYear)
			foundYear = true;
	
	//sprawdzanie kierunku
	if (typ_szukania % 2 == 0)
		if (stud->kierunek == TfieldOfStudy)
			foundKier = true;


	//wyrzucanie wyniku
	if (((typ_szukania < 4) == foundSurname) && ((typ_szukania % 4 <2) == foundYear) && ((typ_szukania % 2 == 0) == foundKier))
		return true;
	else
		return false;
}

void MY_STUDENT_Free(void *stud)
{
	if (stud != NULL)
	{
		MY_STUDENT *studi = (MY_STUDENT *)stud;
		//czyszcze dynamiczne nazwisko
		if(studi->nazwisko)
			free(studi->nazwisko);
		studi->nazwisko = NULL;

		//czyszcze wskaünik do struktury
		if(studi)
			free(studi);
		studi = NULL;
	}
}
