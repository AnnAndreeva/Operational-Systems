#include <iostream>
#include <stdio.h>
#include <time.h>
#include <tuple>
#include <list>
#include <iterator>
#include "windows.h"
#include "MyClass.h"
using namespace std;
DWORD dwBytesWritten = 0;
DWORD dwBytesRead = 0;

MyClass::MyClass() {}

tuple<int, string> MyClass::make_student(int key, string name)
{
	return make_tuple(key, name);//создаем пару ключ-значение
}


void MyClass::add_to_list(int key, string name) //добавление пары ключ-значение в список
{

	if (myList.empty()) //если список пуст
	{
		myList.push_back(make_student(key, name));
	}
	else //если список не пуст
	{
		bool swap = false;//проверка на замену значения		

		for (auto iter = myList.begin(); (!swap) && (iter != myList.end()); iter++)//проходим по списку
		{
			if (get<0>(*iter) == key) //если нашли пару с этим ключом, то меняем старое значение на новое
			{
				get<1>(*iter) = name;
				swap = true;
			}
		}

		if (!swap) //если не нашли, то добавляем в конец списка
		{
			myList.push_back(make_student(key, name));
		}
	}
}


void MyClass::find_student(int key)//поиск пары ключ-значение в списке по ключу
{
	bool find = false;//проверка на нахождение

	for (auto iter = myList.begin(); (!find) && (iter != myList.end()); iter++)//проходим по списку
	{
		if (get<0>(*iter) == key) //если ключи совпали, выводим фамилию студента
		{
			find = true;
			cout << get<1>(*iter) << endl;
		}
	}

	if (!find) {
		cout << "Студента с таким номером нет. " << endl;
	}
}

void MyClass::delete_student(int key)//удаление пары ключ-значение в списке по ключу
{
	bool del = false;//проверка на удаление

	for (auto iter = myList.begin(); (!del) && (iter != myList.end()); iter++)//проходим по списку
	{
		if (get<0>(*iter) == key) //если ключи совпали, то удаляем элемент
		{
			myList.remove(*iter);
			cout << "Студент удален." << endl;
			del = true;
		}
	}

	if (!del) {
		cout << "Студента с таким номером нет." << endl;
	}
}

void MyClass::input_in_file()
{
	HANDLE hFile;
	hFile = CreateFile(L"list.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);//открываем файл на запись

	for (auto iter = myList.begin(); iter != myList.end(); iter++)//проходим по списку
	{
		WriteFile(hFile, &get<0>(*iter), (DWORD)sizeof(int), &dwBytesWritten, NULL);//записываем ключ в файл
		int len = get<1>(*iter).length();//находим длину значения
		WriteFile(hFile, &len, (DWORD)sizeof(int), &dwBytesWritten, NULL);//записываем длину значения в файл
		WriteFile(hFile, get<1>(*iter).c_str(), len, &dwBytesWritten, NULL);//записываем значение в файл
	}
	CloseHandle(hFile);
}

void MyClass::output_from_file()
{
	myList.clear();//очищаем старый список для записи в него данных из файла 

	int key = 0;//считываемый из файла ключ
	int l = 0;//считываемая из файла длина значения
	string name;//считываемое из файла значение

	bool notEOF = true;//для проверки на конец файла
	HANDLE hFile;
	hFile = CreateFile(L"list.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);//открываем файл на чтение

	//for (;;) {if (dwBytesRead){add_to_list(key, name);}else break;} - альтернативный вариант цикла
	while(notEOF){

		ReadFile(hFile, &key, sizeof(int), &dwBytesRead, NULL);//считываем ключ
		ReadFile(hFile, &l, sizeof(int), &dwBytesRead, NULL);//считываем длину значения
		name.clear();//обнуляем значение
		name.append(l, ' ');//присаиваем новую длину
		ReadFile(hFile, (PVOID)name.c_str(), l, &dwBytesRead, NULL);//считываем значение

		if (dwBytesRead)//если есть, что считывать, то добавляем
		{
			add_to_list(key, name);//добавляем в список считанное значение
		}
		else notEOF = false;//если считали 0 байт, значит конец файла
	}

	output_list();//выводим новый список
	CloseHandle(hFile);//закрываем файл
}


void MyClass::output_list()//вывод списка
{
	for (auto iter = myList.begin(); iter != myList.end(); iter++)//проходим по списку
	{
		cout << "Номер студента(ключ): ";
		cout << get<0>(*iter) << endl;
		cout << "Фамилия студента(значение): ";
		cout << get<1>(*iter) << endl;
	}
}

MyClass::~MyClass() {}