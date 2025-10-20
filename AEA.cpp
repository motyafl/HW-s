#include <iostream>
#include <random>
#include <memory>

void swap(std::unique_ptr<int[]> &arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int partition(std::unique_ptr<int[]> &arr, int l, int h)
{
    int pivot = arr[h];
    int i = l - 1;

    for (int j = l; j < h; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, h);
    return i + 1;
}

double partition(std::unique_ptr<int[]> &arr, double l, double h)
{
    int pivot = arr[h];
    int i = l - 1;

    for (int j = l; j < h; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, h);
    return i + 1;
}


void quickSort(std::unique_ptr<int[]> &arr, int l, int h)
{
    if (l < h)
    {
        int p = partition(arr, l, h);
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1, h);
    }
}

int main()
{
    std::setlocale(LC_ALL, "");
    std::random_device rd;  // hardware entropy (if available)
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(-100, 100);

    int aSize = 10;
    std::unique_ptr<int[]> aPtr(new int[aSize]{});
    for (int i = 0; i < aSize; i++) {
        aPtr[i] = dist(gen);
    }

    std::wcout << L"Изначальный массив: ";
    for (int i = 0; i < aSize; i++)
        std::cout << aPtr[i] << " ";
    std::cout << std::endl;

    quickSort(aPtr, 0, aSize - 1);

    std::wcout << L"Отсортированный массив: ";
    for (int i = 0; i < aSize; i++)
        std::cout << aPtr[i] << " ";
    std::cout << std::endl;
}
