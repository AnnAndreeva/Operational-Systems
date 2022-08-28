#include <iostream>
#include <stdio.h>
#include <time.h>
#include <tuple>
#include <list>
#include <iterator>
#include "windows.h"
#include "MyClass.h"
using namespace std;


MyClass::MyClass(){}

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

	for(auto iter = myList.begin(); (!del) && (iter != myList.end()); iter++ )//�������� �� ������
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

MyClass::~MyClass(){}
