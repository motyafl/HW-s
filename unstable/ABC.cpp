#include <iostream>
int reverseOrder(int arr[], int len)
{
	std::wcout << L"Ваш массив в обратном порядке { "; 
	for (int i = len - 1; i >= 0; i--) {
		std::wcout << arr[i] << " ";
	}
	std::wcout << "}\n";
	return 0;
}
int main()
{
	int len;
	while (true) {
		std::setlocale(LC_ALL, "");
		std::wcout << L"Введите размер массива: ";
		std::cin >> len;

		if (len > 0 and len < 100) break;
		else std::wcout << L"Вы ввели неверный размер массива, повторите попытку.\n";
	}
	

	int arr[len];
	for (int i = 0; i < len; i++) {
		double num;//устанавливаем тип double чтобы проверить является ли введенное число целым, т.к. без этого программа просто "обрежет" число
		while (true) {
			std::wcout << L"Введите " << i+1 << L" число массива: ";
			std::cin >> num;
			if (num != static_cast<int>(num))//проверяем равно ли введенное число его целому эквиваленту
			{
				std::wcout << L"Вы ввели неверное число, повторите попытку.\n";
			}

			else break;
		}
		arr[i] = num;
	}

	reverseOrder(arr, len);
}
