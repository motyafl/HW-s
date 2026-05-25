#include <iostream>
#include <random>
int aMin;
int aMax;
int& findMaxMin(const int *pArr, int size = 10)//размер массивавсегда 10, но если нужно, можно передать новое значение размера массива
{
	aMax = *pArr;
	aMin = *pArr;
	for(int n = 0; n < size; n++) {
		if (*pArr > aMax) {
			aMax = *pArr; 
			pArr++;
		}
		else if (*pArr < aMin) {
			aMin = *pArr;
			pArr++;
		}
		else pArr++;
	}
	return aMin;
	return aMax;
}

void scaleArray(int *pArr, int size = 10, int k = 2)//стандартный коэффициент масштабирования равен 2
{
	for(int n = 0; n < size; n++) {
		*pArr *= k; 
		pArr++;
	}
}
int main()
{
	//для разнообразия будем заполнять массив чисел случайными щначениями
	std::random_device rd; 
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(-100, 100);

	std::setlocale(LC_ALL, "");
	int arr[10];
	int *pArr = arr;
	for(int n = 0; n < 10; n++) {
		//*pArr = rand()%201-100;
		*pArr = dist(gen);
		pArr++;
	}

	for (int i : arr) i = dist(gen);
	std::cout << "Изначальный массив:\n";
	for(int i : arr) std::cout << i << " ";
	std::cout << std::endl;

	findMaxMin(arr);
	std::cout << "Максимальный элемент массива: " << aMax << "\nМинимальный элемент массива: " << aMin << std::endl;

	scaleArray(arr);
	std::cout << "Итоговый массив:" << std::endl;
	for(int i : arr) std::cout << i << " ";
	std::cout << std::endl;
}
