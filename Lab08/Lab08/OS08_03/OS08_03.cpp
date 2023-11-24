#include <iostream>
#include <Windows.h>
#define KB (1024)
#define MB (1024 * KB)
#define PG (4 * KB)

int main()
{
    setlocale(LC_ALL, "Rus");
    int pages = 256;
    int countItems = pages * PG / sizeof(int);

    LPVOID xmemaddr = VirtualAlloc(NULL, pages * PG, MEM_COMMIT, PAGE_READWRITE);
    std::cout << "Выделено " << pages * PG / 1024 << " KB виртуальной памяти" << std::endl;

    int* arr = (int*)xmemaddr;
    for (int i = 0; i < countItems; i++)
        arr[i] = i;

    /* С = D1
       м = EC
       и = E8

       Страница D0 = 209, смещение ECE = 3790

       Значение в байте должно получится 209 * 1024 + 3790 = 217806
    */

    int* byte = arr + 209 * KB + 3790;
    std::cout << "Значение памяти в байте: " << *byte << std::endl;


    if (!VirtualFree(xmemaddr, NULL, MEM_RELEASE))
        std::cout << "Ошибка при освобождении вирутальной памяти" << std::endl;

    return 0;
}