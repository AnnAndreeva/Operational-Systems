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


DWORD WINAPI ThreadProc(PVOID a)//����� ������ � ������
{
	MyClass* mC = (MyClass*)a;
	for (;;) {
		WaitForSingleObject(mC->hEventBufFull, INFINITE);//�������� ����������� ���������
		mC->add_to_list(mC->buf_key, mC->buf_mark);//��������� ���� ����-��������
		mC->input_in_file();//���������� � ����

		SetEvent(mC->hEventBufEmpty);//��������� � ���������� ���������, ��� ����� ��������
	}
	return 0;
}

MyClass::MyClass() {
	buf_mark = 0;
	buf_key = 0;

	hEventBufEmpty = CreateEvent(NULL, FALSE, FALSE, "BuffEmpty.txt");//���������� ����� ����
	hEventBufFull = CreateEvent(NULL, FALSE, TRUE, "BuffFull.txt");//������� ������
}

tuple<int, int> MyClass::make_mark(int key, int mark)
{
	return make_tuple(key, mark);//������� ���� ����-��������
}

void MyClass::add_to_buf(int key, int mark)//����� ������ � �����
{
	WaitForSingleObject(hEventBufFull, INFINITE);//���� ���� ����� �� ����������
	int* put_buf = (int*)MapViewOfFile(h_map_file, FILE_MAP_ALL_ACCESS, 0, 0, buf_size);
	int* put_buf1 = (int*)MapViewOfFile(h_map_file1, FILE_MAP_ALL_ACCESS, 0, 0, buf_size);
	CopyMemory((void*)(put_buf), &key, sizeof(int));
	CopyMemory((void*)(put_buf1), &mark, sizeof(int));
	add_to_list(*put_buf, *put_buf1);
}


void MyClass::add_to_list(int key, int mark) //���������� ���� ����-�������� � ������
{

	if (myList.empty()) //���� ������ ����
	{
		myList.push_back(make_mark(key, mark));
	}
	else //���� ������ �� ����
	{
		bool swap = false;//�������� �� ������ ��������		

		for (auto iter = myList.begin(); (!swap) && (iter != myList.end()); iter++)//�������� �� ������
		{
			if (get<0>(*iter) == key) //���� ����� ���� � ���� ������, �� ������ ������ �������� �� �����
			{
				get<1>(*iter) = mark;
				swap = true;
			}
		}

		if (!swap) //���� �� �����, �� ��������� � ����� ������
		{
			myList.push_back(make_mark(key, mark));
		}
	}
}

void MyClass::find_mark(int key)//����� ���� ����-�������� � ������ �� �����
{
	bool find = false;//�������� �� ����������

	for (auto iter = myList.begin(); (!find) && (iter != myList.end()); iter++)//�������� �� ������
	{
		if (get<0>(*iter) == key) //���� ����� �������, ������� ������� ��������
		{
			find = true;
			cout << get<1>(*iter) << endl;
		}
	}

	if (!find) {
		cout << "����� � ����� ������� ���. " << endl;
	}
}

void MyClass::delete_mark(int key)//�������� ���� ����-�������� � ������ �� �����
{
	bool del = false;//�������� �� ��������

	for (auto iter = myList.begin(); (!del) && (iter != myList.end()); iter++)//�������� �� ������
	{
		if (get<0>(*iter) == key) //���� ����� �������, �� ������� �������
		{
			myList.remove(*iter);
			cout << "����� �������." << endl;
			del = true;
		}
	}

	if (!del) {
		cout << "����� � ����� ������� ���." << endl;
	}
}

void MyClass::input_in_file()
{
	HANDLE hFile;
	hFile = CreateFile("list.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);//��������� ���� �� ������

	for (auto iter = myList.begin(); iter != myList.end(); iter++)//�������� �� ������
	{
		WriteFile(hFile, &get<0>(*iter), (DWORD)sizeof(int), &dwBytesWritten, NULL);//���������� ���� � ����
		WriteFile(hFile, &get<1>(*iter), (DWORD)sizeof(int), &dwBytesWritten, NULL);//���������� ����� � ����

	}
	CloseHandle(hFile);
}

void MyClass::output_from_file()
{
	myList.clear();//������� ������ ������ ��� ������ � ���� ������ �� ����� 

	int key = 0;//����������� �� ����� ����
	int l = 0;//����������� �� ����� ����� ��������
	int mark;//����������� �� ����� ��������

	bool notEOF = true;//��� �������� �� ����� �����
	HANDLE hFile;
	hFile = CreateFile("list.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);//��������� ���� �� ������

	//for (;;) {if (dwBytesRead){add_to_list(key, name);}else break;} - �������������� ������� �����
	while (notEOF) {

		ReadFile(hFile, &key, sizeof(int), &dwBytesRead, NULL);//��������� ����
		ReadFile(hFile, &mark, sizeof(int), &dwBytesRead, NULL);//��������� ����


		if (dwBytesRead)//���� ����, ��� ���������, �� ���������
		{
			add_to_list(key, mark);//��������� � ������ ��������� ��������
		}
		else notEOF = false;//���� ������� 0 ����, ������ ����� �����
	}

	output_list();//������� ����� ������
	CloseHandle(hFile);//��������� ����
}

void MyClass::output_list()//����� ������
{
	for (auto iter = myList.begin(); iter != myList.end(); iter++)//�������� �� ������
	{
		cout << "����� �����(����): ";
		cout << get<0>(*iter) << endl;
		cout << "�����(��������): ";
		cout << get<1>(*iter) << endl;
	}
}

MyClass::~MyClass() {}