#include <iostream>
#include <fstream>
#include <memory>
#include <cstring>
#include <sstream>
#include <stdexcept>

struct Student {
    char name[50];
    int age;
    double grade;
};

std::unique_ptr<Student[]> readStudents(const std::string& filename, int& count) {
    std::ifstream in(filename);
    if (!in)
        throw std::runtime_error("Не удалось открыть файл");

    count = 0;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) ++count;
    }

    in.clear();
    in.seekg(0);

    auto students = std::make_unique<Student[]>(count);

    int index = 0;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        Student stud;
        if (!(ss >> stud.name >> stud.age >> stud.grade))
            throw std::runtime_error("Некорректные данные в файле");

        students[index++] = stud;
    }

    return students;
}

void findStudent(Student* arr, size_t size) {
	int maxGrade = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i].grade >= arr[maxGrade].grade)
			maxGrade = i;
	}

	std::cout << "У студента " << arr[maxGrade].name << " максимальная оценка из всех: " << arr[maxGrade].grade << " баллов" << std::endl;
}

void swap(Student* arr, int i, int j)
{    
    Student temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}



int partition(Student* arr, int l, int h)
{
    char* pivot = arr[h].name;
    int i = l - 1;

    for (int j = l; j < h; j++)
    {
        if (strcmp(arr[j].name, pivot) <= 0)
        {
            i++;
            swap(arr, i, j);
        }
    }

    swap(arr, i + 1, h);
    return i + 1;
}

void quickSort(Student* arr, int l, int h)
{
    if (l < h)
    {
        int p = partition(arr, l, h);
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1, h);
    }
}

std::unique_ptr<Student[]> copyStudents(const Student* arr, size_t size) {
	auto students = std::make_unique<Student[]>(size);
	for (int i = 0; i < size; i++) {
		students[i] = arr[i];
	}
	return students;
}

int main()
{
        int count = 0;
        auto students = readStudents("students.txt", count);
        auto students_copy = copyStudents(students.get(), count);
	std::cout << "Количество студентов: " << count << "\n";
	quickSort(students_copy.get(), 0, count - 1);
	findStudent(students.get(), count);
	std::cout << "Оригинальный массив до сортировки:" << std::endl;
	for (int i = 0; i < count; i++) {
		std::cout << students[i].name << " " << students[i].age << " " << students[i].grade << std::endl;
	}

	std::cout << "Отсортированная копия массива:" << std::endl;
	for (int i = 0; i < count; i++) {
		std::cout << students_copy[i].name << " " << students_copy[i].age << " " << students_copy[i].grade << std::endl;
	}
}
