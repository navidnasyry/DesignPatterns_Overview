## 👁️‍🗨️ Observer Design Pattern

### 📌 Purpose

The **Observer Pattern** defines a **one-to-many dependency** between objects so that when one object (the *Subject*) changes state, all its dependents (the *Observers*) are notified and updated **automatically**.

It’s especially useful in **event-driven systems** and **publish/subscribe models**.

---

## 🧭 When to Use Observer

* When multiple objects need to be notified of a change in another object **without tight coupling**.
* In **GUI toolkits**, **notification systems**, or **real-time data feeds**.
* When the subject should not know about concrete observers.

---

## ❌ When Not to Use Observer

* When the number of observers is small and fixed — tight coupling may be simpler.
* In performance-critical sections (observers can introduce latency).
* When deterministic update order is important (observers notify in arbitrary order).

---

## 🔌 Real-world Analogy

A **newsletter subscription** is a classic example:

* The publisher (subject) notifies all subscribers (observers) when a new article is posted.

---

## ✅ C++ Implementation

### Scenario: A weather station that notifies multiple displays of weather changes.

---

### 1. Interfaces

```cpp
class Observer {
public:
    virtual void update(float temperature, float humidity) = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    virtual void registerObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};
```

---

### 2. Concrete Subject

```cpp
#include <vector>

class WeatherData : public Subject {
private:
    std::vector<Observer*> observers;
    float temperature;
    float humidity;

public:
    void registerObserver(Observer* o) override {
        observers.push_back(o);
    }

    void removeObserver(Observer* o) override {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

    void notifyObservers() override {
        for (Observer* o : observers) {
            o->update(temperature, humidity);
        }
    }

    void setMeasurements(float temp, float hum) {
        temperature = temp;
        humidity = hum;
        notifyObservers();
    }
};
```

---

### 3. Concrete Observers

```cpp
class CurrentConditionsDisplay : public Observer {
public:
    void update(float temperature, float humidity) override {
        std::cout << "Current Conditions: " << temperature << "C, " << humidity << "% humidity\n";
    }
};

class StatisticsDisplay : public Observer {
public:
    void update(float temperature, float humidity) override {
        std::cout << "Stats Updated. Avg Temp: " << temperature << ", Humidity: " << humidity << "\n";
    }
};
```

---

### 4. Usage

```cpp
int main() {
    WeatherData weatherStation;

    CurrentConditionsDisplay currentDisplay;
    StatisticsDisplay statsDisplay;

    weatherStation.registerObserver(&currentDisplay);
    weatherStation.registerObserver(&statsDisplay);

    weatherStation.setMeasurements(25.0f, 65.0f);
    weatherStation.setMeasurements(26.5f, 70.0f);

    return 0;
}
```

---

## ❌ Without Observer Pattern

You'd have hard-coded updates like this:

```cpp
class WeatherData {
    CurrentConditionsDisplay display;
    void setMeasurements(float temp, float humidity) {
        display.update(temp, humidity); // Tight coupling
    }
};
```

🔴 **Problems**:

* Can’t dynamically add/remove observers.
* Tight coupling between `WeatherData` and `CurrentConditionsDisplay`.
* Violates Open/Closed Principle — adding another display requires modifying `WeatherData`.

---

## ✅ Summary

| Feature      | Observer Pattern                             |
| ------------ | -------------------------------------------- |
| What it does | Enables one-to-many automatic notifications  |
| Benefits     | Loose coupling, extensibility, flexibility   |
| Best use     | UI updates, subscriptions, event systems     |
| Without it   | Tight coupling, manual updates, brittle code |


