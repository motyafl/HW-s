#include <iostream>
#include <random>

int processArray(int[], int);

int main()
{
	std::random_device rd;  // hardware entropy (if available)
	std::mt19937 gen(rd()); // Mersenne Twister engine
	std::uniform_int_distribution<> dist(-100, 100);

	std::setlocale(LC_ALL, "");
	std::wcout << L"Введите размер массива: ";
	int s{};
	std::cin >> s;
	int arr[s];
	int *pArr = arr;
	for(int n = 0; n < s; n++) {
		//*pArr = rand()%201-100;
		*pArr = dist(gen);
		pArr++;
	}

	std::cout << "Изначальный массив: ";
	for(int i : arr) std::cout << i << " ";
	std::cout << std::endl;

	int sum = processArray(arr, s);
	std::cout << "Модифицированный массив: ";
	for(int i : arr) std::cout << i << " ";
	std::cout << "\nСумма положительных чисел: " << sum << std::endl;
}

int processArray(int arr[], int aSize)
{
	int *pointArr = arr;
	int summ {0};
	for(int i = 0; i < aSize; i++) {
		if (*pointArr < 0) {
			*pointArr *= 2;
			pointArr++;
		}
		else {
			const int C = *pointArr;
			const int &refC = *pointArr;
			//for (int i = 0; i < aSize; i++) {
			//	const int &refC = arr[i];
			summ += refC;
			//}
			pointArr++;
		}
	}
	return summ;
}
