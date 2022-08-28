#include <iostream>
#include <stdio.h>
#include <time.h>
#include "windows.h"
//#include "MyClass.h"  //неявное подклюение DLL
using namespace std;

int main()
{

	setlocale(LC_ALL, "Rus");
	cout << "Задание: Требуется реализовать структуру данных\n«ассоциативный массив», используя связный список." << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;

	//явно подключаем DLL
	HMODULE hModule;
	hModule = LoadLibrary(L"MyDLL.dll");

	int key = 0;
	string name;

	//для удобства получения функций из DLL
	typedef int (*funcAdd)(int key, string name);
	typedef int (*funcOut)();
	typedef int (*funcFind)(int key);
	typedef int (*funcDel)(int key);
	typedef int (*funcInFile)();
	typedef int (*funcOutFile)();

	if (hModule == NULL)
	{
		printf("DLL не подключена!\n");
	}
	else
	{
		//получаем функции из DLL
		funcAdd add = (funcAdd)GetProcAddress(hModule, "addToList");
		funcOut out = (funcOut)GetProcAddress(hModule, "outputList");
		funcFind find = (funcFind)GetProcAddress(hModule, "findStudent");
		funcDel del = (funcDel)GetProcAddress(hModule, "deleteStudent");
		funcInFile inFile = (funcInFile)GetProcAddress(hModule, "inputInFile");
		funcOutFile outFile = (funcOutFile)GetProcAddress(hModule, "outputFromFile");


		if ((add == NULL)|| (out == NULL)|| (find == NULL)|| (del == NULL)|| (inFile == NULL)|| (outFile == NULL))
		{
			cout << GetLastError() << endl;
			printf("Функция из DLL не получена!\n");
		}
		else
		{
			for (int i = 0; i < 2; i++) {
				cout << "Введите номер студента: ";
				key = 0;
				cin >> key;

				cout << "Введите фамилию студента: ";
				cin >> name;
				add(key, name);
			}
			cout << "------------------------------------------------------------------------------------------------------ " << endl;
			out();

			//лабораторная работа №4
			cout << "------------------------------------------------------------------------------------------------------" << endl;
			cout << "Введите номер студента, которого хотите найти: ";
			key = 0;
			cin >> key;
			cout << "Фамилия найденного студента: ";
			find(key);

			cout << "------------------------------------------------------------------------------------------------------" << endl;
			cout << "Введите номер студента, которого хотите удалить: ";
			key = 0;
			cin >> key;
			del(key);
			cout << "------------------------------------------------------------------------------------------------------" << endl;
			out();

			//лабораторная работа №5
			cout << "------------------------------------------------------------------------------------------------------" << endl;
			inFile();
			cout << "Список записан в файл" << endl;
			cout << "------------------------------------------------------------------------------------------------------" << endl;
			outFile();
		}
		system("pause");
		return 0;
	}
}