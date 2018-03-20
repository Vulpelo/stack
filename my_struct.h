#pragma once

struct MY_STUDENT
{
	char *nazwisko;
	int rok_urodzenia;
	enum KIERUNEK_STUD kierunek;

	//Dla zapisu-odczytu z pliku
	size_t nazwiskoLen;
};

enum KIERUNEK_STUD
{
	KIERUNEK_INFORMATYKA,
	KIERUNEK_MATEMATYKA,
	KIERUNEK_FIZYKA,
	KIERUNEK_CHEMIA,
	ERROR
};

int KIERUNEK_STUD_NumberOfElements();

void *MY_STUDENT_Init(char *surname, int year, int kier);

void Kierunek_String_Name_Print(int kier);

void MY_STUDENT_WriteToBinaryFile(void * tmp, FILE *out);

void MY_STUDENT_Print(void *data, int j);

void MY_STUDENT_Free(void *stud);
MY_STUDENT *MY_STUDENT_ReadFromBinaryFile(FILE *in, __int64 *fileDesc);
bool MY_STUDENT_Compare(void *data, char *Tsurname, int TbirthYear, int TfieldOfStudy, short typ_szukania);
