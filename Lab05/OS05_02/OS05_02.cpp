#include <iostream>
#include <cstdlib>
#include "Windows.h"

DWORD getProcessPriority(int i)
{
	switch (i)
	{
		case 1: return IDLE_PRIORITY_CLASS;
		case 2: return BELOW_NORMAL_PRIORITY_CLASS;
		case 3: return NORMAL_PRIORITY_CLASS;
		case 4: return ABOVE_NORMAL_PRIORITY_CLASS;
		case 5: return HIGH_PRIORITY_CLASS;
		case 6: return REALTIME_PRIORITY_CLASS;
		default: throw "Unknown priority class...";
	}
}


int main(int argc, char* argv[])
{
	try
	{
		if (argc == 4)
		{
			HANDLE hp = GetCurrentProcess();

			DWORD mask = atoi(argv[1]);
			DWORD firstPriority = atoi(argv[2]);
			DWORD secondPriority = atoi(argv[3]);

			if (!SetProcessAffinityMask(hp, mask))
				throw "SetProcessAffinityMask error";

			std::cout << "Current affinity mask: " << std::showbase << std::hex << mask << std::endl;
			std::cout << "First process priority: " << getProcessPriority(firstPriority) << std::endl;
			std::cout << "Second process priority: " << getProcessPriority(secondPriority) << std::endl;

			LPCWSTR path = L"D:\\University\\5th_term\\OS\\Lab05\\x64\\Debug\\OS05_02x.exe";
			STARTUPINFO si1, si2;
			PROCESS_INFORMATION pi1, pi2;
			ZeroMemory(&si1, sizeof(STARTUPINFO));
			ZeroMemory(&si2, sizeof(STARTUPINFO));
			si1.cb = sizeof(STARTUPINFO);
			si2.cb = sizeof(STARTUPINFO);

			if (CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | getProcessPriority(firstPriority), NULL, NULL, &si1, &pi1))
				std::cout << "-- Process OS05_02_1 was created\n";
			else 
				std::cout << "-- Process OS05_02_1 wasn't created\n";

			if (CreateProcess(path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | getProcessPriority(secondPriority), NULL, NULL, &si2, &pi2))
				std::cout << "-- Process OS05_02_2 was created\n";
			else 
				std::cout << "-- Process OS05_02_2 wasn't created\n";

			WaitForSingleObject(pi1.hProcess, INFINITE);
			WaitForSingleObject(pi2.hProcess, INFINITE);

			CloseHandle(pi1.hProcess);
			CloseHandle(pi2.hProcess);
		}
		else
			std::cout << "No parameters provided" << std::endl;
	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}
}