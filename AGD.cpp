#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <cstring>

void quickSort(int* arr, int low, int high) {
    if (low >= high) return;
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    int pi = i + 1;
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
}

void quickSort(int* arr, int& size) {
    if (size > 0) quickSort(arr, 0, size - 1);
}

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int* arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void mergeSort(int* arr, int& size) {
    if (size > 0) mergeSort(arr, 0, size - 1);
}

int binarySearch(const int* arr, int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int* readArrayFromFile(const char* filename, int& size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
        size = 0;
        return nullptr;
    }

    int count = 0;
    int tmp;
    while (file >> tmp) ++count;
    file.close();

    if (count == 0) {
        size = 0;
        return nullptr;
    }

    int* arr = new int[count];
    std::ifstream file2(filename);
    for (int i = 0; i < count; ++i) {
        file2 >> arr[i];
    }
    file2.close();

    size = count;
    return arr;
}

void printArray(const int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i];
        if (i < size - 1) std::cout << " ";
    }
    std::cout << "\n";
}

int* copyArray(const int* src, int size) {
    if (!src || size <= 0) return nullptr;
    int* dest = new int[size];
    std::memcpy(dest, src, size * sizeof(int));
    return dest;
}

int main() {
    int size = 0;
    int* original = readArrayFromFile("input_1.txt", size);
    if (!original || size == 0) {
        std::cout << "Файл пуст или ошибка чтения.\n";
        return 1;
    }

    std::cout << "Исходный массив:\n";
    printArray(original, size);

    // quick sort
    int* arr1 = copyArray(original, size);
    int size1 = size;
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(arr1, size1);
    auto end = std::chrono::high_resolution_clock::now();
    auto quick_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    //merge sort
    int* arr2 = copyArray(original, size);
    int size2 = size;
    start = std::chrono::high_resolution_clock::now();
    mergeSort(arr2, size2);
    end = std::chrono::high_resolution_clock::now();
    auto merge_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "\nОтсортированный массив:\n";
    printArray(arr1, size1); // arr1 и arr2 одинаковы

    std::cout << "\nВремя выполнения:\n";
    std::cout << "Быстрая сортировка: " << quick_time.count() << " мкс\n";
    std::cout << "Сортировка слиянием: " << merge_time.count() << " мкс\n";

    std::cout << "\nВведите число для поиска: ";
    int target;
    std::cin >> target;

    int index = binarySearch(arr1, size1, target);
    if (index != -1) {
        std::cout << "Элемент " << target << " найден на позиции " << index+1 << " (считая с 1)\n";
    } else {
        std::cout << "Элемент " << target << " не найден.\n";
    }

    delete[] original;
    delete[] arr1;
    delete[] arr2;

    return 0;
}
