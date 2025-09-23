#include <iostream>
#include <string>
bool chechString(std::string &str, int len)
{
	for (char i : str) {
		if (len >= 50 || !isdigit(i)) {
			std::wcout << L"Вы ввели неверное значение или последовательность слишком длинная, попробуйте ввести последовательность еще раз.\n";
			return true;
		}
		else continue;
	}
	return 0;
}

int outNumber(int arr[], int len)//мы не знаем конечного размера массива, значит не можем передать его по ссылке...
{
	while (true) {
		int num;
		std::wcout << L"Введите порядковый номер цифры: ";
		std::cin >> num;
		//if (outNumber(len, num)) {
		if (num >= 0 or num < len) {
			return arr[num-1];
			//std::wcout << L"Цифра с индексом " << num << ": " << arr[num - 1] << "\n";
			break;
		}
		else {
			std::wcout << L"Вы ввели неправильный порядковый номер, попробуйте еще раз.\n";
			continue;
		}
	}
}

int main()
{	
	std::setlocale(LC_ALL, "");
	std::string str;
	int len;

	while (true) {
		std::wcout << L"Введите последовательность цифр (0-9): ";
		getline(std::cin, str);
		int &lenRef = len;
		lenRef = str.length();
		if (chechString(str, lenRef)) continue;
		else break;
	}

	int arr[len];
	for (int i = 0; i < len; i++) {
		arr[i] = str[i] - '0';
	}
	//std::wcout << L"Цифра с индексом " << num << ": " << arr[num - 1] << "\n";
	std::cout << outNumber(arr, len) << '\n' << std::endl;

/*	while (true) {
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
	}*/
}
