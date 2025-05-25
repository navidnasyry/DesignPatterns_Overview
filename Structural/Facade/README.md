## 🎭 Facade Design Pattern

### 🧠 Purpose

The **Facade Pattern** provides a **unified, simplified interface** to a set of interfaces in a subsystem. It hides the complexity of underlying systems and makes them easier to use.

---

### 📝 When to Use the Facade Pattern

* When you want to **simplify access to a complex system**.
* When you're integrating a **subsystem** and want to provide a **clean interface**.
* To **decouple clients from implementation details** of a system.
* To **reduce dependencies** between clients and subsystems.

---

### ✅ Real-world Analogy

A **car dashboard** is a facade to a complex machine: starting the car, turning the wheel, pressing pedals — all simplified interfaces to a complicated engine and electrical system underneath.

---

## ✅ C++ Example: Facade Pattern

#### Scenario

Imagine you're writing a **Home Theater System**. Internally, it has subsystems like:

* `Amplifier`
* `DVD Player`
* `Projector`

You don’t want the user to control each subsystem separately — so you create a **Facade** to handle common operations like "watchMovie()" or "endMovie()".

---

### 🔧 Subsystems

```cpp
class Amplifier {
public:
    void on() { std::cout << "Amplifier on\n"; }
    void off() { std::cout << "Amplifier off\n"; }
};

class DVDPlayer {
public:
    void on() { std::cout << "DVD Player on\n"; }
    void play() { std::cout << "Playing DVD\n"; }
    void off() { std::cout << "DVD Player off\n"; }
};

class Projector {
public:
    void on() { std::cout << "Projector on\n"; }
    void off() { std::cout << "Projector off\n"; }
};
```

---

### 🎬 Facade

```cpp
class HomeTheaterFacade {
private:
    Amplifier* amp;
    DVDPlayer* dvd;
    Projector* projector;

public:
    HomeTheaterFacade(Amplifier* a, DVDPlayer* d, Projector* p)
        : amp(a), dvd(d), projector(p) {}

    void watchMovie() {
        std::cout << "Get ready to watch a movie...\n";
        amp->on();
        projector->on();
        dvd->on();
        dvd->play();
    }

    void endMovie() {
        std::cout << "Shutting down the movie theater...\n";
        dvd->off();
        projector->off();
        amp->off();
    }
};
```

---

### ✅ Usage

```cpp
int main() {
    Amplifier amp;
    DVDPlayer dvd;
    Projector projector;

    HomeTheaterFacade homeTheater(&amp, &dvd, &projector);
    homeTheater.watchMovie();
    homeTheater.endMovie();

    return 0;
}
```

---

## ❌ Without Facade

```cpp
int main() {
    Amplifier amp;
    DVDPlayer dvd;
    Projector projector;

    amp.on();
    projector.on();
    dvd.on();
    dvd.play();

    dvd.off();
    projector.off();
    amp.off();

    return 0;
}
```

🔴 Problem: Too much responsibility on the client.

* Complex subsystem logic exposed.
* Duplicated control logic across clients.
* Poor readability and maintainability.

---

### 🚫 Disadvantages of Not Using Facade

1. **High Coupling**: Clients must know and manage all subsystem classes.
2. **Duplicated Code**: Multiple parts of the code might repeat startup/shutdown logic.
3. **Hard to Change**: Changes in subsystem behavior require updating all clients.
4. **Reduced Clarity**: Client logic becomes cluttered with low-level operations.


---

## 🔍 What's the Problem?

The **Facade Pattern**, while helpful in simplifying complex subsystems, can **violate the Dependency Inversion Principle (DIP)** — the **"D"** in **SOLID**:

> **DIP**: High-level modules should not depend on low-level modules. Both should depend on abstractions.

In a basic Facade implementation like this:

```cpp
class HomeTheaterFacade {
    Amplifier* amp;
    DVDPlayer* dvd;
    Projector* projector;

    // ...
};
```

The **Facade (a high-level class)** is **directly dependent on concrete classes** like `Amplifier`, `DVDPlayer`, and `Projector`.

* 🛑 This creates **tight coupling**.
* 🛑 Makes **unit testing harder**.
* 🛑 Reduces **flexibility** — changing implementation of subsystems requires changes in the Facade.

---

## ✅ How to Fix It — Use Interfaces or Abstract Base Classes

Instead of depending on concrete implementations, **depend on abstractions**.

---

### ✅ Step 1: Define Abstract Interfaces

```cpp
class IAmplifier {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual ~IAmplifier() = default;
};

class IDVDPlayer {
public:
    virtual void on() = 0;
    virtual void play() = 0;
    virtual void off() = 0;
    virtual ~IDVDPlayer() = default;
};

class IProjector {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual ~IProjector() = default;
};
```

---

### ✅ Step 2: Implement Concrete Classes

```cpp
class Amplifier : public IAmplifier {
public:
    void on() override { std::cout << "Amplifier on\n"; }
    void off() override { std::cout << "Amplifier off\n"; }
};

class DVDPlayer : public IDVDPlayer {
public:
    void on() override { std::cout << "DVD Player on\n"; }
    void play() override { std::cout << "Playing DVD\n"; }
    void off() override { std::cout << "DVD Player off\n"; }
};

class Projector : public IProjector {
public:
    void on() override { std::cout << "Projector on\n"; }
    void off() override { std::cout << "Projector off\n"; }
};
```

---

### ✅ Step 3: Refactor Facade to Use Interfaces

```cpp
class HomeTheaterFacade {
private:
    IAmplifier* amp;
    IDVDPlayer* dvd;
    IProjector* projector;

public:
    HomeTheaterFacade(IAmplifier* a, IDVDPlayer* d, IProjector* p)
        : amp(a), dvd(d), projector(p) {}

    void watchMovie() {
        std::cout << "Starting movie...\n";
        amp->on();
        projector->on();
        dvd->on();
        dvd->play();
    }

    void endMovie() {
        std::cout << "Ending movie...\n";
        dvd->off();
        projector->off();
        amp->off();
    }
};
```

---

## ✅ Benefits of This Approach

| Before (Violation)                 | After (Following DIP)               |
| ---------------------------------- | ----------------------------------- |
| Facade depends on concrete classes | Facade depends on abstractions      |
| Tight coupling                     | Loose coupling                      |
| Hard to mock/test                  | Easy to mock/test                   |
| Rigid to change                    | Open to extension, closed to change |

---

## ✨ Summary

To make **Facade Pattern** respect **DIP**:

* Use **interfaces or abstract base classes** for subsystems.
* Inject dependencies into the Facade via constructors or dependency injection containers.
* This makes the system more **flexible, testable, and maintainable**.

