#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>

int input() {
	int M = 0;
	printf("Введите целое цисло: ");
	scanf("%d", &M);
	return M;
}

bool task(int M, int count) {
	int sum = 0;
	int a, b, c;

	a = count / 100;
	b = (count / 10) % 10;
	c = count % 10;

	sum = a + b + c;

	if (sum == M) {
		return true;
	}
	else return false;
}

void output(int M) {
	for (int count = 100; count < 1000; count++) {
		if (task(M, count)) {
			printf("%d\n", count);
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");

	output(input());

	system("pause");
	return 0;
}

