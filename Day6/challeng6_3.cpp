// Implement error handling in the Logger class to handle file I/O errors.

#include <iostream>
#include <fstream>
#include <string>
 
 using namespace std;

class Logger {
public:
    Logger(const string& filename) : logFile_(filename, ios::app) {
        if (!logFile_) {
            cerr << "Failed to open log file: " << filename << endl;
        }
    }

    void log(const string& message) {
        if (!logFile_) {
            cerr << "Log file is not open." << endl;
            return;
        }

        logFile_ << message << endl;
        if (!logFile_) {
             cerr << "Failed to write to log file." << endl;  /* If the write operation failed
                                                               (for example, due to a full disk or a hardware error), 
                                                               an error message is printed.*/
        }
    }

private:
    ofstream logFile_;
};

int main() {
    Logger logger("log.txt");
    logger.log("This is a log message.");
    return 0;
}


/*
1. The Logger constructor attempts to open the log file in append mode and checks if the file was successfully opened. If not, 
   it prints an error message to std::cerr.
2.The log method checks if the file is open before attempting to write to it. If the file is not open, it prints an error message.
3.After writing to the file, the log method checks if the write operation was successful. If not, it prints an error message.

This approach avoids using exceptions and simplifies error handling by directly checking the stream's state and using std::cerr to report errors.*/


/*The use of an underscore (_) at the end of a variable name, like logFile_,
 is a common naming convention in C++ and other languages. 
 It is used to distinguish member variables from other variables, such as function parameters and local variables.
  Here are some reasons and benefits for using this naming convention:

1.Clarity and Readability: It makes it clear which variables are members of a class, improving the readability of the code.

2.Avoiding Name Collisions: It helps avoid name collisions between member variables and other variables, 
   such as parameters or local variables within member functions.

3.Consistency: Following a consistent naming convention helps maintain a uniform code style across a project, 
   making it easier for developers to understand and collaborate on the code.*/