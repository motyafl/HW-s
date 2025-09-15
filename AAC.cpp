/*
A programm that splits a five-digit number into digits in order
*/
#include <iostream>
#include <cstdlib>
int printDigits(int num)
{
    std::wcout << L"Разложенное число: \n";
    for (int i = 10000; i > 0; i = i/10)
        {
            std::cout << abs(num/i) << "\n";//берем модуль числа чтобы иметь возможность работать с отрицательными числами
            num = num%i;
        }
    return 0;
}
int main()
{
    std::setlocale(LC_ALL, "Russian");
    int num;
    std::wcout << L"Введите целое пятизначное число: ";
    std::cin >> num;
    printDigits(num);
    return 0;
}
