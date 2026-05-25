#include <iostream>
#include <string>
#include <vector>

class Car {
private:
    std::string brand;
    std::string model;
    int year;

public:
    Car() : brand(""), model(""), year(0) {}

    Car(std::string brand, std::string model, int year) 
        : brand(std::move(brand)), model(std::move(model)), year(year) {}

    Car(const Car& other) : brand(other.brand), model(other.model), year(other.year) {}

    virtual ~Car() = default;

    std::string getBrand() const { return brand; }
    void setBrand(std::string brand) {
        if (brand.empty()) {
            std::cout << "Предупреждение: Марка не может быть пустой строкой!" << std::endl;
            return;
        }
        this->brand = brand;
    }

    std::string getModel() const { return model; }
    void setModel(std::string model) {
        if (model.empty()) {
            std::cout << "Предупреждение: Модель не может быть пустой строкой!" << std::endl;
            return;
        }
        this->model = model;
    }

    int getYear() const { return year; }
    void setYear(int year) {
        if (year < 1886 || year > 2026) {
            std::cout << "Предупреждение: Некорректный год автомобиля!" << std::endl;
            return;
        }
        this->year = year;
    }

    virtual void displayInfo() const {
        std::cout << "Автомобиль: " << brand << " " << model << ", Год выпуска: " << year << std::endl;
    }
};

class Truck : public Car {
private:
    double loadCapacity;

public:
    Truck() : Car(), loadCapacity(0.0) {}

    Truck(std::string brand, std::string model, int year, double loadCapacity)
        : Car(std::move(brand), std::move(model), year), loadCapacity(loadCapacity) {}

    Truck(const Truck& other) : Car(other), loadCapacity(other.loadCapacity) {}

    double getLoadCapacity() const { return loadCapacity; }
    void setLoadCapacity(double loadCapacity) {
        if (loadCapacity < 0.0) {
            std::cout << "Предупреждение: Грузоподъемность не может быть отрицательной!" << std::endl;
            return;
        }
        this->loadCapacity = loadCapacity;
    }

    void displayInfo() const override {
        std::cout << "Грузовик: " << getBrand() << " " << getModel() 
                  << ", Год выпуска: " << getYear() 
                  << ", Грузоподъемность: " << loadCapacity << " т" << std::endl;
    }
};

int main() {
    const int size = 4;
    Car* fleet[size];

    fleet[0] = new Car("Toyota", "Camry", 2021);
    fleet[1] = new Truck("KAMAZ", "65115", 2018, 15.0);
    fleet[2] = new Car("BMW", "M5", 2023);
    fleet[3] = new Truck("Volvo", "FH16", 2022, 25.5);

    std::cout << "Информация об автопарке" << std::endl;
    for (int i = 0; i < size; ++i) {
        fleet[i]->displayInfo();
    }

    for (int i = 0; i < size; ++i) {
        delete fleet[i];
    }

    return 0;
}

