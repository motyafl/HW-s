#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int* partition_last(int* low, int* high) {
    int pivot = *high;
    int* i = low - 1;
    for (int* j = low; j < high; ++j) {
        if (*j <= pivot) {
            ++i;
            swap(*i, *j);
        }
    }
    swap(*(i + 1), *high);
    return (i + 1);
}

int* partition_first(int* low, int* high) {
    int pivot = *low;
    int* i = low;
    for (int* j = low + 1; j <= high; ++j) {
        if (*j <= pivot) {
            ++i;
            swap(*i, *j);
        }
    }
    swap(*low, *i);
    return i;
}

int* partition_median(int* low, int* high) {
    int* mid = low + (high - low) / 2;

    int* medianPtr;
    int a = *low, b = *mid, c = *high;

    if ((a <= b && b <= c) || (c <= b && b <= a))
        medianPtr = mid;
    else if ((b <= a && a <= c) || (c <= a && a <= b))
        medianPtr = low;
    else
        medianPtr = high;

    swap(*medianPtr, *high);

    return partition_last(low, high);
}
void quickSort(int* low, int* high,
               int* (*partitionFunc)(int*, int*)) {
    if (low < high) {
        int* p = partitionFunc(low, high);
        quickSort(low, p - 1, partitionFunc);
        quickSort(p + 1, high, partitionFunc);
    }
}

std::unique_ptr<int[]> readArrayFromFile(const std::string& filename, int& size) {
    std::ifstream in(filename);
    if (!in)
        throw std::runtime_error("Не удалось открыть файл");

    size = 0;
    std::string line;
    while (std::getline(in, line))
        if (!line.empty())
            ++size;

    in.clear();
    in.seekg(0); 

    auto ptr = std::make_unique<int[]>(size);
    int n = 0;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        int number = static_cast<int>(std::stol(line));
        ptr[n++] = number;
    }

    return ptr;
}

void writeArrayToFile(const std::string& filename, int* arr, int& size) {
    std::ofstream fout(filename);
    for (int i = 0; i < size; ++i)
        fout << arr[i] << "\n";
}

int main(int argc, char* argv[]) {
	int size = 0;
	auto arr = readArrayFromFile(argv[1], size);

	std::cout << "Изначальный массив:\n";
        for (int i = 0; i < size; ++i)
            std::cout << arr[i] << " ";
        std::cout << "\n";

        quickSort(arr.get(), arr.get() + size - 1, partition_median); //какой элемент выбрать first last или median

        std::cout << "Отсортированный массив:\n";
        for (int i = 0; i < size; ++i)
            std::cout << arr[i] << " ";
        std::cout << "\n";

        writeArrayToFile(argv[2], arr.get(), size);
}
