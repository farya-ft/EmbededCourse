#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

using namespace std;
class Logger {
public:
    Logger(const string& filename);
    ~Logger();
    void log(const string& message);

private:
     ofstream logfile;
};

#endif // LOGGER_H
