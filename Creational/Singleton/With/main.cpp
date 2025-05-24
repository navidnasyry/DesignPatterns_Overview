#include<iostream>

using namespace std;

class Logger {
private:
    Logger() {}  // Private constructor
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& getInstance() {
        static Logger instance; // Guaranteed to be destroyed, instantiated on first use
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "[Log]: " << message << std::endl;
    }
};

int main() {
    Logger::getInstance().log("System initialized.");
    Logger::getInstance().log("User login successful.");
    return 0;
}
