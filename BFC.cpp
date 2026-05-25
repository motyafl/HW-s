#include <iostream>
#include <string>
#include <stdexcept>

class Person {
protected:
    std::string name;
    int age;

public:
    Person(std::string n, int a) : name(std::move(n)), age(a) {
        if (age < 0) {
            throw std::invalid_argument("Возраст не может быть отрицательным");
        }
    }

    virtual ~Person() = default;

    virtual void printInfo() const {
        std::cout << "Имя: " << name << ", Возраст: " << age;
    }

    friend bool compareAge(const Person& p1, const Person& p2);
};

bool compareAge(const Person& p1, const Person& p2) {
    return p1.age < p2.age;
}

class Employee : virtual public Person {
protected:
    double salary;

public:
    Employee(std::string n, int a, double s) : Person(std::move(n), a), salary(s) {}
    ~Employee() override = default;

    void printInfo() const override {
        Person::printInfo();
        std::cout << ", Зарплата: " << salary;
    }
};

class Student : virtual public Person {
protected:
    double gpa;

public:
    Student(std::string n, int a, double g) : Person(std::move(n), a), gpa(g) {}
    ~Student() override = default;

    void printInfo() const override {
        Person::printInfo();
        std::cout << ", Средний балл: " << gpa;
    }
};

class WorkingStudent : public Employee, public Student {
public:
    WorkingStudent(std::string n, int a, double s, double g)
        : Person(std::move(n), a), Employee(name, age, s), Student(name, age, g) {}

    ~WorkingStudent() override = default;

    void printInfo() const override {
        Employee::printInfo();
        std::cout << ", Средний балл: " << gpa << " (Режим: Работающий студент)";
    }

private:
    using Student::gpa; // Скрытие прямого изменения или доступа к gpa внешними средствами Student
};

int main() {
    try {
        Person* p = new WorkingStudent("Кирилл", 20, 45000, 4.8);
        p->printInfo();
        std::cout << std::endl;

        WorkingStudent* ws = dynamic_cast<WorkingStudent*>(p);
        if (ws) {
            std::cout << "Успешное приведение к типу WorkingStudent" << std::endl;
        }

        delete p;

        std::cout << "Попытка создания объекта с некорректным возрастом..." << std::endl;
        Student badStudent("Анна", -5, 4.2);

    } catch (const std::invalid_argument& e) {
        std::cout << "Перехвачено исключение: " << e.what() << std::endl;
    }

    return 0;
}

