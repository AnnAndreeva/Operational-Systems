#include <iostream>
#include <stdio.h>
#include <time.h>
#include <tuple>
#include <list>
#include <iterator>
#include "windows.h"
#include "MyClass.h"
using namespace std;


MyClass::MyClass(){}

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
		bool swap = false;//проверка на замену значени€		
	
		for (auto iter = myList.begin(); (!swap) && (iter != myList.end()); iter++)//проходим по списку
		{
			if (get<0>(*iter) == key) //если нашли пару с этим ключом, то мен€ем старое значение на новое
			{
				get<1>(*iter) = name;
				swap = true;
			}
		}

		if (!swap) //если не нашли, то добавл€ем в конец списка
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
		cout << "—тудента с таким номером нет. " << endl;
	}
}

void MyClass::delete_student(int key)//удаление пары ключ-значение в списке по ключу
{
	bool del = false;//проверка на удаление

	for(auto iter = myList.begin(); (!del) && (iter != myList.end()); iter++ )//проходим по списку
	{
		if (get<0>(*iter) == key) //если ключи совпали, то удал€ем элемент
		{
			myList.remove(*iter);
			cout << "—тудент удален." << endl;
			del = true;
		}
	}

	if (!del) {
		cout << "—тудента с таким номером нет." << endl;
	}
}

void MyClass::output_list()//вывод списка
{	
	for (auto iter = myList.begin(); iter != myList.end(); iter++)//проходим по списку
	{
		cout << "Ќомер студента(ключ): ";
		cout << get<0>(*iter) << endl;
		cout << "‘амили€ студента(значение): ";
		cout << get<1>(*iter) << endl;
	}
}

MyClass::~MyClass(){}
