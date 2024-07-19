#include <iostream>
#include "Logger.h"

using namespace std;

int main() {
    Logger logger("Log.txt");

    for (int i = 0; i <= 10; ++i) {
        logger.log("Count: " + to_string(i));
    }

    cout << "Counting completed and logged to Log.txt" << endl;

    return 0;
}



/*Detailed Breakdown of Loop Body
cpp
Copy code
logger.log("Count: " + std::to_string(i));


std::to_string(i):
This function converts the integer i to a std::string. For example, if i is 5, std::to_string(i) will produce the string "5".

String Concatenation:
"Count: " + std::to_string(i) concatenates the string "Count: " with the string representation of i. For example, when i is 5, this expression will produce the string "Count: 5".

logger.log:
This calls the log method of the Logger instance logger, passing the concatenated string as an argument.
The log method writes this string to the log file (Log.txt), followed by a newline.*/