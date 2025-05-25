## 🏭 Factory Pattern – In Practice

### 📝 When to Use Factory

The **Factory Pattern** is ideal when:

* You need to create objects **without specifying their exact class**.
* The creation logic is **complex, conditional**, or requires **encapsulation**.
* You want to **centralize and manage instantiation**, especially when dealing with inheritance or interfaces.

📦 **Example Scenario**: Suppose you’re developing a graphics editor that supports multiple shapes like `Circle`, `Square`, `Triangle`. You don’t want to write `new Circle()` or `new Square()` everywhere. Instead, use a factory to create shapes based on user input.

---

### ✅ With Factory Pattern (C++)

```cpp
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
```

---

### ❌ Without Factory Pattern

```cpp
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
```

---

## 🚫 Disadvantages of Not Using Factory

When you **don't** use the Factory pattern in the right place:

1. **Tight Coupling:**

   * Classes are directly dependent on concrete classes instead of abstractions, reducing flexibility.

2. **Scattered Object Creation Logic:**

   * `new` expressions are repeated in multiple places. If the logic changes (e.g., you add caching or logging), you need to update many areas.

3. **Hard to Maintain or Extend:**

   * Adding a new shape (like `Triangle`) requires changes across multiple files or locations.

4. **Violation of Open/Closed Principle:**

   * Modifying client code each time a new type is added violates the principle of being open for extension but closed for modification.

---

### ⚠️ Note on Builder vs Factory

If you're wondering about using **Builder vs Factory**, here's the distinction:

| Use Case            | Builder                         | Factory                                 |
| ------------------- | ------------------------------- | --------------------------------------- |
| Object Complexity   | High (multi-step creation)      | Low to medium (focus on type selection) |
| Object Variants     | Same process, different outputs | Different objects from a selection pool |
| Control Granularity | Fine-grained                    | Coarse-grained                          |



Excellent question! You're right to raise a concern about the **Open/Closed Principle** in the **Factory Design Pattern** — it *can* violate it in its basic form. Let’s break this down.

---

## 🧩 Does the Factory Pattern Violate Open/Closed Principle?

### 🛑 Yes — In Its Basic Form

In a **basic Factory**, like this:

```cpp
if (type == "circle") return new Circle();
else if (type == "square") return new Square();
```

👉 Every time you add a new type (e.g., `Triangle`), you have to **modify the factory code**. This **violates the Open/Closed Principle**, which states:

> "Software entities should be open for extension but closed for modification."

---

## ✅ How to Solve It: Make Factory Open/Closed

You can solve this by **decoupling the factory logic from the specific product types**, using **a registry or map of creators**.

---

### ✅ Open/Closed Factory Using a Registry (C++ Example)

```cpp
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
```

---

## 🧠 Benefits

* 💡 **Adding new shapes requires no changes to `ShapeFactory` itself**.
* 🧱 New types can be registered in different compilation units (i.e., plugins).
* ✅ Complies with **Open/Closed Principle**.

---

## 📌 Summary

| Design                     | Open/Closed Compliant? | Drawbacks                                              |
| -------------------------- | ---------------------- | ------------------------------------------------------ |
| **Basic Factory**          | ❌ No                   | Must modify factory to add new types                   |
| **Registry-Based Factory** | ✅ Yes                  | Slightly more complex, requires registration mechanism |

---
