
    #include <iostream>
    #include <thread>
    #include <chrono>

    // Pseudo-code for an embedded environment
    class Sensor {
    public:
        void readSensorData() {
            while (true) {
                // Simulate reading sensor data
                std::cout << "Reading sensor data" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    };

    class Display {
    public:
        void updateDisplay() {
            while (true) {
                // Simulate updating the display
                std::cout << "Updating display" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
    };

    int main() {
        Sensor sensor;
        Display display;

        std::thread sensorThread(&Sensor::readSensorData, &sensor);
        std::thread displayThread(&Display::updateDisplay, &display);

        sensorThread.join();
        displayThread.join();

        return 0;
    }