#include <iostream>
#include <Windows.h>

void sh(HANDLE pheap)
{
	PROCESS_HEAP_ENTRY phe;
	phe.lpData = NULL;
	while (HeapWalk(pheap, &phe))
	{
		// R - начало непрерывной области
		// U - нераспределенная область 
		// B - распределенная область
		std::cout << "-- address = " << std::showbase << std::hex << phe.lpData <<
			", size = " << std::dec << phe.cbData <<
			((phe.wFlags & PROCESS_HEAP_REGION) ? " R" : "") <<
			((phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) ? " U" : "") <<
			((phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) ? " B" : "") << "\n";
	}
}

int main()
{
	HANDLE pheap = GetProcessHeap();
	std::cout << "\n==================  BEFORE  ==================\n\n";
	sh(pheap);

	int size = 300000;
	int* m = new int[size];
	std::cout << "-- m = " << std::showbase << std::hex << m << ", size = " << std::dec << size << '\n';

	std::cout << "\n==================  AFTER  ==================\n\n";
	sh(pheap);
}