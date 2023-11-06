#include <iostream>
#include "Windows.h"
#include <cstdlib>
#include <intrin.h>
#include <iomanip>



int main()
{
	HANDLE hp = GetCurrentProcess();
	HANDLE ht = GetCurrentThread();

	DWORD pid = GetCurrentProcessId();
	DWORD tid = GetCurrentThreadId();
	DWORD_PTR icpu = -1;

	for (int i = 0; i < 1000000; i++)
	{
		if (i % 1000 == 0 && i != 0)
		{
			Sleep(200);
			std::cout << "i: " << std::dec << i;
			std::cout << ", PID [" << pid << "]," << " ";
			DWORD procPriority = GetPriorityClass(hp);
			std::cout << "TID [" << tid << "]" << std::endl;
			DWORD thPriority = GetThreadPriority(ht);

			switch (procPriority)
			{
			case IDLE_PRIORITY_CLASS:
				std::cout << "Process priority:  IDLE_PRIORITY_CLASS\n";
				break;
			case BELOW_NORMAL_PRIORITY_CLASS:
				std::cout << "Process priority:  BELOW_NORMAL_PRIORITY_CLASS\n";
				break;
			case NORMAL_PRIORITY_CLASS:
				std::cout << "Process priority:  NORMAL_PRIORITY_CLASS\n";
				break;
			case ABOVE_NORMAL_PRIORITY_CLASS:
				std::cout << "Process priority:  ABOVE_NORMAL_PRIORITY_CLASS\n";
				break;
			case HIGH_PRIORITY_CLASS:
				std::cout << "Process priority:  HIGH_PRIORITY_CLASS\n";
				break;
			case REALTIME_PRIORITY_CLASS:
				std::cout << "Process priority:  REALTIME_PRIORITY_CLASS\n";
				break;
			default:
				std::cout << "Unknown process priority.\n";
				break;
			}

			

			switch (thPriority)
			{
			case THREAD_PRIORITY_LOWEST:
				std::cout << "Thread priority:  THREAD_PRIORITY_LOWEST\n";
				break;
			case THREAD_PRIORITY_BELOW_NORMAL:
				std::cout << "Thread priority:  THREAD_PRIORITY_BELOW_NORMAL\n";
				break;
			case THREAD_PRIORITY_NORMAL:
				std::cout << "Thread priority:  THREAD_PRIORITY_NORMAL\n";
				break;
			case THREAD_PRIORITY_ABOVE_NORMAL:
				std::cout << "Thread priority:  THREAD_PRIORITY_ABOVE_NORMAL\n";
				break;
			case THREAD_PRIORITY_HIGHEST:
				std::cout << "Thread priority:  THREAD_PRIORITY_HIGHEST\n";
				break;
			case THREAD_PRIORITY_IDLE:
				std::cout << "Thread priority:  THREAD_PRIORITY_IDLE\n";
				break;
			default:
				std::cout << "Unknown thread priority.\n";
				break;
			}

			icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
			std::cout << "ThreadIdealProcessor [" << std::dec << icpu << "]" << std::endl;
			std::cout << "-----------------------------------------" << std::endl;
		}
	}

	system("pause");
}