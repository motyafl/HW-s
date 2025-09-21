#include <iostream>
#include <string>
bool chechString(std::string str, int len)
{
	for (int i = 0; i < len; i++) {
		if (len >= 50 || !isdigit(str[i])) {
			std::wcout << L"Вы ввели неверное значение или последовательность слишком длинная, попробуйте ввести последовательность еще раз.\n";
			return true;
		}
		else continue;
	}
	return 0;
}

int outNumber(int arr[], int len)
{
	int num;
	while (true) {
		std::wcout << L"Введите порядковый номер цифры: ";
		std::cin >> num;
		if (num < len) {
			break;
		}
		else {
			std::wcout << L"Вы ввели неправильный порядковый номер, попробуйте еще раз.\n";
			continue;
		}
	}
	int out = arr[num-1];
	return out;
}

int main()
{	
	std::setlocale(LC_ALL, "");
	std::string str;
	while (true) {
		std::cout << str;	
		std::wcout << L"Введите последовательность цифр (0-9): ";
		getline(std::cin, str);
		int len = str.length();
		if (chechString(str, len)) continue;
		else break;
	}

	int len = str.length();
	int arr[len];
	for (int i = 0; i < len; i++) {
		arr[i] = str[i] - '0';
	}
	int number = outNumber(arr, len);
	std::wcout << L"Цифра с указанным индексом: " << number << "\n";
}
