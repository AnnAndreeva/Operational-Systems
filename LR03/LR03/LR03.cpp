#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <time.h>
#include "windows.h"

int main()
{
	setlocale(LC_ALL, "Rus");
	printf("Задание: Необходимо каждый элемент строки разделить на наибольший элемент строки\nв динамическом массиве размерностью NxM.\n");

	int N = 0;
	int M = 0;
	printf("Введите N: ");
	scanf("%d", &N);
	printf("\nВведите M: ");
	scanf("%d", &M);

	srand(time(0)); // генерация случайных чисел

	HANDLE matrHeap;// указатель на кучу
	matrHeap = HeapCreate(0, 0, 0);// cоздаем кучу

	if (matrHeap != NULL)// если создана удачно
	{
		double** matr;
		matr = (double**)HeapAlloc(matrHeap, 0, N*sizeof(int*));//выделяем место в куче для матрицы
		for (int i = 0; i < N; i++)
		{
			matr[i] = (double*)HeapAlloc(matrHeap, 0, M * sizeof(int));//выделяем место в куче для столбцов матрицы
		}

		//заполнение матрицы
		for (int count_row = 0; count_row < N; count_row++)
		{
			for (int count_column = 0; count_column < M; count_column++)
			{
				matr[count_row][count_column] = double(rand() % 20 + 1) / ((rand() % 10 + 1));
				printf("%lf   ", matr[count_row][count_column]);
			}
			printf("\n");
		}

		printf("-----------------------------------------------------------\n");

		// поиск максимума в строке и изменение элементов
		double max;
		for (int count_row = 0; count_row < N; count_row++)
		{
			max = matr[count_row][0];
			for (int count_column = 0; count_column < M; count_column++)
			{
				if (matr[count_row][count_column] >  max)
				{
					max = matr[count_row][count_column];
				}
			}

			for (int count_column = 0; count_column < M; count_column++)
			{
				matr[count_row][count_column] = matr[count_row][count_column] / max;
			}
		}

		//вывод матрицы
		for (int count_row = 0; count_row < N; count_row++)
		{
			for (int count_column = 0; count_column < M; count_column++)
			{
				printf("%lf   ", matr[count_row][count_column]);
			}
			printf("\n");
		}


		// Разрушить и сообщить в случае ошибки
		if (HeapDestroy(matrHeap) == 0)
			printf("Ошибка удаления кучи.");
	}
	else
	{
		printf("Ошибка создания кучи.");
	}

	system("pause");
	return 0;
}
