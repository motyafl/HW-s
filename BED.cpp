#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

namespace Company {

    class Employee {
    protected:
        std::string name;
        int id;
        double salary;

    public:
        Employee(std::string empName, int empId, double empSalary)
            : name(std::move(empName)), id(empId), salary(empSalary) {
            if (salary < 0) {
                throw std::invalid_argument("Зарплата не может быть отрицательной");
            }
        }

        virtual ~Employee() = default;

        Employee& operator=(const Employee& other) {
            if (this != &other) {
                name = other.name;
                id = other.id;
                salary = other.salary;
            }
            return *this;
        }

        std::string getName() const { return name; }
        int getId() const { return id; }
        double getSalary() const { return salary; }

        virtual double calculateBonus() const = 0;
    };

    class Manager : public Employee {
    public:
        Manager(std::string empName, int empId, double empSalary)
            : Employee(std::move(empName), empId, empSalary) {}

        double calculateBonus() const override {
            return salary * 0.25;
        }
    };

    class Developer : public Employee {
    public:
        Developer(std::string empName, int empId, double empSalary)
            : Employee(std::move(empName), empId, empSalary) {}

        double calculateBonus() const override {
            return salary * 0.15;
        }
    };

    class Intern : public Employee {
    public:
        Intern(std::string empName, int empId, double empSalary)
            : Employee(std::move(empName), empId, empSalary) {}

        double calculateBonus() const override {
            return salary * 0.05;
        }
    };

    double calculateTotalManagerBonus(const std::vector<Employee*>& staff) {
        double totalBonus = 0;
        for (const auto& emp : staff) {
            if (dynamic_cast<Manager*>(emp) != nullptr) {
                totalBonus += emp->calculateBonus();
            }
        }
        return totalBonus;
    }
}

int main() {
    try {
        std::cout << "Попытка создать сотрудника с отрицательной зарплатой..." << std::endl;
        Company::Developer badEmp("Алексей", 404, -50000);
    } catch (const std::invalid_argument& e) {
        std::cout << "Перехвачено исключение: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    std::vector<Company::Employee*> staff;
    staff.push_back(new Company::Manager("Елена", 1, 120000));
    staff.push_back(new Company::Developer("Иван", 2, 90000));
    staff.push_back(new Company::Intern("Анна", 3, 30000));
    staff.push_back(new Company::Manager("Олег", 4, 150000));

    std::cout << "Список сотрудников и их бонусы" << std::endl;
    for (const auto& emp : staff) {
        std::cout << "Сотрудник: " << emp->getName() 
                  << ", Базовый оклад: " << emp->getSalary() 
                  << ", Бонус: " << emp->calculateBonus() << std::endl;
    }
    std::cout << std::endl;

    double totalManagersBonus = Company::calculateTotalManagerBonus(staff);
    std::cout << "Суммарный бонус только для управленческого состава (Manager): " 
              << totalManagersBonus << std::endl;

    Company::Manager mgr1("Дмитрий", 5, 100000);
    Company::Manager mgr2("Сергей", 6, 110000);
    mgr1 = mgr2; 
    mgr1 = mgr1;

    for (auto& emp : staff) {
        delete emp;
    }

    return 0;
}
