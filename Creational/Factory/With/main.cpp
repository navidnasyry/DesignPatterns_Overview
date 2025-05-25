#include <iostream>
#include <memory>
#include <string>

// Product interface
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() {}
};

// Concrete products
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Circle\n";
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing a Square\n";
    }
};

// Factory
class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(const std::string& type) {
        if (type == "circle") return std::make_unique<Circle>();
        else if (type == "square") return std::make_unique<Square>();
        else return nullptr;
    }
};

// Usage
int main() {
    auto shape1 = ShapeFactory::createShape("circle");
    auto shape2 = ShapeFactory::createShape("square");

    shape1->draw();
    shape2->draw();

    return 0;
}
