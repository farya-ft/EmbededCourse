#include "Logger.h"
#include <iostream>
using namespace std;

Logger::Logger(const string& filename) : logfile(filename, ios::out | ios::app) {
    if (!logfile.is_open()) {
        cerr << "Failed to open log file!" << std::endl;
        exit(EXIT_FAILURE);
    }
}

Logger::~Logger() {
    if (logfile.is_open()) {
        logfile.close();
    }
}

void Logger::log(const string& message) {
    logfile << message << endl;
}


/*std::ios::out
Purpose: This flag is used to open the file for output operations.
Behavior: When you specify std::ios::out, it means that the file will be opened for writing. If the file already exists, the content might be truncated (i.e., cleared) unless combined with other flags that alter this behavior.
Usage: It is used when you need to write data to a file.

std::ios::app
Purpose: This flag stands for "append".
Behavior: When you specify std::ios::app, it means that all output operations will be performed at the end of the file. The file pointer is moved to the end of the file before any write operation, preserving existing content and appending new data.
Usage: It is used when you need to add new data to the end of an existing file without erasing its current contents.

Combined Usage: std::ios::out | std::ios::app
Purpose: Combining these flags ensures that the file is opened for writing and that new data is appended to the end of the file.
Behavior: The file is opened for output (std::ios::out), and any new data written to the file is appended to the existing content (std::ios::app).
Usage: This combination is ideal for logging purposes, where you typically want to add new log entries to the end of the log file without losing previous entries.*/