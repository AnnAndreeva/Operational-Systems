#pragma once
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <list>
#include <time.h>
#include <string>
#include "windows.h"

using namespace std;

#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif
MYDLL_API list<tuple<int, string>> myList;//список - ассоциативный масиив
MYDLL_API tuple<int, string> makeStudent(int key, string name); //создание пары ключ-значение
MYDLL_API void addToList(int key, string name);//добавление пары ключ-значение в список
MYDLL_API void findStudent(int key);//поиск пары ключ-значение в списке по ключу
MYDLL_API void deleteStudent(int key);//удаление пары ключ-значение в списке по ключу


MYDLL_API void inputInFile();//записываем список в файл
MYDLL_API void outputFromFile();//считываем список из файла

MYDLL_API void outputList();//вывод списка




//extern "C"
