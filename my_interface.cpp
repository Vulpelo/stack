#include "stdafx.h"
#include "stdlib.h"
#include "string.h"

//Moje pliki
#include "my_interface.h"
#include "my_stack.h"
#include "my_struct.h"
#include "my_mess.h"

#pragma warning (disable : 4996)

//print
void MY_INTERFACE_Menu()
{
	int k, l;	
	while (1)
	{
		printf("\n=======Ilosc elementow stosu: %d==========", My_Stack_NumberOfElements());
		printf("\n=Menu=====================================\n");
		printf("1-Dodaj studenta do 'stosu'\n");
		printf("2-Usun\n");
		printf("3-Wyszukaj\n");
		printf("4-Wyswietl\n");
		printf("5-Zapisz 'stos' do pliku binarnego\n");
		printf("6-Wczytaj 'stos' z pliku binarnego\n");
		printf("9-Zamknij\n");
		printf("------------------------------------------\n>");
		k = scanf_s("%d", &l);
		while (getchar() != '\n'); // Wyczyszcza dodatkowe znaki
		switch (l)
		{
		case 1:
			MY_INREFACE_AddStudent();
			break;
		case 2:
			MY_INTERFACE_Print_Delete();
			break;
		case 3:
			MY_INTERFACE_Find();
			break;
		case 4:
			MY_INTERFACE_Print();
			break;
		case 5:
			MY_INTERFACE_WriteToBinaryFile();
			break;
		case 6:
			MY_INTERFACE_ReadFromBinaryFile();
			break;
		case 9:
			return;
		default:
			my_mess_fun(MY_MESS_WRONG_ENTERED_DATA_WARN);
		}
	};
}

//1
static void MY_INREFACE_AddStudent()
{
	int year;
	//====Nazwisko=====//
	size_t len_text = 5;
	char *text = (char *)malloc(len_text * sizeof(char)); 
	if(!text)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_ERROR(NULL, text, NULL, NULL);
	
	printf("Nazwisko: ");
	int c;
	int dl = 0;
	while ((c = getchar()) != '\n')
	{
		if (dl< len_text - 1)
			text[dl] = c;
		else // Powiekszanie tablicy
		{
			len_text = len_text + 5;
			text = (char *)realloc(text, len_text * sizeof(char));
			if (!text)
				if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
					my_mess_ERROR(NULL, text, NULL, NULL);
			text[dl] = c;
		}
		dl++;
	}
	text[dl] = '\0';
	//ewentualne czyszczenie nadmiaru tablicy
	if (dl < len_text - 1)
	{
		len_text = dl + 1;
		text = (char *)realloc(text, len_text * sizeof(char));
		if (!text)
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				my_mess_ERROR(NULL, text, NULL, NULL);
	}

	printf("Rok urodzenia: ");
	scanf_s("%d", &year);

	//czyszczenie dodatkowych nieprzeczytanych znakow
	while ((c = getchar()) != '\n');

	printf("Kierunek:(Wprowadz odpowiednia cyfre)\n");
	MY_INTERFACE_PrintAllFieldOfStudy();
	while (scanf_s("%d", &dl) <= 0 || dl < 0 || dl > KIERUNEK_STUD_NumberOfElements() - 2)
	{
		while ((c = getchar()) != '\n'); // Wyczyszcza dodatkowe znaki
		my_mess_fun(MY_MESS_WRONG_ENTERED_DATA_WARN);
		printf("Kierunek:(Wprowadz odpowiednia cyfre)\n");
		MY_INTERFACE_PrintAllFieldOfStudy();
	}
	if (! My_Stack_Add(MY_STUDENT_Init(text, year, dl), MY_STUDENT_Free))
	{
		my_mess_fun(MY_MESS_STACK_PUSH_WARNING);
	}
}

