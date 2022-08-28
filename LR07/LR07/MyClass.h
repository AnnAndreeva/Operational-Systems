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

	tuple <int, int> make_mark(int key, int mark); //�������� ���� ����-��������

	void add_to_buf(int key, int mark);//���������� � �����

	void add_to_list(int key, int mark); //���������� ���� ����-�������� � ������
	void find_mark(int key);//����� ���� ����-�������� � ������ �� �����
	void delete_mark(int key);//�������� ���� ����-�������� � ������ �� �����

	void input_in_file();//���������� ������ � ����
	void output_from_file();//��������� ������ �� �����

	void output_list();//����� ������
	~MyClass();
};


