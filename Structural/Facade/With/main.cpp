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


class HomeTheaterFacade {
private:
    Amplifier* amp;
    DVDPlayer* dvd;
    Projector* projector;

public:
    HomeTheaterFacade(Amplifier* a, DVDPlayer* d, Projector* p)
        : amp(a), dvd(d), projector(p) {}

    void watchMovie() {
        std::cout << "Get ready to watch a movie...\n";
        amp->on();
        projector->on();
        dvd->on();
        dvd->play();
    }

    void endMovie() {
        std::cout << "Shutting down the movie theater...\n";
        dvd->off();
        projector->off();
        amp->off();
    }
};


int main() {
    Amplifier amp;
    DVDPlayer dvd;
    Projector projector;

    HomeTheaterFacade homeTheater(&amp, &dvd, &projector);
    homeTheater.watchMovie();
    homeTheater.endMovie();

    return 0;
}
