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
	HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 4096 * 1024, 0);
	sh(heap);

	int* x1 = (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 300000 * sizeof(int));
	std::cout << "\nAddress: " << x1 << "\n\n";
	sh(heap);

	HeapFree(heap, HEAP_NO_SERIALIZE, x1);
	sh(heap);
	HeapDestroy(heap);
}