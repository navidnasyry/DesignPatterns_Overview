#include<iostream>
#include <vector>

class Observer {
public:
    virtual void update(float temperature, float humidity) = 0;
    virtual ~Observer() = default;
};

class Subject {
public:
    virtual void registerObserver(Observer* o) = 0;
    virtual void removeObserver(Observer* o) = 0;
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};


class WeatherData : public Subject {
private:
    std::vector<Observer*> observers;
    float temperature;
    float humidity;

public:
    void registerObserver(Observer* o) override {
        observers.push_back(o);
    }

    void removeObserver(Observer* o) override {
        observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
    }

    void notifyObservers() override {
        for (Observer* o : observers) {
            o->update(temperature, humidity);
        }
    }

    void setMeasurements(float temp, float hum) {
        temperature = temp;
        humidity = hum;
        notifyObservers();
    }
};



class CurrentConditionsDisplay : public Observer {
public:
    void update(float temperature, float humidity) override {
        std::cout << "Current Conditions: " << temperature << "C, " << humidity << "% humidity\n";
    }
};

class StatisticsDisplay : public Observer {
public:
    void update(float temperature, float humidity) override {
        std::cout << "Stats Updated. Avg Temp: " << temperature << ", Humidity: " << humidity << "\n";
    }
};


int main() {
    WeatherData weatherStation;

    CurrentConditionsDisplay currentDisplay;
    StatisticsDisplay statsDisplay;

    weatherStation.registerObserver(&currentDisplay);
    weatherStation.registerObserver(&statsDisplay);

    weatherStation.setMeasurements(25.0f, 65.0f);
    weatherStation.setMeasurements(26.5f, 70.0f);

    return 0;
}
