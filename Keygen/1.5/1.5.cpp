
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>

int main()
{
	unsigned char key[11];
	unsigned char convert[4];
	int i;
	unsigned int tempDword;
	unsigned char EDIPlus8, EDIPlus9;

	srand((unsigned int)time(0));

start_over:
	for(i = 0; i < 11; i++)
	{
		key[i] = (rand() % 0x5d)+0x21; //0x21=33d; 0x5d=93
	}

	//i=2:5 thi duoc chuyen doi 
	for(i = 0; i < 4; i++)
	{
		convert[i] = key[i+2]+(14-i);
		if(convert[i] > 0x7b)   //0x7b=123d
		{
			convert[i] = convert[i] >> 1;
		}
	}
	tempDword = *(unsigned int*)(convert);

	__asm
	{
		// chuyen doi sang cac so nguyen bcd duoc dong goi 18 chu so
		// va thuc hien them cac thuat toan khac
		pushad;
		push 0;
		push 0;
		mov eax, [tempDword];
		push eax;
		fild qword ptr[esp];
		fbstp [esp];
		pop ecx;
		pop eax;
		pop eax;
		mov edx, ecx;
		shr ecx, 4;
		and edx, 0x0f0f0f0f;
		and ecx, 0x0f0f0f0f;
		add edx, 0x30303030;
		add ecx, 0x30303030;
		
		mov[EDIPlus8], cl;
		mov[EDIPlus9], dl;

		popad;
	}

	key[0] = EDIPlus8;
	key[1] = EDIPlus9;

	// thuc hien nguoc lai cua phep toan ((ax+bx)^0x1b3f)-0x123
	*(unsigned short*)key += 0x1a1c;

	// thuc hien bien doi nguoc
	key[0] -= 16;
	key[1] -= 15;
	if(key[0] < 0x21 || key[1] < 0x21)  //0x21=33
	{
		goto start_over;
	}

	//in ra key gom 11 ky tu sau khi qua cac buoc bien doi
	printf("==> KEY: ");
	for(i = 0; i < 11; i++)
		printf("%c",key[i]);
	printf("\n");

	_getch();
	return 0;
}