## 🔌 Adapter Design Pattern

### 🧠 Purpose

The **Adapter Pattern** is used to **bridge the gap between incompatible interfaces**. It allows you to **reuse existing functionality** without modifying the original source code by adapting it to work with a new interface.

---

### 📝 When to Use the Adapter Pattern

* When you want to **use a class that doesn’t match the required interface**.
* When you want to integrate **legacy code or third-party libraries** into your system.
* When refactoring is **not possible or desirable** due to access restrictions or risks.

---

### ✅ Real-world Analogy

A **power socket adapter** allows your laptop charger (US plug) to work with a European wall socket (EU plug). Instead of changing the charger or the socket, you use an adapter in between.

---

### ✅ C++ Example: Adapter Pattern

#### Scenario

You have a **legacy printer driver** that exposes a different method than your new system expects.

#### Old Interface (Legacy Code):

```cpp
class OldPrinter {
public:
    void printText(const std::string& text) {
        std::cout << "Printing from OldPrinter: " << text << "\n";
    }
};
```

#### New Expected Interface:

```cpp
class Printer {
public:
    virtual void print(const std::string& text) = 0;
    virtual ~Printer() {}
};
```

#### Adapter:

```cpp
class PrinterAdapter : public Printer {
private:
    OldPrinter* oldPrinter;

public:
    PrinterAdapter(OldPrinter* op) : oldPrinter(op) {}

    void print(const std::string& text) override {
        oldPrinter->printText(text);
    }
};
```

#### Usage:

```cpp
int main() {
    OldPrinter* legacy = new OldPrinter();
    Printer* printer = new PrinterAdapter(legacy);

    printer->print("Hello Adapter!");

    delete legacy;
    delete printer;

    return 0;
}
```

---

### ❌ Without Adapter (Anti-Pattern)

```cpp
int main() {
    OldPrinter* oldPrinter = new OldPrinter();
    oldPrinter->printText("Hello Adapter!");
    delete oldPrinter;
}
```

🔴 In this case:

* Your system cannot treat different types of printers polymorphically.
* You break abstraction and interface uniformity.
* You're tightly coupling your system to legacy implementations.

---

### 🚫 Disadvantages of Not Using Adapter

When you don’t use the Adapter pattern where needed:

1. **Tight Coupling**: You directly depend on incompatible interfaces.
2. **Code Duplication**: You might rewrite similar logic to work with each incompatible system.
3. **Poor Maintainability**: Changes in legacy or third-party code will ripple through your application.
4. **Broken Polymorphism**: Your code cannot treat different types via a common interface.

---
