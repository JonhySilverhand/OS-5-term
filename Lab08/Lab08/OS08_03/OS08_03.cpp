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
    std::cout << "�������� " << pages * PG / 1024 << " KB ����������� ������" << std::endl;

    int* arr = (int*)xmemaddr;
    for (int i = 0; i < countItems; i++)
        arr[i] = i;

    /* � = D1
       � = EC
       � = E8

       �������� D0 = 209, �������� ECE = 3790

       �������� � ����� ������ ��������� 209 * 1024 + 3790 = 217806
    */

    int* byte = arr + 209 * KB + 3790;
    std::cout << "�������� ������ � �����: " << *byte << std::endl;


    if (!VirtualFree(xmemaddr, NULL, MEM_RELEASE))
        std::cout << "������ ��� ������������ ����������� ������" << std::endl;

    return 0;
}