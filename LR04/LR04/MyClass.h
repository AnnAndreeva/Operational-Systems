#pragma once
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <list>
#include <iterator>
#include <time.h>
#include "windows.h"
using namespace std;

class MyClass
{	
public:
	list<tuple<int, string>> myList;
	
	MyClass();
	
	tuple <int, string> make_student(int key, string name); //создание пары ключ-значение
	void add_to_list(int key, string name); //добавление пары ключ-значение в список
	void find_student(int key);//поиск пары ключ-значение в списке по ключу
	void delete_student( int key);//удаление пары ключ-значение в списке по ключу
	void output_list();//вывод списка
	~MyClass();
};

