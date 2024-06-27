
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
        std::ofstream outFile(filename, ios::app); // Append mode
        if (outFile.is_open()) {
            for (int value : data) {
                outFile << value << endl;
            }
            outFile.close();
        }
    }

    void readData() {
        lock_guard<mutex> guard(logMutex);
        ifstream inFile(filename);
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        }
    }

private:
    string filename;
};

void generateData(DataLogger &logger, int start) {
    for (int i = 0; i < 5; ++i) {
        vector<int> data = {start + i, start + i + 1, start + i + 2};
        logger.logData(data);
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    DataLogger logger("data_log.txt");

    thread t1(generateData, ref(logger), 100);
    thread t2(generateData, ref(logger), 200);

    t1.join();
    t2.join();

    logger.readData();

    return 0;
}
