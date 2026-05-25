#include <iostream>
int stringSize(char str[])
{
	int count{0};
	for(char *pStr = str; *pStr != '\0'; pStr++) {
		count++;
	}
	return count;
}

int countVowels(char *pStr, int sSize)
{
	int vows{0};
	//for(pStr; *pStr != '\0'; pStr++) {
	for(int i = 0; i < sSize; i++) {
		if (*pStr == 65 || *pStr == 69 || *pStr == 73 || *pStr == 79 || *pStr == 85 || *pStr == 89 || *pStr == 97 || *pStr == 101 || *pStr == 105 || *pStr == 111 || *pStr == 117 || *pStr == 121) { vows++; pStr++;}
		else pStr++;
	}
	return vows;
}

void replaceSpaces(char str[])
{
	char *pStr = str;
	int sSize = stringSize(str);
	for(int i = 0; i < sSize; i++) {
		if (*pStr == 32) {
			*pStr = 95;
		pStr++;
		}
		else pStr++;
	}
}

int main()
{
	setlocale(LC_ALL, "");
	char str[255]{};
	std::wcout << L"Введите строку: ";
	std::cin.getline(str, 255);
	int sSize = stringSize(str);
	std::wcout << L"Исходная строка: " << std::endl;
	for(int i = 0; i < sSize; i++) std::cout << str[i];
	{
		int vows =  countVowels(str, sSize);
		std::wcout << L"\nКоличество гласных: " << vows << std::endl; 
	}
	replaceSpaces(str);
	std::wcout << L"Модифицированная строка: " << std::endl;
	for(int i = 0; i < sSize; i++) std::cout << str[i];
	std::cout << std::endl;
}
