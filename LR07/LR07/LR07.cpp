﻿#include <iostream>
#include <stdio.h>
#include <time.h>
#include "windows.h"
#include "MyClass.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Задание: Требуется реализовать структуру данных\n«ассоциативный массив», используя связный список." << endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	MyClass mC;

	int key = 0;
	int mark = 0;

	for (int i = 0; i < 2; i++) {
		key = rand() % 10 + 1;
		mark = rand() % 50 + 1;

		mC.add_to_buf(key, mark);
	}

	mC.output_list();

	cout << "------------------------------------------------------------------------------------------------------ " << endl;
	MyClass mC1;
	mC1.output_from_file();
	mC1.add_to_buf(10, 100000);
	mC1.output_list();

	cout << "------------------------------------------------------------------------------------------------------ " << endl;
	MyClass mC2;
	mC2.output_from_file();
	mC2.output_list();

	WaitForSingleObject(mC2.hEventBufEmpty, INFINITE);

	//лабораторная работа №7
	/*
	изучение методов написания многопоточных приложений и синхронизации потоков в программном интерфейсе Win32. В библиотеку функций для
	работы с заданной структурой данных, реализованную в задании №5 или №6, добавляется следующая функциональность. Вызов функции для добавления
	элемента в структуру выполняется в одном потоке, обработка вызова с действительным помещением элементов в нее – в другом потоке. Передача
	аргументов вызова осуществляется через буфер в памяти, доступ к которому синхронизируется. При каждом добавлении элемента в структуру данных
	происходит ее сохранение на диск целиком, как в задании №5. Тестирующая программа демонстрирует корректность записи элементов путем чтения
	файла на диске и печати его содержимого по окончании добавления
	*/


	system("pause");
	return 0;
}