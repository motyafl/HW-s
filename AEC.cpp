#include <iostream>

void reverseString(char*);

int sizeArr(char *str)
{
	int count{0};
	for(char *pStr = str; *pStr != '\0'; pStr++) {
		count++;
	}
	return count;
}

int main()
{
    std::setlocale(LC_ALL, "");
    char arr[100];
    std::wcout << L"Введите строку: ";
    std::cin.getline(arr, 100);
    int l = sizeArr(arr);
    std::wcout << L"Исходная строка: ";
    for (int i = 0; i < l; i++)
        {
            std::cout << arr[i];
        }
    std::cout << std::endl;


    reverseString(arr);
    std::wcout << L"Перевернутая строка: ";
    for (int i = 0; i < l; i++)
        {
            std::cout << arr[i];
        }
    std::cout << std::endl;

}

void reverseString(char *str)
{
    //arr[1] = arr[0] ^ arr[1];
    //arr[0] ^= arr[1];
    //arr[1] ^= arr[0];

    int j = (sizeArr(str)-1);
    for (int i = 0; i < j; i++) {
        str[j] = str[i] ^ str[j];
        str[i] ^= str[j];
        str[j] ^= str[i];
        j--;
    }
}
