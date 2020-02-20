#pragma once
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <time.h>

char Name[256];
char* NameRev;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Name: ");
	std::cin >> Name;

	NameRev = _strrev(Name);
	DWORD var_44 = 0, var_48 = 0, var_4c = 0, var_50 = 0, out = 0; 
	char buff[256];

	for (int i = 0; i<strlen(Name); i++)
		var_48 -= (NameRev[i] - 0x20); //NameRev[i] - 0x20 = var_44
	//mov     eax, [ebp + var_44]; var_44 = EAX
	//sub     eax, 20h; EAX - 20h 
	//mov[ebp + var_44], eax
	//mov     ecx, [ebp + var_48]; ECX = var_48
	//sub     ecx, [ebp + var_44]; ECX - var44

	sprintf_s(buff, "%X", var_48);
	printf("\nSerial: %s", _strrev(buff));

	srand(time(NULL));	// khoi tao random seed
	int Number = rand() % 5;
	sprintf_s(buff, "%i", Number);
	char cData = buff[0];


	HANDLE hFile = CreateFile(TEXT("RES-REGGED.txt"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(hFile, &cData, sizeof(cData), &out, NULL);
	CloseHandle(hFile);

	hFile = CreateFile(TEXT("RES-VALIDATE.diz"), GENERIC_READ, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile);


	_getch();
	return 0;
}