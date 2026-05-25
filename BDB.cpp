#include <iostream>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Rectangle : public Shape {
protected:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

    void setDimensions(double w, double h) {
        width = w;
        height = h;
    }
};

class Colored {
private:
    std::string color;

public:
    Colored(std::string c) : color(std::move(c)) {}
    virtual ~Colored() = default;

    std::string getColor() const {
        return color;
    }

    void setColor(std::string c) {
        color = std::move(c);
    }
};

class ColoredRectangle : public Rectangle, public Colored {
public:
    ColoredRectangle(double w, double h, std::string c) 
        : Rectangle(w, h), Colored(std::move(c)) {}

    double area() const override {
        return Rectangle::area();
    }

private:
    using Rectangle::setDimensions;

public:
    friend void printInfo(const ColoredRectangle& cr);
};

void printInfo(const ColoredRectangle& cr) {
    std::cout << "Цвет фигуры: " << cr.getColor() << ", Площадь фигуры: " << cr.area() << std::endl;
}

int main() {
    Shape* shape = new ColoredRectangle(10.0, 5.0, "Красный");

    ColoredRectangle* cr = dynamic_cast<ColoredRectangle*>(shape);
    if (cr != nullptr) {
        printInfo(*cr);
    }

    delete shape;
    return 0;
}

