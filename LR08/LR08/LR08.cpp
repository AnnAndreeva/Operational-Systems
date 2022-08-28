#include <Windows.h>
#include <iostream>
#include "MyClass.h"
#define PROC_NAME "../../LR08_child\\Debug\\LR08_child.exe"

int main()
{
	setlocale(LC_ALL, "Rus");
	STARTUPINFO start_inform;
	PROCESS_INFORMATION proc_inf;

	ZeroMemory(&start_inform, sizeof(STARTUPINFO));
	start_inform.cb = sizeof(STARTUPINFO);

	MyClass* mc = new MyClass();
	
    mc->add_to_buf(5, 1000);
	SetEvent(mc->hEventBufFull);
	
	if (!CreateProcess(PROC_NAME, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &start_inform, &proc_inf)) {
		cout << "Процесс не создан" << GetLastError();
		return 1;
	}
	else {
		cout << "Ожидайте, запущен дочерний процесс" << endl;
		WaitForSingleObject(proc_inf.hProcess, INFINITE);

		CloseHandle(proc_inf.hThread);
		CloseHandle(proc_inf.hProcess);

		cout << "Список, полученный из файла: " << endl;
		mc->output_from_file();
	}
	system("Pause");
	return 0;
}
