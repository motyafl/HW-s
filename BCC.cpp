#include <iostream>
#include <string>
#include <cmath>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Rectangle : virtual public Shape {
private:
    double width;
    double height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override { return width * height; }
    friend class ShapePrinter;
};

class Circle : virtual public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.1415926535 * radius * radius; }
    friend class ShapePrinter;
};

class Triangle : virtual public Shape {
private:
    double a, b, c;
public:
    Triangle(double sideA, double sideB, double sideC) : a(sideA), b(sideB), c(sideC) {}
    double area() const override {
        double p = (a + b + c) / 2.0;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }
    friend class ShapePrinter;
};

class Color {
private:
    std::string hexColor;
public:
    Color(std::string col) : hexColor(std::move(col)) {}
    virtual ~Color() = default;
    std::string getColor() const { return hexColor; }
};

class ColoredShape : public Shape, public Color {
private:
    Shape* concreteShape;
public:
    ColoredShape(Shape* shape, std::string col) 
        : Color(std::move(col)), concreteShape(shape) {}
    
    ~ColoredShape() override { delete concreteShape; }

    double area() const override { return concreteShape->area(); }
    friend class ShapePrinter;
};

class ShapePrinter {
public:
    void printRectangle(const Rectangle& r) const {
        std::cout << "Прямоугольник: стороны = " << r.width << "x" << r.height << ", площадь = " << r.area() << std::endl;
    }
    void printCircle(const Circle& c) const {
        std::cout << "Круг: радиус = " << c.radius << ", площадь = " << c.area() << std::endl;
    }
    void printTriangle(const Triangle& t) const {
        std::cout << "Треугольник: стороны = " << t.a << ", " << t.b << ", " << t.c << ", площадь = " << t.area() << std::endl;
    }
    void printColoredShape(const ColoredShape& cs) const {
        std::cout << "Окрашенная фигура: цвет = " << cs.getColor() << ", площадь = " << cs.area() << std::endl;
    }
};

void callAreaViaPointer(const Shape* shape) {
    double (Shape::*memPtr)() const = &Shape::area;
    std::cout << "Вычисленная площадь: " << (shape->*memPtr)() << std::endl;
}

int main() {
    Rectangle* rect = new Rectangle(4.0, 5.0);
    Circle* circ = new Circle(3.0);
    Triangle* tri = new Triangle(3.0, 4.0, 5.0);
    ColoredShape* redCircle = new ColoredShape(new Circle(5.0), "#FF0000");

    double (Shape::*areaMethodPtr)() const = &Shape::area;

    std::cout << "Площадь прямоугольника: " << (rect->*areaMethodPtr)() << std::endl;
    std::cout << "Площадь круга: " << (circ->*areaMethodPtr)() << std::endl;
    std::cout << "Площадь треугольника: " << (tri->*areaMethodPtr)() << std::endl;
    std::cout << "Площадь окрашенной фигуры: " << (redCircle->*areaMethodPtr)() << std::endl;
    std::cout << std::endl;

    ShapePrinter printer;
    printer.printRectangle(*rect);
    printer.printCircle(*circ);
    printer.printTriangle(*tri);
    printer.printColoredShape(*redCircle);
    std::cout << std::endl;

    callAreaViaPointer(rect);
    callAreaViaPointer(redCircle);

    delete rect;
    delete circ;
    delete tri;
    delete redCircle;

    return 0;
}

