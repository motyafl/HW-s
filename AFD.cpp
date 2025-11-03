#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <sstream>
#include <stdexcept>

struct Employee {
    std::string name;
    int age;
    double salary;
};

std::unique_ptr<Employee[]> readEmployees(const std::string& filename, int& count) {
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

    auto employees = std::make_unique<Employee[]>(count);

    int index = 0;
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        Employee emp;
        if (!(ss >> emp.name >> emp.age >> emp.salary))
            throw std::runtime_error("Некорректные данные в файле");

        employees[index++] = emp;
    }

    return employees;
}

Employee* findEmployee(Employee* employees, int count, const std::string& name) {
    for (int i = 0; i < count; ++i) {
        if (employees[i].name == name)
            return &employees[i];
    }
    return nullptr;
}

Employee* findEmployee(Employee* employees, int count, int age) {
    for (int i = 0; i < count; ++i) {
        if (employees[i].age == age)
            return &employees[i];
    }
    return nullptr;
}

void changeSalary(Employee& emp, double newSalary) {
    emp.salary = newSalary;
}

void writeEmployees(const std::string& filename, Employee* employees, int count) {
    std::ofstream out(filename);

    for (int i = 0; i < count; ++i) {
        out << employees[i].name << " " << employees[i].age << " " << employees[i].salary << "\n";
    }
}

int countAboveThreshold(Employee employees[], int count, double threshold) {
    if (count == 0)
        return 0; 

    int current = 0;
    if (employees[count - 1].salary > threshold) {
        current = 1;
    }

    return current + countAboveThreshold(employees, count - 1, threshold);
}

int main(int argc, char* argv[]) 
{
        int count = 0;
        auto employees = readEmployees(argv[1], count);

        std::cout << "Считано сотрудников: " << count << "\n";

        std::string searchName = "Alisa"; //поиск по имени
        Employee* found = findEmployee(employees.get(), count, searchName);
        if (found) {
            std::cout << "Найден сотрудник " << found->name << " с зарплатой " << found->salary << "\n";
            changeSalary(*found, found->salary + 500); // повышение зарплаты
        } else {
            std::cout << "Сотрудник " << searchName << " не найден.\n";
        }

        double threshold = 100000;
        int above = countAboveThreshold(employees.get(), count, threshold);
        std::cout << "Количество сотрудников с зарплатой > " << threshold << ": " << above << "\n";

	writeEmployees(argv[2], employees.get(), count);
	std::cout << "Результаты записаны в " << argv[2] << "\n";
}
