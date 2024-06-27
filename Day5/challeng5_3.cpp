//Write exception handling for a scenario where a sensor fails to initialize.

#include <iostream>
#include <exception>
using namespace std;

// Custom exception class for sensor initialization failure
class SensorInitializationException : public std::exception      // The SensorInitializationException class inherits from std::exception and overrides the what() method to provide a custom error message.
{
public:
    const char *what() const noexcept override
    {
        return "Sensor initialization failed";
    }
};

// Sensor class simulating the sensor initialization
class Sensor
{
public:
    void initialize()
    {
        // Simulate a failure
        bool success = false;

        if (!success)
        {
            throw SensorInitializationException();
        }

        cout << "Sensor initialized successfully." << endl;
    }
};

int main()
{
    Sensor sensor;

    try
    {
        sensor.initialize();
    }
    catch (const SensorInitializationException &e)
    {
        cerr << "Error: " << e.what() << endl;
        // Handle the error, for example, retry initialization or terminate the program
    }

    return 0;
}
