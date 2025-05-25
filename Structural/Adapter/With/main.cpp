#include<iostream>


class OldPrinter {
public:
    void printText(const std::string& text) {
        std::cout << "Printing from OldPrinter: " << text << "\n";
    }
};

class IPrinter {
public:
    virtual void print(const std::string& text) = 0;
    virtual ~IPrinter() {}
};


class PrinterAdapter : public IPrinter {
private:
    OldPrinter* oldPrinter;

public:
    PrinterAdapter(OldPrinter* op) : oldPrinter(op) {}

    void print(const std::string& text) override {
        oldPrinter->printText(text);
    }
};


int main() {
    OldPrinter* legacy = new OldPrinter();
    IPrinter* printer = new PrinterAdapter(legacy);

    printer->print("Hello Adapter!");

    delete legacy;
    delete printer;

    return 0;
}
