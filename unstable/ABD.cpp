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

bool outNumber(int len, int num)
{
	if (num <= 0 or num > len) return false;
	else return true;
}

int main()
{	
	std::setlocale(LC_ALL, "");
	std::string str;
	while (true) {
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

	while (true) {
		int num;
		std::wcout << L"Введите порядковый номер цифры: ";
		std::cin >> num;
		if (outNumber(len, num)) {
			std::wcout << L"Цифра с индексом " << num << ": " << arr[num - 1] << "\n";
			break;
		}
		else {
			std::wcout << L"Вы ввели неправильный порядковый номер, попробуйте еще раз.\n";
			continue;
		}
	}
}
