#include<iostream>


class IPaymentStrategy {
public:
    virtual void pay(int amount) = 0;
    virtual ~IPaymentStrategy() = default;
};

class CreditCardPayment : public IPaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using Credit Card.\n";
    }
};

class PayPalPayment : public IPaymentStrategy {
public:
    void pay(int amount) override {
        std::cout << "Paid " << amount << " using PayPal.\n";
    }
};

class Checkout {
private:
    IPaymentStrategy* strategy;

public:
    void setPaymentStrategy(IPaymentStrategy* ps) {
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

