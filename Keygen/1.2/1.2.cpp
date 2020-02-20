#include <iostream>
#include <string>
#include <time.h>
using namespace std;

int main()
{
	srand(time(NULL));
	int number = rand() % 9000 + 1000;
	
	cout << "Phat sinh ID tu dong: ";
	cout << number << endl;
	
	//Bat dau phat sinh key tu ID
	//EBX + 4C + 1 + 38B  = EBX + 984
	number += 984;
	//EBX = EBX + EBX
	number += number;
	//Nhan EBX voi 3
	number *= 3;
	//Tru EBX di 1
	number -= 1;
	cout << "Serial Key la: ";
	cout << number << endl;
	system("pause");
}