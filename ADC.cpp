#include <iostream>

int stringSize(char str[])
{
	int count{0};
	for(char *pStr = str; *pStr != '\0'; pStr++) {
		count++;
	}
	return count;
}

void encrypt(int *max, char *pStr)
{
	int key = 0x5A;
	for (int i = 0; i < *max; i++) {
		*pStr = *pStr ^ key;
		pStr++;
	}
}

void decrypt(int *max, char *pStr)
{
	int key = 0x5A;
	for (int i = 0; i < *max; i++) {
		*pStr = *pStr ^ key;
		pStr++;
	}
}

int main()
{
	setlocale(LC_ALL, "");
	char str[255]{};
	std::cout << "Введите строку: ";
	std::cin.getline(str, 255);
	int max = stringSize(str);
	std::cout << "Исходная строка: " << std::endl;
	for(int i = 0; i < max; i++) std::cout << str[i];
	std::cout << "\nЗашифрованная строка: " << std::endl;
	encrypt(&max, str);
	for(int i = 0; i < max; i++) std::cout << str[i];
	std::cout << "\nРасшифрованная строка: " << std::endl;
	decrypt(&max, str);
	for(int i = 0; i < max; i++) std::cout << str[i];
	std::cout << std::endl;
}
