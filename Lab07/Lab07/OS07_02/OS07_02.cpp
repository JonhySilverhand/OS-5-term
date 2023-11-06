#include <iostream>
#include <Windows.h>
#include <ctime>

int main()
{
	clock_t start = clock();
	int k = 0;
	bool flag5 = true, flag10 = true;

	while (true)
	{
		k++;
		if ((clock() - start) / CLOCKS_PER_SEC == 5 && flag5)
		{
			std::cout << "Iterations after 5s: " << k << std::endl;
			flag5 = false;
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 10 && flag10)
		{
			std::cout << "Iterations after 10s: " << k << std::endl;
			flag10 = false;
		}
		if ((clock() - start) / CLOCKS_PER_SEC == 15)
		{
			std::cout << "Iterations after 15s: " << k << std::endl;
			break;
		}
	}

	return 0;
}