#include <iostream>

int countVowels(char* str) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        char c = str[i];
        char lower = static_cast<char>(c | 32); //приводим буквы к нижнему регистру с помощью побитового или 

        if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
            ++count;
        }
    }
    return count;
}

int countVowels(const std::string& str) {
    int count = 0;
    for (char c : str) {
        char lower = static_cast<char>(c | 32); //приводим буквы к нижнему регистру с помощью побитового или 

        if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
            ++count;
        }
    }
    return count;
}

int main ()
{
	setlocale(LC_ALL, "");
	char str[100] {};
	int vows {0};//счетчик гласных
	std::wcout << L"Введите строку: ";
	std::cin.getline(str, 100);
	std::wcout << L"Ваша строка: " << str << std::endl;
	std::wcout << L"Количество гласных: " << countVowels(str) << std::endl;
}	
