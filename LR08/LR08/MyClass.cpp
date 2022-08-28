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


DWORD WINAPI ThreadProc(PVOID a)//поток записи в список
{
	MyClass* mC = (MyClass*)a;
	for (;;) {
		WaitForSingleObject(mC->hEventBufFull, INFINITE);//ожидание сигнального состояния
		mC->add_to_list(mC->buf_key, mC->buf_mark);//добавляем пару ключ-значение
		mC->input_in_file();//записываем в файл

		SetEvent(mC->hEventBufEmpty);//переводит в сигнальное состояние, что буфер свободен
	}
	return 0;
}

MyClass::MyClass() {
	buf_mark = 0;
	buf_key = 0;

	hEventBufEmpty = CreateEvent(NULL, FALSE, FALSE, "BuffEmpty.txt");//изначально буфер чист
	hEventBufFull = CreateEvent(NULL, FALSE, TRUE, "BuffFull.txt");//событие занято
}

tuple<int, int> MyClass::make_mark(int key, int mark)
{
	return make_tuple(key, mark);//создаем пару ключ-значение
}

void MyClass::add_to_buf(int key, int mark)//поток записи в буфер
{
	WaitForSingleObject(hEventBufFull, INFINITE);//ждем пока буфер не заполнится
	int* put_buf = (int*)MapViewOfFile(h_map_file, FILE_MAP_ALL_ACCESS, 0, 0, buf_size);
	int* put_buf1 = (int*)MapViewOfFile(h_map_file1, FILE_MAP_ALL_ACCESS, 0, 0, buf_size);
	CopyMemory((void*)(put_buf), &key, sizeof(int));
	CopyMemory((void*)(put_buf1), &mark, sizeof(int));
	add_to_list(*put_buf, *put_buf1);
}


void MyClass::add_to_list(int key, int mark) //добавление пары ключ-значение в список
{

	if (myList.empty()) //если список пуст
	{
		myList.push_back(make_mark(key, mark));
	}
	else //если список не пуст
	{
		bool swap = false;//проверка на замену значения		

		for (auto iter = myList.begin(); (!swap) && (iter != myList.end()); iter++)//проходим по списку
		{
			if (get<0>(*iter) == key) //если нашли пару с этим ключом, то меняем старое значение на новое
			{
				get<1>(*iter) = mark;
				swap = true;
			}
		}

		if (!swap) //если не нашли, то добавляем в конец списка
		{
			myList.push_back(make_mark(key, mark));
		}
	}
}

void MyClass::find_mark(int key)//поиск пары ключ-значение в списке по ключу
{
	bool find = false;//проверка на нахождение

	for (auto iter = myList.begin(); (!find) && (iter != myList.end()); iter++)//проходим по списку
	{
		if (get<0>(*iter) == key) //если ключи совпали, выводим фамилию студента
		{
			find = true;
			cout << get<1>(*iter) << endl;
		}
	}

	if (!find) {
		cout << "Метки с таким номером нет. " << endl;
	}
}

void MyClass::delete_mark(int key)//удаление пары ключ-значение в списке по ключу
{
	bool del = false;//проверка на удаление

	for (auto iter = myList.begin(); (!del) && (iter != myList.end()); iter++)//проходим по списку
	{
		if (get<0>(*iter) == key) //если ключи совпали, то удаляем элемент
		{
			myList.remove(*iter);
			cout << "Метка удалена." << endl;
			del = true;
		}
	}

	if (!del) {
		cout << "Метки с таким номером нет." << endl;
	}
}

void MyClass::input_in_file()
{
	HANDLE hFile;
	hFile = CreateFile("list.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);//открываем файл на запись

	for (auto iter = myList.begin(); iter != myList.end(); iter++)//проходим по списку
	{
		WriteFile(hFile, &get<0>(*iter), (DWORD)sizeof(int), &dwBytesWritten, NULL);//записываем ключ в файл
		WriteFile(hFile, &get<1>(*iter), (DWORD)sizeof(int), &dwBytesWritten, NULL);//записываем метку в файл

	}
	CloseHandle(hFile);
}

void MyClass::output_from_file()
{
	myList.clear();//очищаем старый список для записи в него данных из файла 

	int key = 0;//считываемый из файла ключ
	int l = 0;//считываемая из файла длина значения
	int mark;//считываемое из файла значение

	bool notEOF = true;//для проверки на конец файла
	HANDLE hFile;
	hFile = CreateFile("list.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);//открываем файл на чтение

	//for (;;) {if (dwBytesRead){add_to_list(key, name);}else break;} - альтернативный вариант цикла
	while (notEOF) {

		ReadFile(hFile, &key, sizeof(int), &dwBytesRead, NULL);//считываем ключ
		ReadFile(hFile, &mark, sizeof(int), &dwBytesRead, NULL);//считываем ключ


		if (dwBytesRead)//если есть, что считывать, то добавляем
		{
			add_to_list(key, mark);//добавляем в список считанное значение
		}
		else notEOF = false;//если считали 0 байт, значит конец файла
	}

	output_list();//выводим новый список
	CloseHandle(hFile);//закрываем файл
}

void MyClass::output_list()//вывод списка
{
	for (auto iter = myList.begin(); iter != myList.end(); iter++)//проходим по списку
	{
		cout << "Номер метки(ключ): ";
		cout << get<0>(*iter) << endl;
		cout << "Метка(значение): ";
		cout << get<1>(*iter) << endl;
	}
}

MyClass::~MyClass() {}