class Computer {
public:
    std::string CPU, GPU, RAM, Storage;

    Computer(std::string cpu, std::string gpu, std::string ram, std::string storage)
        : CPU(cpu), GPU(gpu), RAM(ram), Storage(storage) {}

    void show() {
        std::cout << "Computer Configuration:\n"
                  << "CPU: " << CPU << "\n"
                  << "GPU: " << GPU << "\n"
                  << "RAM: " << RAM << "\n"
                  << "Storage: " << Storage << "\n";
    }
};

int main() {
    Computer gamingPC("Intel i9", "RTX 4080", "32GB", "2TB SSD");
    gamingPC.show();
    return 0;
}
