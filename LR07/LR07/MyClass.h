#pragma once
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <list>
#include <time.h>
#include "windows.h"
using namespace std;

class MyClass
{
public:

	list<tuple<int, int>> myList;

	int buf_mark;
	int buf_key;

	HANDLE hThread;
	HANDLE hEventBufFull;
	HANDLE hEventBufEmpty;

	MyClass();

	tuple <int, int> make_mark(int key, int mark); //создание пары ключ-значение

	void add_to_buf(int key, int mark);//добавление в буфер

	void add_to_list(int key, int mark); //добавление пары ключ-значение в список
	void find_mark(int key);//поиск пары ключ-значение в списке по ключу
	void delete_mark(int key);//удаление пары ключ-значение в списке по ключу

	void input_in_file();//записываем список в файл
	void output_from_file();//считываем список из файла

	void output_list();//вывод списка
	~MyClass();
};


