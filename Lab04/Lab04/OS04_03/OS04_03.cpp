﻿#include <iostream>
#include <Windows.h>
using namespace std;
DWORD pid = NULL;

DWORD WINAPI ChildThread_T1()
{
	DWORD tid = GetCurrentThreadId();

	for (short i = 0; i < 50; ++i)
	{
		cout << "PID = " << pid << ", Thread1 ID = " << tid << endl;
		Sleep(1000);
	}
	return 0;
}

DWORD WINAPI ChildThread_T2()
{
	DWORD tid = GetCurrentThreadId();

	for (short i = 0; i < 125; ++i)
	{
		cout << "PID = " << pid << ", Thread2 ID = " << tid << endl;
		Sleep(1000);
	}
	return 0;
}

int main()
{
	pid = GetCurrentProcessId();
	DWORD parentId = GetCurrentThreadId();
	DWORD childId_T1 = NULL;
	DWORD childId_T2 = NULL;
	HANDLE handleChild_T1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_T1, NULL, 0, &childId_T1);
	HANDLE handleChild_T2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread_T2, NULL, 0, &childId_T2);

	for (short i = 1; i <= 100; ++i)
	{
		switch (i)
		{
		case 20: SuspendThread(handleChild_T1); break;
		case 60: ResumeThread(handleChild_T1);  break;
		case 40: SuspendThread(handleChild_T2); break;
		case 100: ResumeThread(handleChild_T2); break;
		}
		cout << i << " - PID = " << pid << ", Thread main ID = " << parentId << endl;
		Sleep(1000);
	}

	WaitForSingleObject(handleChild_T1, INFINITE);
	WaitForSingleObject(handleChild_T2, INFINITE);
	CloseHandle(handleChild_T1);
	CloseHandle(handleChild_T2);
	system("pause");
	return 0;
}