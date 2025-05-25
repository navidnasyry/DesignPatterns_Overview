#include<iostream>


class OldPrinter {
public:
    void printText(const std::string& text) {
        std::cout << "Printing from OldPrinter: " << text << "\n";
    }
};


int main() {
    OldPrinter* oldPrinter = new OldPrinter();
    oldPrinter->printText("Hello Adapter!");
    delete oldPrinter;
}
