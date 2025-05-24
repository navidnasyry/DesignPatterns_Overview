#include <iostream>
#include <string>

class Logger {
private:
    // Inline static member initialization (C++17+)
    inline static Logger* instance = nullptr;

    // Private constructor to prevent external instantiation
    Logger() {
        std::cout << "Logger initialized.\n";
    }

public:
    // Deleted copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Static accessor
    static Logger* getInstance() {
        if (instance == nullptr) {
            instance = new Logger();
        }
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "[Log]: " << message << std::endl;
    }
};

int main() {
    Logger* logger1 = Logger::getInstance();
    Logger* logger2 = Logger::getInstance();

    logger1->log("First message");
    logger2->log("Second message");

    if (logger1 == logger2) {
        std::cout << "Singleton verified: Same instance used.\n";
    }

    return 0;
}
