/*
A programm that calculates the expression by inputed values
*/
#include <iostream>
#include <iomanip>
int calculateExpression(double a, double b, double f)
{
    double res {(a + b - f/a) + f*a*a - (a + b)}; //правильней написать f*a*a-f/a, это выражение получается после раскрытия скобок
    std::cout << "(a + b - f/a) + f*a*a - (a + b) = " << std::fixed << std::setprecision(4) << res;
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    double a, b, f;
    std::wcout << L"Введите число а: ";
    std::cin >> a;
    std::wcout << L"Введите число b: ";
    std::cin >> b;
    std::wcout << L"Введите число f: ";
    std::cin >> f;
    calculateExpression(a, b, f);
    return 0;
}
