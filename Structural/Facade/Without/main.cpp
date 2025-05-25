#include<iostream>


class Amplifier {
public:
    void on() { std::cout << "Amplifier on\n"; }
    void off() { std::cout << "Amplifier off\n"; }
};

class DVDPlayer {
public:
    void on() { std::cout << "DVD Player on\n"; }
    void play() { std::cout << "Playing DVD\n"; }
    void off() { std::cout << "DVD Player off\n"; }
};

class Projector {
public:
    void on() { std::cout << "Projector on\n"; }
    void off() { std::cout << "Projector off\n"; }
};

int main() {
    Amplifier amp;
    DVDPlayer dvd;
    Projector projector;

    amp.on();
    projector.on();
    dvd.on();
    dvd.play();

    dvd.off();
    projector.off();
    amp.off();

    return 0;
}
