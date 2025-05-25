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

int main() {
    std::string userInput = "circle";
    Shape* shape;

    if (userInput == "circle") {
        shape = new Circle();
    } else if (userInput == "square") {
        shape = new Square();
    }

    shape->draw();
    delete shape;

    return 0;
}
