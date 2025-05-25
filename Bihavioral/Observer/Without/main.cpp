#include <iostream>
using namespace std;

// Directly referenced display classes
class CurrentConditionsDisplay {
public:
    void update(float temperature, float humidity) {
        cout << "Current Conditions: " << temperature << "C, " << humidity << "% humidity\n";
    }
};

class StatisticsDisplay {
public:
    void update(float temperature, float humidity) {
        cout << "Statistics Updated. Avg Temp: " << temperature << ", Humidity: " << humidity << "\n";
    }
};

// Subject class with hard-coded dependencies
class WeatherData {
private:
    float temperature;
    float humidity;

    // Direct references to display classes — tight coupling
    CurrentConditionsDisplay currentDisplay;
    StatisticsDisplay statsDisplay;

public:
    void setMeasurements(float temp, float hum) {
        temperature = temp;
        humidity = hum;
        notifyDisplays(); // Must call displays manually
    }

    void notifyDisplays() {
        // Each display must be known and manually updated
        currentDisplay.update(temperature, humidity);
        statsDisplay.update(temperature, humidity);
    }
};

// Client code
int main() {
    WeatherData weatherStation;

    weatherStation.setMeasurements(24.0f, 60.0f);
    weatherStation.setMeasurements(27.5f, 70.0f);

    return 0;
}
