
//Combining multi-threading with STL containers and file I/O can help manage concurrent data processing and logging.

#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <mutex>
#include <chrono>

using namespace std;
mutex logMutex;

class DataLogger {
public:
    DataLogger(const string &filename) : filename(filename) {}

    void logData(const vector<int> &data) {
        std::lock_guard<mutex> guard(logMutex);
        std::ofstream outFile(filename, ios::app); // Open file in append mode
        if (outFile.is_open()) {
            for (int value : data) {
                outFile << value << endl; // Write data to the file
            }
            outFile.close();
        }
    }

    void readData() {
        lock_guard<mutex> guard(logMutex);
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {  // Read data line by line
                cout << line << endl; // Print each line to the console
            }
            inFile.close();  // Close the file
        }
    }

private:
    string filename;  // Member variable to store the filename
};

void generateData(DataLogger &logger, int start) {
    for (int i = 0; i < 5; ++i) {
        vector<int> data = {start + i, start + i + 1, start + i + 2}; // Generate data
        logger.logData(data);
        this_thread::sleep_for(chrono::milliseconds(500));// Sleep for 500 milliseconds
    }
}

int main() {
    DataLogger logger("data_log.txt");  // Create a DataLogger object with the filename

    thread t1(generateData, ref(logger), 100);  // Start first thread to generate data
    thread t2(generateData, ref(logger), 200);

    t1.join(); // Wait for the first thread to finish
    t2.join();

    logger.readData();  // Read and print the logged data

    return 0;
}
