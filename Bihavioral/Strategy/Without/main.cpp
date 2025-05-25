#include<iostream>

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
