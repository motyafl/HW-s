#include <iostream>
#include <string>
int retInt(int &a, int &b)
{
	int n = b;
	b = a;
	a = n;
	return a, b;
}

int retStr(std::string *pStr1, std::string *pStr2)
{
	std::string strn;
	strn = *pStr1;
	*pStr1 = *pStr2;
	*pStr2 = strn;
	return 0;
}
int main()
{
	std::setlocale(LC_ALL, "");
	int a;
	int b;
	std::string str1;
	std::string str2;
	std::wcout << L"Введите первое число: ";
	std::cin >> a;
	std::wcout << L"Введите второе число: ";
	std::cin >> b;
	std::wcout << L"Введите первую строку: ";
	getline(std::cin, str1);
	std::wcout << L"Введите вторую строку: ";
	getline(std::cin, str2);
	retInt(a, b);
	std::wcout << a << "\n" << b << std::endl;
	retStr(&str1, &str2);
	std::wcout << str1 << "\n" << str2 << std::endl;
}
