#include<iostream>

using namespace std;

class Logger {
public:
    void log(const std::string& message) {
        std::cout << "[Log]: " << message << std::endl;
    }
};

int main() {
    Logger logger1;
    Logger logger2;

    logger1.log("Start application.");
    logger2.log("This is a separate logger instance.");

    return 0;
}
