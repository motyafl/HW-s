#include <iostream>

class Shape {
private:
    void draw() {
        std::cout << "Отрисовка фигуры" << std::endl;
    }

public:
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    void draw() {
        std::cout << "Отрисовка круга" << std::endl;
    }
};

void processShape(Shape* shape) {
    Circle* circlePtr = dynamic_cast<Circle*>(shape);
    if (circlePtr != nullptr) {
        circlePtr->draw();
    }
}

int main() {
    Circle circle;
    Shape* shapePtr = &circle;
    
    processShape(shapePtr);
    
    return 0;
}

