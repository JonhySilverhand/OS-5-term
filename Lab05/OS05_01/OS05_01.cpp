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

	std::cout << "-----------------------------------------" << std::endl;

	std::cout << "Current PID [" << pid << "]" << std::endl;
	DWORD procPriority = GetPriorityClass(hp);

	switch(procPriority)
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

	std::cout << "-----------------------------------------" << std::endl;

	std::cout << "Current TID [" << tid << "]" << std::endl;
	DWORD thPriority = GetThreadPriority(ht);

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

	DWORD_PTR pa = NULL, sa = NULL, icpu = -1;
	char buffer[15];
	if (!GetProcessAffinityMask(hp, &pa, &sa))
		throw "GetProcessAffinityMask";
	
	_itoa_s(pa, buffer, 2);
	std::cout << "Process affinity Mask: " << buffer << ", HEX: " << std::showbase << std::hex << pa << std::endl;
	_itoa_s(sa, buffer, 2);
	std::cout << "System affinity Mask:  " << buffer << ", HEX: " << std::showbase << std::hex << sa << std::endl;

	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	std::cout << "Max processors count:  " << std::dec << sys_info.dwNumberOfProcessors << std::endl;
	icpu = SetThreadIdealProcessor(ht, MAXIMUM_PROCESSORS);
	std::cout << "Thread IdealProcessor: " << std::dec << icpu << std::endl;

	system("pause");
}