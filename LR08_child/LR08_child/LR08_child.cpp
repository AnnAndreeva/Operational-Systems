#include <Windows.h>
#include <iostream>
#include "MyClass.h"
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "Дочерний процесс запущен" << endl;
	MyClass mc;
	
	for (int i = 0; i < 3; i++) {
		mc.add_to_list(i+1, i*10+5);
	}
	mc.output_list();

	int key, mark;

	WaitForSingleObject(mc.hEventBufFull, INFINITE);//ждем пока буфер не наполнится

	int* put_buf = (int*)MapViewOfFile(mc.h_map_file, FILE_MAP_ALL_ACCESS, 0, 0, buf_size);
	int* put_buf1 = (int*)MapViewOfFile(mc.h_map_file1, FILE_MAP_ALL_ACCESS, 0, 0, buf_size);
	CopyMemory((void*)(&key), put_buf, sizeof(int));
	CopyMemory((void*)(&mark), put_buf1, sizeof(int));

	SetEvent(mc.hEventBufFull);
	mc.add_to_buf(key, mark);

	cout<<"-----------------------------------------------------------------------------------" << endl;
	mc.input_in_file();
	cout << "Список, записанный в файл: " << endl;
	mc.output_list();

	SetEvent(mc.hEventBufEmpty);
	system("Pause");
	return 0;
}