//2
//print
static void MY_INTERFACE_Print_Delete()
{
	int k, l;
	while (1)
	{
		printf("\n=Menu->Usun===============================\n");
		printf("1-Pierwszego studenta (Pierwszy element 'stosu')\n");
		printf("2-Wszystkich studentow (Caly 'stos')\n");
		printf("9-Cofnij\n");
		printf("------------------------------------------\n>");
		k = scanf_s("%d", &l);
		while (getchar() != '\n'); // Wyczyszcza dodatkowe znaki

		switch (l)
		{
		case 1:
			MY_INTERFACE_DeleteFirst();
			return;
		case 2:
			MY_INTERFACE_DeleteAll();
			return;
		case 9:
			return;
		default:
			my_mess_fun(MY_MESS_WRONG_ENTERED_DATA_WARN);
		}
	};
}
static void MY_INTERFACE_DeleteFirst()
{
	My_Stack_deleteFirst();
}
static void MY_INTERFACE_DeleteAll()
{
	My_Stack_Free();
	printf("-Wyczyszczono stos-\n");
}

//3
//print
static void MY_INTERFACE_Find()
{
	int k, l;
	while (1)
	{
		printf("\n=Menu->Wyszukaj===========================\n");
		printf("1-Po nazwisku\n");
		printf("2-Po roku urodzenia\n");
		printf("3-Po kierunku\n");
		printf("9-Cofnij\n");
		printf("-------------------------------------------\n>");

		k = scanf_s("%d", &l);
		while (getchar() != '\n'); // Wyczyszcza dodatkowe znaki

		switch (l)
		{
		case 1:
			MY_INTERFACE_FindBySurname();
			return;
		case 2:
			MY_INTERFACE_FindByBirthYear();
			return;
		case 3:
			MY_INTERFACE_FindByFieldOfStudy();
			return;
		case 9:
			return;
		default:
			my_mess_fun(MY_MESS_WRONG_ENTERED_DATA_WARN);
		}

	};
}
static void MY_INTERFACE_FindBySurname()
{
	size_t len_text = 5;
	char *text = (char *)malloc(len_text * sizeof(char)); 
	if (!text)
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_ERROR(NULL, text, NULL, NULL);


	printf("Szukane nazwisko: ");
	int c;
	int dl = 0;
	while ((c = getchar()) != '\n')
	{
		if (dl< len_text - 1)
			text[dl] = c;
		else // Powiekszanie tablicy
		{
			len_text = len_text + 5;
			text = (char *)realloc(text, len_text * sizeof(char));
			if (!text)
				if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
					my_mess_ERROR(NULL, text, NULL, NULL);

			text[dl] = c;
		}
		dl++;
	}
	text[dl] = '\0';
	//ewentualne czyszczenie nadmiaru tablicy
	if (dl < len_text - 1)
	{
		len_text = dl + 1;
		text = (char *)realloc(text, len_text * sizeof(char));
		if (!text)
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				my_mess_ERROR(NULL, text, NULL, NULL); //Wykrywanie b³êdu
	}


	void *tmp;
	int nr = 1;
	bool found = false, foundAny = false;
	while ((tmp = My_Stack_GetOne(nr)) != NULL)
	{
		if (MY_STUDENT_Compare(tmp, text, -1, -1, 3))
		{
			foundAny = true;
			MY_STUDENT_Print(tmp, nr);
		}
		nr++;
	}
	if (foundAny == false)
		printf("-Nie znaleniono studenta o podanym nazwisku-\n");

	if (text)
		free(text);
	text = NULL;
}
static void MY_INTERFACE_FindByBirthYear()
{
	int rok, c, k;
	printf("Szukany rok urodzenia: ");
	while (k = scanf_s("%d", &rok) <= 0)
	{
		while ((c = getchar()) != '\n'); // Wyczyszcza dodatkowe znaki
		my_mess_fun(MY_MESS_WRONG_ENTERED_DATA_WARN);
		printf("\nSzukany rok urodzenia: ");
	}
	while ((c = getchar()) != '\n'); // Wyczyszcza dodatkowe znaki

	void *tmp;
	int nr = 1;
	bool foundAny = false;
	while ((tmp = My_Stack_GetOne(nr)) != NULL)
	{
		if (MY_STUDENT_Compare(tmp, "", rok, -1, 5))
		{
			foundAny = true;
			MY_STUDENT_Print(tmp, nr);
		}
		nr++;
	}
	if (foundAny == false)
		printf("Nie znaleniono studenta o podanym roku urodzenia\n");
}
static void MY_INTERFACE_FindByFieldOfStudy()
{
	int c, kier;
	printf("Szukany kierunek:(wprowadz odpowiednia cyfre)\n");
	MY_INTERFACE_PrintAllFieldOfStudy();
	while (c = scanf_s("%d", &kier) <= 0 || kier < 0 || kier > KIERUNEK_STUD_NumberOfElements() - 2)
	{
		while ((c = getchar()) != '\n'); // Wyczyszcza dodatkowe znaki
		my_mess_fun(MY_MESS_WRONG_ENTERED_DATA_WARN);
		printf("Szukany kierunek:(wprowadz odpowiednia cyfre)\n");
		MY_INTERFACE_PrintAllFieldOfStudy();
	}

	while ((c = getchar()) != '\n'); // Wyczyszcza dodatkowe znaki
	
	void *tmp;
	int nr = 1;
	bool foundAny = false;
	while ((tmp = My_Stack_GetOne(nr)) != NULL)
	{
		if (MY_STUDENT_Compare(tmp, "", 0, kier, 6))
		{
			foundAny = true;
			MY_STUDENT_Print(tmp, nr);
		}
		nr++;
	}
	if (foundAny == false)
		printf("-Nie znaleniono studenta na podanym kierunku-\n");
}


