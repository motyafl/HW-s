#include <iostream>
#include <string>
int main ()
{
	setlocale(LC_ALL, "");
	char str[100] {};
	int vows {0};//счетчик гласных
	int cons {0};//счетчик согласных
	std::wcout << L"Введите строку: ";
	std::cin.getline(str, 100);
	std::wcout << L"Ваша строка: " << str << std::endl;
	for(char *pStr = str; *pStr != '\0'; pStr++) {
		if (*pStr >= 65 && *pStr <= 90) {
			if (*pStr == 65 || *pStr == 69 || *pStr == 73 || *pStr == 79 || *pStr == 85 || *pStr == 89) {
				*pStr = static_cast<char>(*pStr + 1);
				vows++;
			}

			else {
				*pStr = static_cast<char>(*pStr - 1);
				cons ++;
			}
		}

		else if (*pStr >= 97 && *pStr <= 122) {
			if (*pStr == 97 || *pStr == 101 || *pStr == 105 || *pStr == 111 || *pStr == 117 || *pStr == 121) {
				*pStr = static_cast<char> (*pStr + 1);
				vows++;
			}

			else {
				*pStr = static_cast<char> (*pStr - 1);
				cons ++;
			}
		}

		else continue;
	}

	std::wcout << L"Количество гласных: " << vows << L"\nКоличество согласных: " << cons << L"\nПреобразованная строка: " << str << std::endl;


	/*for(int i = 0; i < 100; i++) {
		if (*pStr == '\0') break;
		std::cout << *pStr << std::endl;

		pStr ++;
	}*/
	
}
