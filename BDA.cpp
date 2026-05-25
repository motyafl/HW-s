#include <iostream>
#include <string>

class Vehicle {
private:
    int speed;
    double weight;
    static int objectCount;

public:
    Vehicle(int s, double w) : speed(s), weight(w) {
        ++objectCount;
    }

    Vehicle(const Vehicle& other) : speed(other.speed), weight(other.weight) {
        ++objectCount;
    }

    virtual ~Vehicle() {
        --objectCount;
    }

    virtual void info() const {
        std::cout << "Транспортное средство: Скорость = " << speed 
                  << " км/ч, Вес = " << weight << " кг" << std::endl;
    }

    static int getObjectCount() {
        return objectCount;
    }

    friend bool compareByWeight(const Vehicle& v1, const Vehicle& v2);
};

int Vehicle::objectCount = 0;

bool compareByWeight(const Vehicle& v1, const Vehicle& v2) {
    return v1.weight > v2.weight;
}

class Car : public Vehicle {
private:
    std::string brand;

public:
    Car(int s, double w, std::string b) : Vehicle(s, w), brand(std::move(b)) {}

    void info() const override {
        Vehicle::info();
        std::cout << "Марка: " << brand << std::endl;
    }
};

class ElectricCar : public Car {
private:
    double batteryCapacity;

public:
    ElectricCar(int s, double w, std::string b, double bc) 
        : Car(s, w, std::move(b)), batteryCapacity(bc) {}

    void info() const override {
        Car::info();
        std::cout << "Емкость батареи: " << batteryCapacity << " кВтч" << std::endl;
    }

    virtual double range() const = 0;

    operator double() const {
        return batteryCapacity;
    }
};

class PremiumElectricCar : public ElectricCar {
public:
    PremiumElectricCar(int s, double w, std::string b, double bc) 
        : ElectricCar(s, w, std::move(b), bc) {}

    double range() const override {
        return (*this) * 5.5; 
    }
};

int main() {
    Vehicle* v1 = new Car(180, 1500.0, "BrandA");
    Vehicle* v2 = new PremiumElectricCar(220, 2100.0, "BrandB", 85.0);

    v1->info();
    v2->info();

    if (compareByWeight(*v1, *v2)) {
        std::cout << "Первое транспортное средство тяжелее второго" << std::endl;
    } else {
        std::cout << "Второе транспортное средство тяжелее или равно по весу первому" << std::endl;
    }

    PremiumElectricCar* eCar = dynamic_cast<PremiumElectricCar*>(v2);
    if (eCar) {
        double capacity = *eCar;
        std::cout << "Извлеченная емкость батареи через оператор приведения: " << capacity << " кВтч" << std::endl;
        std::cout << "Максимальный пробег: " << eCar->range() << " км" << std::endl;
    }

    delete v1;
    delete v2;

    return 0;
}

