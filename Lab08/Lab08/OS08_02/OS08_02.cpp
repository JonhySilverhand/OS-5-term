#include <iostream>
#include <Windows.h>

int main()
{
	for (int i = 1; i <= 1000000; ++i)
	{
		std::cout << i << ". OS08_02" << std::endl;
		Sleep(1000);
	}
}