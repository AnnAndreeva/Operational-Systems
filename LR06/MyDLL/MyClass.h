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
MYDLL_API list<tuple<int, string>> myList;//������ - ������������� ������
MYDLL_API tuple<int, string> makeStudent(int key, string name); //�������� ���� ����-��������
MYDLL_API void addToList(int key, string name);//���������� ���� ����-�������� � ������
MYDLL_API void findStudent(int key);//����� ���� ����-�������� � ������ �� �����
MYDLL_API void deleteStudent(int key);//�������� ���� ����-�������� � ������ �� �����


MYDLL_API void inputInFile();//���������� ������ � ����
MYDLL_API void outputFromFile();//��������� ������ �� �����

MYDLL_API void outputList();//����� ������




//extern "C"