//4
//print
static void MY_INTERFACE_Print()
{
	int k, l;
	while (1)
	{
		printf("\n=Menu->Wyswietl===========================\n");
		printf("1-Pierwszy element 'stosu'\n");
		printf("2-Wszystkiech studentow (Caly 'stos')\n");
		printf("9-Cofnij\n");
		printf("------------------------------------------\n>");
		k = scanf_s("%d", &l);
		while (getchar() != '\n'); // Wyczyszcza dodatkowe znaki

		switch (l)
		{
		case 1:
			MY_INTERFACE_PrintFirstStudent();
			return;
		case 2:
			MY_INTERFACE_PrintAllStudents();
			return;
		case 9:
			return;
		default:
			my_mess_fun(MY_MESS_WRONG_ENTERED_DATA_WARN);
		}
	};
}
static void MY_INTERFACE_PrintFirstStudent()
{
	void *tmp;

	if ((tmp = My_Stack_GetOne(1)) != NULL)
		MY_STUDENT_Print(tmp, 1);
	else
		printf("\n--Element nr %d nieistnieje--\n", 1);
}
static void MY_INTERFACE_PrintAllStudents()
{
	void *tmp;
	int nr=1;
	printf("\n======Zawartosc stosu======\n");
	tmp = My_Stack_GetOne(nr);
	while(tmp != NULL)
	{
		MY_STUDENT_Print(tmp, nr);

		tmp = My_Stack_GetNext();
		nr++;
	};
	if (nr == 1)
	{
		printf("-Stos jest pusty-\n\n");
	}
}

