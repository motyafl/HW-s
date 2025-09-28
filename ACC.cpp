#include <iostream>
#include <string>
int retInt(int &a, int &b)
{
	int n = b;
	b = a;
	a = n;
	return a, b;
}

int retStr(std::wstring *pStr1, std::wstring *pStr2)
{
	std::wstring strn;
	strn = *pStr1;
	*pStr1 = *pStr2;
	*pStr2 = strn;
	return 0;
}
int main()
{
	std::setlocale(LC_ALL, "");
	int a {45};
	int b {90};
	std::wstring str1;
	std::wstring str2;
	std::wcout << L"Первое число равно " << a << std::endl;
	std::wcout << L"Второе число равно " << b << std::endl;
	std::wcout << L"Введите первую строку: ";
	getline(std::wcin, str1);
	std::wcout << L"Введите вторую строку: ";
	getline(std::wcin, str2);
	retInt(a, b);
	std::wcout << L"Числа после обмена:\nПервое число: " << a << L"\nВторое число: " << b << std::endl;
	retStr(&str1, &str2);
	std::wcout << L"Строки после обмена:\nПервая строка: " << str1 << L"\nВторая строка: " << str2 << std::endl;
}
//я не думаю что 3б 4 и 5 пункт этой задачи имеет хотя бы какое-то отношение к ней, как минимум потому что не понятно как задавать массив без запроса его размера у пользователя и почему это просто скопировано из 3 задачи из предыдущего дз, спросить я не могу, поэтому отсылаю на решение 3 задачи предыдущего дз
