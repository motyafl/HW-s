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
// assumes swap(int&, int&) and partition_last(int*, int*) already exist

int* partition_median(int* low, int* high) {
    // compute mid pointer
    int* mid = low + (high - low) / 2;

    // find pointer to median of *low, *mid, *high
    int* medianPtr;
    int a = *low, b = *mid, c = *high;

    if ((a <= b && b <= c) || (c <= b && b <= a))
        medianPtr = mid;
    else if ((b <= a && a <= c) || (c <= a && a <= b))
        medianPtr = low;
    else
        medianPtr = high;

    // move median element to the end so partition_last can use it as pivot
    swap(*medianPtr, *high);

    // now perform the usual partition (pivot is at *high)
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
        throw std::runtime_error("Cannot open input file");

    // First, count how many lines (numbers) in file
    size = 0;
    std::string line;
    while (std::getline(in, line))
        if (!line.empty())
            ++size;

    in.clear();
    in.seekg(0); // rewind file to beginning

    // Now allocate memory and read values
    auto ptr = std::make_unique<int[]>(size);
    int n = 0;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        int number = static_cast<int>(std::stol(line));
        ptr[n++] = number;
    }

    return ptr;
}

void writeArrayToFile(const std::string& filename, int* arr, int size) {
    std::ofstream fout(filename);
    if (!fout)
        throw std::runtime_error("Cannot open output file");
    for (int i = 0; i < size; ++i)
        fout << arr[i] << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " input.txt output.txt\n";
        return 1;
    }

    try {
        int size = 0;
        auto arr = readArrayFromFile(argv[1], size);

        std::cout << "Original array:\n";
        for (int i = 0; i < size; ++i)
            std::cout << arr[i] << " ";
        std::cout << "\n";

        quickSort(arr.get(), arr.get() + size - 1, partition_median);

        std::cout << "Sorted array:\n";
        for (int i = 0; i < size; ++i)
            std::cout << arr[i] << " ";
        std::cout << "\n";

        writeArrayToFile(argv[2], arr.get(), size);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
