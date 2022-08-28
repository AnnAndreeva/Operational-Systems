#include "pch.h"
#include <utility>
#include <limits.h>
#include "MyClass.h"

// DLL internal state variables:
static unsigned long long previous_;  // Previous value, if any
static unsigned long long current_;   // Current sequence value
static unsigned index_;               // Current seq. position


DWORD dwBytesWritten = 0;
DWORD dwBytesRead = 0;


tuple<int, string> makeStudent(int key, string name)
{
	return make_tuple(key, name);//������� ���� ����-��������
}


__declspec(dllexport) void addToList(int key, string name) //���������� ���� ����-�������� � ������
{

	if (myList.empty()) //���� ������ ����
	{
		myList.push_back(makeStudent(key, name));
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
			myList.push_back(makeStudent(key, name));
		}
	}
}


__declspec(dllexport) void findStudent(int key)//����� ���� ����-�������� � ������ �� �����
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

__declspec(dllexport) void deleteStudent(int key)//�������� ���� ����-�������� � ������ �� �����
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

__declspec(dllexport) void inputInFile()
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

__declspec(dllexport) void outputFromFile()
{
	myList.clear();//������� ������ ������ ��� ������ � ���� ������ �� ����� 

	int key = 0;//����������� �� ����� ����
	int l = 0;//����������� �� ����� ����� ��������
	string name;//����������� �� ����� ��������

	bool notEOF = true;//��� �������� �� ����� �����
	HANDLE hFile;
	hFile = CreateFile(L"list.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);//��������� ���� �� ������

	//for (;;) {if (dwBytesRead){add_to_list(key, name);}else break;} - �������������� ������� �����
	while (notEOF) {

		ReadFile(hFile, &key, sizeof(int), &dwBytesRead, NULL);//��������� ����
		ReadFile(hFile, &l, sizeof(int), &dwBytesRead, NULL);//��������� ����� ��������
		name.clear();//�������� ��������
		name.append(l, ' ');//���������� ����� �����
		ReadFile(hFile, (PVOID)name.c_str(), l, &dwBytesRead, NULL);//��������� ��������

		if (dwBytesRead)//���� ����, ��� ���������, �� ���������
		{
			addToList(key, name);//��������� � ������ ��������� ��������
		}
		else notEOF = false;//���� ������� 0 ����, ������ ����� �����
	}

	outputList();//������� ����� ������
	CloseHandle(hFile);//��������� ����
}


__declspec(dllexport) void outputList()//����� ������
{
	for (auto iter = myList.begin(); iter != myList.end(); iter++)//�������� �� ������
	{
		cout << "����� ��������(����): ";
		cout << get<0>(*iter) << endl;
		cout << "������� ��������(��������): ";
		cout << get<1>(*iter) << endl;
	}
}

