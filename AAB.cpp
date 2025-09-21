/*
A programm that inputs the lower case letter and outputs the corresponding upper chase letter
*/
#include <iostream>
int toUpperCase(char a)
{
    char f = static_cast<char>(a-32);//чтобы избежать предупреждения
    std::wcout << L"Соответствующая буква верхнего регистра: " << f;
    return 0;
}

int main()
{
    std::setlocale(LC_ALL, "");
    char a;
    std::wcout << L"Введите букву нижнего регистра: ";
    std::cin >> a;
    toUpperCase(a);
    return 0;
}

