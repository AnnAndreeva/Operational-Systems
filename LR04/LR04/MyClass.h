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
	
	tuple <int, string> make_student(int key, string name); //�������� ���� ����-��������
	void add_to_list(int key, string name); //���������� ���� ����-�������� � ������
	void find_student(int key);//����� ���� ����-�������� � ������ �� �����
	void delete_student( int key);//�������� ���� ����-�������� � ������ �� �����
	void output_list();//����� ������
	~MyClass();
};

