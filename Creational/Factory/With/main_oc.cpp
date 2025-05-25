#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

// Base product
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() {}
};

// Concrete products
class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Circle\n";
    }
};

class Square : public Shape {
public:
    void draw() const override {
        std::cout << "Drawing Square\n";
    }
};

// Factory with registration
class ShapeFactory {
    using Creator = std::function<std::unique_ptr<Shape>()>;
    static std::unordered_map<std::string, Creator>& getRegistry() {
        static std::unordered_map<std::string, Creator> registry;
        return registry;
    }

public:
    static void registerShape(const std::string& name, Creator creator) {
        getRegistry()[name] = std::move(creator);
    }

    static std::unique_ptr<Shape> createShape(const std::string& name) {
        auto it = getRegistry().find(name);
        if (it != getRegistry().end()) {
            return (it->second)();
        }
        return nullptr;
    }
};

// Registration helper
struct ShapeRegistrar {
    ShapeRegistrar(const std::string& name, std::function<std::unique_ptr<Shape>()> creator) {
        ShapeFactory::registerShape(name, creator);
    }
};

// Register types
ShapeRegistrar registerCircle("circle", []() { return std::make_unique<Circle>(); });
ShapeRegistrar registerSquare("square", []() { return std::make_unique<Square>(); });

int main() {
    auto shape1 = ShapeFactory::createShape("circle");
    auto shape2 = ShapeFactory::createShape("square");

    shape1->draw();
    shape2->draw();

    return 0;
}
