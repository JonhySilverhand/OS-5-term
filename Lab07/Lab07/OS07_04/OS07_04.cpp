#include <iostream>
#include <Windows.h>
#include <ctime>

int main()
{
	DWORD pid = GetCurrentProcessId();
	std::cout << "Main process ID: " << pid << '\n';

	long long it = -60 * 10000000;

	HANDLE htimer = CreateWaitableTimer(NULL, FALSE, L"OS07_04");
	if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 60000, NULL, NULL, FALSE))
		throw "SetWaitableTimer Error";

	LPCWSTR path = L"D:\\University\\5th_term\\OS\\Lab07\\Lab07\\x64\\Debug\\OS07_04_X.exe";

	PROCESS_INFORMATION pi1, pi2;
	clock_t start = clock();

	STARTUPINFO si1;
	ZeroMemory(&si1, sizeof(STARTUPINFO));
	si1.cb = sizeof(STARTUPINFO);

	if (CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
		std::cout << "Process OS08_04_1 was created" << std::endl;
	else
		std::cout << "CreateProcess 1 error" << std::endl;

	STARTUPINFO si2;
	ZeroMemory(&si2, sizeof(STARTUPINFO));
	si2.cb = sizeof(STARTUPINFO);

	if (CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
		std::cout << "Process OS08_04_2 was created" << std::endl;
	else
		std::cout << "CreateProcess 2 error" << std::endl;


	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	CloseHandle(htimer);
	std::cout << "Elapsed time = " << (clock() - start) / CLOCKS_PER_SEC << " s" << std::endl;
	system("pause");
	return 0;
}