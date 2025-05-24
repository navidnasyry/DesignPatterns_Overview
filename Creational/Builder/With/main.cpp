#include<iostream>

using namespace std;

class Computer {
    public:
        std::string CPU, GPU, RAM, Storage;
    
        void show() {
            std::cout << "Computer Configuration:\n"
                      << "CPU: " << CPU << "\n"
                      << "GPU: " << GPU << "\n"
                      << "RAM: " << RAM << "\n"
                      << "Storage: " << Storage << "\n";
        }
    };
    
    // Builder
    class ComputerBuilder {
    private:
        Computer comp;
    public:
        ComputerBuilder& setCPU(std::string cpu) { comp.CPU = cpu; return *this; }
        ComputerBuilder& setGPU(std::string gpu) { comp.GPU = gpu; return *this; }
        ComputerBuilder& setRAM(std::string ram) { comp.RAM = ram; return *this; }
        ComputerBuilder& setStorage(std::string storage) { comp.Storage = storage; return *this; }
        Computer build() { return comp; }
    };
    
    // Usage
    int main() {
        ComputerBuilder builder;
        Computer gamingPC = builder.setCPU("Intel i9")
                                    .setGPU("RTX 4080")
                                    .setRAM("32GB")
                                    .setStorage("2TB SSD")
                                    .build();
    
        gamingPC.show();
        return 0;
    }
    