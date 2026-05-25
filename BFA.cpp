#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <string>

template <typename T>
struct Point {
    T x, y;
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

template <typename T>
class Polygon : public Shape {
protected:
    std::vector<Point<T>> vertices;

public:
    Polygon(const std::vector<Point<T>>& pts) : vertices(pts) {}
    Polygon(const Polygon& other) : vertices(other.vertices) {}
    virtual ~Polygon() = default;

    Polygon& operator=(const Polygon& other) {
        if (this != &other) {
            vertices = other.vertices;
        }
        return *this;
    }
};

template <typename T>
class Triangle : public Polygon<T> {
private:
    static int count;

public:
    Triangle(const std::vector<Point<T>>& pts) : Polygon<T>(pts) {
        if (pts.size() != 3) {
            throw std::invalid_argument("Для треугольника требуется ровно 3 точки");
        }
        ++count;
    }

    Triangle(const Triangle& other) : Polygon<T>(other) {
        ++count;
    }

    ~Triangle() override {
        --count;
    }

    double area() const override {
        auto& p = this->vertices;
        return std::abs(p[0].x * (p[1].y - p[2].y) + p[1].x * (p[2].y - p[0].y) + p[2].x * (p[0].y - p[1].y)) / 2.0;
    }

    static int getCount() { return count; }

    template <typename U>
    friend void printTriangleInfo(const Triangle<U>& t);
};

template <typename T>
int Triangle<T>::count = 0;

template <typename T>
void printTriangleInfo(const Triangle<T>& t) {
    std::cout << "Треугольник: площадь = " << t.area() << std::endl;
}

template <typename T>
class Rectangle : public Polygon<T> {
private:
    static int count;

public:
    Rectangle(const std::vector<Point<T>>& pts) : Polygon<T>(pts) {
        if (pts.size() != 4) {
            throw std::invalid_argument("Для прямоугольника требуется ровно 4 точки");
        }
        ++count;
    }

    Rectangle(const Rectangle& other) : Polygon<T>(other) {
        ++count;
    }

    ~Rectangle() override {
        --count;
    }

    double area() const override {
        auto& p = this->vertices;
        double side1 = std::sqrt(std::pow(p[1].x - p[0].x, 2) + std::pow(p[1].y - p[0].y, 2));
        double side2 = std::sqrt(std::pow(p[2].x - p[1].x, 2) + std::pow(p[2].y - p[1].y, 2));
        return side1 * side2;
    }

    static int getCount() { return count; }

    template <typename U>
    friend void printRectangleInfo(const Rectangle<U>& r);
};

template <typename T>
int Rectangle<T>::count = 0;

template <typename T>
void printRectangleInfo(const Rectangle<T>& r) {
    std::cout << "Прямоугольник: площадь = " << r.area() << std::endl;
}

int main() {
    try {
        std::vector<Point<double>> invalidPoints = {{0, 0}, {1, 1}};
        
        try {
            std::cout << "Попытка создания фигуры с некорректным числом точек..." << std::endl;
            Triangle<double> badTri(invalidPoints);
        } catch (const std::invalid_argument& e) {
            std::cout << "Внутренний catch: " << e.what() << std::endl;
            throw; 
        }
    } catch (const std::exception& e) {
        std::cout << "Внешний catch: Фигура не была создана из-за ошибки." << std::endl;
    }

    std::vector<Point<double>> triPoints = {{0, 0}, {4, 0}, {0, 3}};
    Triangle<double> tri(triPoints);
    printTriangleInfo(tri);

    return 0;
}

