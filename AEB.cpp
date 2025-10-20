#include <iostream>

int factorial(int n)
{
    if (n == 0 || n == 1)
       return 1;
    return n*factorial(n-1);
}

int fibonacci(int n)
{
    if (n <= 1)
       return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int compute(int &nRef, int (*func)(int))
{
    return func(nRef);
}

int main()
{
    setlocale(LC_ALL, "");
    int n{};
    int choise{};
    std::wcout << L"Выберете функцию(1-факториал, 2-Фибоначчи): ";
    std::cin >> choise;
    std::wcout << L"Введите число: ";
    std::cin >> n;
    switch (choise) {
           case 1:
           std::wcout << n << L" факториал равняется " << compute(n, factorial) << std::endl;
           break;
           case 2:
           std::wcout << n << L" число Фибоначчи равно " << compute(n, fibonacci) << std::endl;
           break;
           default:
           std::wcout << L"Вы ввели неправильный номер функции" << std::endl;
    }
}
