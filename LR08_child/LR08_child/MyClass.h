#pragma once
#include <iostream>
#include <stdio.h>
#include <tuple>
#include <list>
#include <time.h>
#include "windows.h"

#define buf_size 256
#define name_of_file_in_memory L"file"
#define name_of_file_in_memory1 L"file1"

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
	HANDLE h_map_file = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, buf_size, name_of_file_in_memory);
	HANDLE h_map_file1 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, buf_size, name_of_file_in_memory1);

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