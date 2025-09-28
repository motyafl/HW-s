#include <iostream>
int XOR(int max, int key, int arr[])
{
	int *pArr = arr;
	//for (int *pArr = arr; *pArr != '\n'; *pArr++) {
	//for(int n : int *pArr = arr) {
		//int keyi = static_const<int>(key);		
	for (int i = 0; i < max; i++) {
		*pArr = *pArr ^ key;
		pArr++;
	}
	return 0;
}
int main()
{
	std::setlocale(LC_ALL, "");
	int max;
	std::wcout << L"Введите длину массива: ";
	std::cin >> max;
	int arr[max];
	for (int n = 0; n < max; n++) {
		
		std::wcout << L"Введите " << n+1 << L" число массива: ";
		int v;
		std::cin >> v;
		arr[n] = v;
		std::cout << "\n";
	}

	std::wcout << L"Ваш массив [";
	for (int a : arr) {
		std::wcout << " " << a;
	}
	std::wcout << " ]\n";

	std::wcout << L"Введите ключ для шифрования: ";
	int key;
	std::cin >> key;

	XOR(max, key, arr);
	std::wcout << L"Зашифрованный массив [";
	for (int a : arr) {
		std::wcout << " " << a;
	}
	std::wcout << " ]\n";

	XOR(max, key, arr);
	std::wcout << L"Расшифрованный массив [";
	for (int a : arr) {
		std::wcout << " " << a;
	}
	std::wcout << " ]\n";

}
