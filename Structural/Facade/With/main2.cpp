#include<iostream>


class IAmplifier {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual ~IAmplifier() = default;
};

class IDVDPlayer {
public:
    virtual void on() = 0;
    virtual void play() = 0;
    virtual void off() = 0;
    virtual ~IDVDPlayer() = default;
};

class IProjector {
public:
    virtual void on() = 0;
    virtual void off() = 0;
    virtual ~IProjector() = default;
};

class Amplifier : public IAmplifier {
public:
    void on() override { std::cout << "Amplifier on\n"; }
    void off() override { std::cout << "Amplifier off\n"; }
};

class DVDPlayer : public IDVDPlayer {
public:
    void on() override { std::cout << "DVD Player on\n"; }
    void play() override { std::cout << "Playing DVD\n"; }
    void off() override { std::cout << "DVD Player off\n"; }
};

class Projector : public IProjector {
public:
    void on() override { std::cout << "Projector on\n"; }
    void off() override { std::cout << "Projector off\n"; }
};


class HomeTheaterFacade {
private:
    IAmplifier* amp;
    IDVDPlayer* dvd;
    IProjector* projector;

public:
    HomeTheaterFacade(IAmplifier* a, IDVDPlayer* d, IProjector* p)
        : amp(a), dvd(d), projector(p) {}

    void watchMovie() {
        std::cout << "Starting movie...\n";
        amp->on();
        projector->on();
        dvd->on();
        dvd->play();
    }

    void endMovie() {
        std::cout << "Ending movie...\n";
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
