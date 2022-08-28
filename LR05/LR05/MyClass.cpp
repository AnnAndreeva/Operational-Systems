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
	return make_tuple(key, name);//������� ���� ����-��������
}


void MyClass::add_to_list(int key, string name) //���������� ���� ����-�������� � ������
{

	if (myList.empty()) //���� ������ ����
	{
		myList.push_back(make_student(key, name));
	}
	else //���� ������ �� ����
	{
		bool swap = false;//�������� �� ������ ��������		

		for (auto iter = myList.begin(); (!swap) && (iter != myList.end()); iter++)//�������� �� ������
		{
			if (get<0>(*iter) == key) //���� ����� ���� � ���� ������, �� ������ ������ �������� �� �����
			{
				get<1>(*iter) = name;
				swap = true;
			}
		}

		if (!swap) //���� �� �����, �� ��������� � ����� ������
		{
			myList.push_back(make_student(key, name));
		}
	}
}


void MyClass::find_student(int key)//����� ���� ����-�������� � ������ �� �����
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
		cout << "�������� � ����� ������� ���. " << endl;
	}
}

void MyClass::delete_student(int key)//�������� ���� ����-�������� � ������ �� �����
{
	bool del = false;//�������� �� ��������

	for (auto iter = myList.begin(); (!del) && (iter != myList.end()); iter++)//�������� �� ������
	{
		if (get<0>(*iter) == key) //���� ����� �������, �� ������� �������
		{
			myList.remove(*iter);
			cout << "������� ������." << endl;
			del = true;
		}
	}

	if (!del) {
		cout << "�������� � ����� ������� ���." << endl;
	}
}

void MyClass::input_in_file()
{
	HANDLE hFile;
	hFile = CreateFile(L"list.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);//��������� ���� �� ������

	for (auto iter = myList.begin(); iter != myList.end(); iter++)//�������� �� ������
	{
		WriteFile(hFile, &get<0>(*iter), (DWORD)sizeof(int), &dwBytesWritten, NULL);//���������� ���� � ����
		int len = get<1>(*iter).length();//������� ����� ��������
		WriteFile(hFile, &len, (DWORD)sizeof(int), &dwBytesWritten, NULL);//���������� ����� �������� � ����
		WriteFile(hFile, get<1>(*iter).c_str(), len, &dwBytesWritten, NULL);//���������� �������� � ����
	}
	CloseHandle(hFile);
}

void MyClass::output_from_file()
{
	myList.clear();//������� ������ ������ ��� ������ � ���� ������ �� ����� 

	int key = 0;//����������� �� ����� ����
	int l = 0;//����������� �� ����� ����� ��������
	string name;//����������� �� ����� ��������

	bool notEOF = true;//��� �������� �� ����� �����
	HANDLE hFile;
	hFile = CreateFile(L"list.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);//��������� ���� �� ������

	//for (;;) {if (dwBytesRead){add_to_list(key, name);}else break;} - �������������� ������� �����
	while(notEOF){

		ReadFile(hFile, &key, sizeof(int), &dwBytesRead, NULL);//��������� ����
		ReadFile(hFile, &l, sizeof(int), &dwBytesRead, NULL);//��������� ����� ��������
		name.clear();//�������� ��������
		name.append(l, ' ');//���������� ����� �����
		ReadFile(hFile, (PVOID)name.c_str(), l, &dwBytesRead, NULL);//��������� ��������

		if (dwBytesRead)//���� ����, ��� ���������, �� ���������
		{
			add_to_list(key, name);//��������� � ������ ��������� ��������
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
		cout << "����� ��������(����): ";
		cout << get<0>(*iter) << endl;
		cout << "������� ��������(��������): ";
		cout << get<1>(*iter) << endl;
	}
}

MyClass::~MyClass() {}