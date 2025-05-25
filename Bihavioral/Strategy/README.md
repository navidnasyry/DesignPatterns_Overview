## 🧠 Strategy Design Pattern

### 📌 Purpose

The **Strategy Pattern** enables selecting an algorithm’s behavior at runtime. It **defines a family of algorithms**, encapsulates each one, and makes them interchangeable without changing the context (client) code.

This is particularly useful when you need to switch between multiple behaviors or algorithms dynamically.

---

## 📅 When to Use Strategy

* When you need to use different **variants of an algorithm** (e.g. sorting, filtering, validation).
* When you want to **remove conditional logic** or `switch`/`if-else` statements.
* When you want to **isolate algorithm logic** from the main business logic.
* When your behavior can change **dynamically at runtime**.

---

## 🔌 Real-world Analogy

Imagine a **navigation app** (like Google Maps) — you can switch between different strategies to get to your destination:

* Fastest route
* Shortest distance
* Avoid tolls

Each of these is a strategy for the same goal.

---

## ✅ C++ Implementation

### 🚗 Scenario: Payment processing

A store supports multiple payment methods: Credit Card and PayPal. The payment processing logic should be swappable without altering the checkout code.

---

### 1. Strategy Interface

```cpp
class PaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~PaymentStrategy() = default;
};
```

---

### 2. Concrete Strategies

```cpp
class CreditCardPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Credit Card.\n";
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using PayPal.\n";
    }
};
```

---

### 3. Context Class

```cpp
class Checkout {
private:
    PaymentStrategy* strategy;

public:
    void setPaymentStrategy(PaymentStrategy* ps) {
        strategy = ps;
    }

    void processPayment(int amount) {
        if (strategy) {
            strategy->pay(amount);
        } else {
            std::cout << "No payment strategy selected.\n";
        }
    }
};
```

---

### 4. Usage

```cpp
int main() {
    Checkout checkout;

    CreditCardPayment credit;
    PayPalPayment paypal;

    checkout.setPaymentStrategy(&credit);
    checkout.processPayment(100);

    checkout.setPaymentStrategy(&paypal);
    checkout.processPayment(250);

    return 0;
}
```

---

## ❌ Without Strategy Pattern (Anti-Pattern)

```cpp
class Checkout {
public:
    void processPayment(const std::string& method, int amount) {
        if (method == "credit") {
            std::cout << "Paid " << amount << " using Credit Card.\n";
        } else if (method == "paypal") {
            std::cout << "Paid " << amount << " using PayPal.\n";
        } else {
            std::cout << "Invalid payment method.\n";
        }
    }
};
```

🔴 Problems:

* Conditional logic grows as you add more payment methods.
* Violates **Open/Closed Principle** (you must modify `Checkout` to add new strategies).
* Not scalable or testable — no separation of concerns.

---

## 🚫 Disadvantages of Not Using Strategy

| Without Strategy                     | With Strategy                        |
| ------------------------------------ | ------------------------------------ |
| Rigid, unscalable code               | Easily extendable with new behaviors |
| Business logic mixed with algorithms | Clear separation of concerns         |
| Hard to test or replace behaviors    | Interchangeable strategy objects     |
| Violates Open/Closed Principle       | Follows OCP and DIP                  |

---