//5 
static void MY_INTERFACE_WriteToBinaryFile()
{
	void *tmp;
	unsigned int number = My_Stack_NumberOfElements();

	FILE *out;

	if ((out = fopen("Out.bin", "wb")) == NULL) //zapis binarny
	{
		if (my_mess_fun(MY_MESS_FILE_NOT_CREATED_ERROR) == MY_DECISION_BREAK)
		{
			exit(2); 
		}
	}

	unsigned int dodano = 0;//liczy ilosc elementow zapisanych do pliku
	//ustawianie wielkoœci tablicy (tablica z wielkosciami poszczególnych objektów)
	__int64 *fileDesc = (__int64 *)malloc((number + 1) * sizeof(__int64));
	if (!fileDesc)
	{
		if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
			my_mess_ERROR(NULL, NULL, fileDesc, out);
	}
	else
	{
		//wielkoœci tablicy fileDesc
		if(fwrite(&number, sizeof(unsigned int), 1, out) < 1)
			if (my_mess_fun(MY_MESS_WRITE_TO_FILE) == MY_DECISION_BREAK)
				my_mess_ERROR(NULL, NULL, fileDesc, out);
		//rezerwowanie miejsca na pocz¹tku pliku dla fileDesc
		_fseeki64(out, (number + 1) * sizeof(__int64), SEEK_CUR);

		tmp = My_Stack_GetOne(1);
		for (dodano = 0; dodano<number && tmp != NULL; dodano++)
		{
			//zapisywanie do fileDesc aktualnej pozycji wskaŸnika w pliku
			fileDesc[dodano] = ftell(out);
			
			MY_STUDENT_WriteToBinaryFile(tmp, out);

			tmp = My_Stack_GetNext();
		}
		fileDesc[number] = ftell(out);
		//zapisywanie fileDesc do zarezerwowanego miejsca w pliku

		_fseeki64(out, sizeof(unsigned int), SEEK_SET);

		if(fwrite(fileDesc, sizeof(__int64), number + 1, out) < number + 1 )
			if (my_mess_fun(MY_MESS_WRITE_TO_FILE) == MY_DECISION_BREAK)
				my_mess_ERROR(NULL, NULL, fileDesc, out);
	}
	if(out)
		fclose(out);
	out = NULL;
	if (fileDesc)
		free(fileDesc);
	fileDesc = NULL;
	printf("\n--zapisano %d elementow stosu do pliku \"Out.bin\"--\n", dodano);
}

//6
static void MY_INTERFACE_ReadFromBinaryFile()
{
	FILE *in;
	MY_STUDENT *tmp = NULL;

	if (((in = fopen("Out.bin", "rb")) == NULL))
	{
		my_mess_fun(MY_MESS_FILE_NOT_OPENED_WARN);
	}
	else
	{
		int dodano = 0; //liczy ilosc elementow wczytanych z pliku (tylko dla informacji)
		__int64 *fileDesc = NULL;
		unsigned int ilElem = 0;

		//wczytywanie wielkosci tablicy fileDesc
		if(fread(&ilElem, sizeof(unsigned int), 1, in) < 1)
		if (my_mess_fun(MY_MESS_READ_FROM_FILE) == MY_DECISION_BREAK)
			my_mess_ERROR(NULL, NULL, fileDesc, in);

		fileDesc = (__int64 *)malloc((ilElem + 1) * sizeof(__int64));

		if (!fileDesc)
		{
			if (my_mess_fun(MY_MESS_MEM_ALOC_ERROR) == MY_DECISION_BREAK)
				my_mess_ERROR(NULL, NULL, fileDesc, in);
		}
		else
		{
			//wczytywanie tablicy fileDesc
			if(fread(fileDesc, sizeof(__int64), ilElem + 1, in) < ilElem + 1)
				if (my_mess_fun(MY_MESS_READ_FROM_FILE) == MY_DECISION_BREAK)
					my_mess_ERROR(NULL, NULL, fileDesc, in);

			for (unsigned int i = 0; i < ilElem; i++)
			{
				//wymagane do odczytywania pliku od ty³u
				unsigned int nrElementu = ilElem - i - 1;
				_fseeki64(in, fileDesc[nrElementu], SEEK_SET);

				tmp = MY_STUDENT_ReadFromBinaryFile(in, fileDesc);
				
				My_Stack_Add(tmp, MY_STUDENT_Free);

				tmp = NULL;
				dodano++;
			}
		}

		fclose(in);
		printf("\n--wczytano %d elementow stosu z pliku \"Out.bin\"--\n", dodano);
	}
}

//Helping functions
static void MY_INTERFACE_PrintAllFieldOfStudy()
{
	for (int i = 0; i < KIERUNEK_STUD_NumberOfElements() - 1; i++)
	{
		printf("%d- ", i);
		Kierunek_String_Name_Print(i);
		printf(" ; ");
	}
	printf("\n");
}
