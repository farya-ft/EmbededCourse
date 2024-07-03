## Day 6: STL Containers and File I/O
!!! 1. STL Containers
The STL provides various containers like vector, list, map, and set to manage collections of data. Let's explore some of these.

##### 1.Vector

A vector is a dynamic array that can change size.

Code: Vector Example

  
```cpp
    #include <iostream>
    #include <vector>

    int main() {
        std::vector<int> numbers = {1, 2, 3, 4, 5};

        // Adding elements
        numbers.push_back(6);
        numbers.push_back(7);

        // Accessing elements
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        // Removing elements
        numbers.pop_back(); // Removes last element

        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        return 0;
    }

```
##### Explanation:

std::vector<int> numbers = {1, 2, 3, 4, 5};: Initializes a vector with values.
numbers.push_back(6);: Adds an element to the end.
numbers.pop_back();: Removes the last element.
Iterates through the vector to print elements.
***

##### 2.Map

A map is a collection of key-value pairs.

Code: Map Example

 ```cpp

    #include <iostream>
    #include <map>
    #include <string>

    int main() {
        std::map<std::string, int> ageMap;

        // Adding elements
        ageMap["Alice"] = 30;
        ageMap["Bob"] = 25;

        // Accessing elements
        std::cout << "Alice's age: " << ageMap["Alice"] << std::endl;

        // Iterating over the map
        for (const auto &pair : ageMap) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }

        return 0;
    }
```
##### Explanation:

std::map<std::string, int> ageMap;: Initializes a map.
ageMap["Alice"] = 30;: Adds a key-value pair.
Iterates through the map to print elements.
###### Let's break down the iteration part of the code:

###### 1.Range-Based For Loop:

* The loop uses the range-based for syntax, which is a feature introduced in C++11. This allows you to iterate over all elements in a container (like a map, vector, or array) without needing to use iterators or indices explicitly.
###### 2.Const Reference to Pair:

* const auto &pair means that for each element in ageMap, a constant reference to the element (which is a pair) is created.
* auto is a placeholder that lets the compiler deduce the type of pair from the type of the elements in the container ageMap. In this case, each element in ageMap is a std::pair<const std::string, int>.
###### 3.Accessing Key-Value Pair:

* pair.first accesses the key of the current pair (which is a std::string in this map).
* pair.second accesses the value of the current pair (which is an int in this map).

###### 4.Printing the Key-Value Pair:

* std::cout << pair.first << ": " << pair.second << std::endl; prints the key and value of the current pair in the format "key: value".
###### What Happens During Iteration
The loop iterates over each key-value pair in the map ageMap.
For each iteration:
It binds the current key-value pair to pair.
It prints the key and the value of the current pair.

!!! 2. File I/O

File I/O allows you to read from and write to files.

Code: File I/O Example

 ```cpp
    #include <iostream>
    #include <fstream>
    #include <string>

    int main() {
        std::string filename = "example.txt";

        // Writing to a file
        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "Hello, World!" << std::endl;
            outFile << "C++ File I/O" << std::endl;
            outFile.close();
        }

        // Reading from a file
        std::ifstream inFile(filename);
        if (inFile.is_open()) {
            std::string line;
            while (getline(inFile, line)) {
                std::cout << line << std::endl;
            }
            inFile.close();
        }

        return 0;
    }
```    
##### Explanation:

std::ofstream outFile(filename);: Opens a file for writing.
outFile << "Hello, World!" << std::endl;: Writes to the file.
std::ifstream inFile(filename);: Opens a file for reading.
getline(inFile, line): Reads lines from the file.
3. Embedded Systems Insight
In embedded systems, file I/O might involve reading from or writing to SD cards or flash memory, and STL containers can be used to manage data efficiently.

#### Embedded Example: Data Logging (Pseudo-code)

 ```cpp
    #include <iostream>
    #include <vector>
    #include <fstream>

    // Pseudo-code for an embedded environment
    class DataLogger {
    public:
        DataLogger(const std::string &filename) : filename(filename) {}

        void logData(const std::vector<int> &data) {
            std::ofstream outFile(filename, std::ios::app); // Append mode
            if (outFile.is_open()) {
                for (int value : data) {
                    outFile << value << std::endl;
                }
                outFile.close();
            }
        }

        void readData() {
            std::ifstream inFile(filename);
            if (inFile.is_open()) {
                std::string line;
                while (getline(inFile, line)) {
                    std::cout << line << std::endl;
                }
                inFile.close();
            }
        }

    private:
        std::string filename;
    };

    int main() {
        DataLogger logger("data_log.txt");

        std::vector<int> data = {100, 200, 300};
        logger.logData(data);

        logger.readData();

        return 0;
    }
```

##### Explanation:

DataLogger: Class to handle logging data to a file.
logData: Method to log data.
readData: Method to read logged data.
4. Combining with Multi-threading
Combining multi-threading with STL containers and file I/O can help manage concurrent data processing and logging.

#### Example: Multi-threaded Data Logging (Pseudo-code)

  ```cpp
    #include <iostream>
    #include <vector>
    #include <thread>
    #include <fstream>
    #include <mutex>
    #include <chrono>

    std::mutex logMutex;

    class DataLogger {
    public:
        DataLogger(const std::string &filename) : filename(filename) {}

        void logData(const std::vector<int> &data) {
            std::lock_guard<std::mutex> guard(logMutex);
            std::ofstream outFile(filename, std::ios::app); // Append mode
            if (outFile.is_open()) {
                for (int value : data) {
                    outFile << value << std::endl;
                     /* << is the stream insertion operator, which is used to write data to streams.
                      In this case, it writes the integer value to the file.*/
                }
                outFile.close();
            }
        }

        void readData() {
            std::lock_guard<std::mutex> guard(logMutex);
            std::ifstream inFile(filename);
            if (inFile.is_open()) {
                std::string line;
                while (getline(inFile, line)) {
                    std::cout << line << std::endl;
                }
                inFile.close();
            }
        }

    private:
        std::string filename;
    };

    void generateData(DataLogger &logger, int start) {
        for (int i = 0; i < 5; ++i) {
            std::vector<int> data = {start + i, start + i + 1, start + i + 2};
            logger.logData(data);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    int main() {
        DataLogger logger("data_log.txt");

        std::thread t1(generateData, std::ref(logger), 100);
        std::thread t2(generateData, std::ref(logger), 200);

        t1.join();
        t2.join();

        logger.readData();

        return 0;
    }
 ```

##### Explanation:

std::mutex logMutex: Mutex to protect file access.
std::lock_guard<std::mutex> guard(logMutex): Locks the mutex in a scoped manner.
generateData: Function to generate and log data in a separate thread.
Two threads t1 and t2 generate and log data concurrently.



* In this project, the `std::mutex` is used to ensure thread safety when accessing and modifying shared resources, specifically the log file. 

### Purpose of std::ofstream
```

1.File Handling: std::ofstream is specifically designed for file output operations.
 It provides functionalities to open, write to, and close files, which are essential for logging purposes.
2.Stream Operations: std::ofstream inherits from std::ostream,
 allowing it to be used with the stream insertion operator (<<) to write formatted output to files.
 _Why Not std::string?
If logFile_ were defined as a std::string, it would only hold the filename, 
not handle the actual file operations. To perform file operations,
 you would still need an std::ofstream object.
```

### Context
The project involves logging data to a file and reading from the file using multiple threads. The threads concurrently write data to the same file, which can lead to data corruption or other synchronization issues if not handled properly.

### Role of `std::mutex`

1. **Ensuring Exclusive Access:**
   The mutex (`logMutex`) is used to ensure that only one thread at a time can access and modify the log file. This is crucial when multiple threads might attempt to write to or read from the file simultaneously.

2. **Avoiding Race Conditions:**
   A race condition occurs when two or more threads access shared data concurrently, and the outcome of the operations depends on the timing of the threads' execution. By locking the mutex before accessing the file and unlocking it afterward, the code ensures that the file operations are atomic and race conditions are avoided.

### Specific Usage

1. **Logging Data (`logData` Method):**

  ```cpp 
   void logData(const std::vector<int> &data) {
       std::lock_guard<std::mutex> guard(logMutex);  // Locks the mutex
       std::ofstream outFile(filename, std::ios::app); // Append mode
       if (outFile.is_open()) {
           for (int value : data) {
               outFile << value << std::endl;
           }
           outFile.close();
       }
   }
   
```
   In the `logData` method, `std::lock_guard<std::mutex>` is used to lock the mutex (`logMutex`) when the method is called. This ensures that while one thread is writing data to the file, no other thread can access the file until the first thread releases the lock (when the `guard` goes out of scope).

2. **Reading Data (`readData` Method):**
 
 ```cpp

   void readData() {
       std::lock_guard<std::mutex> guard(logMutex);  // Locks the mutex
       std::ifstream inFile(filename);
       if (inFile.is_open()) {
           std::string line;
           while (getline(inFile, line)) {
               std::cout << line << std::endl;
           }
           inFile.close();
       }
   }
```   
   Similarly, in the `readData` method, the mutex is locked using `std::lock_guard<std::mutex>`. This prevents any thread from writing to the file while another thread is reading from it, ensuring that the reading operation is not interrupted and that the data read is consistent.

### Summary

The use of `std::mutex` in this project ensures that:

- Only one thread can write to or read from the log file at any given time.
- The file operations are atomic, preventing data corruption and ensuring data consistency.
- The race conditions are avoided, which makes the program behave predictably regardless of the thread execution order.

By using `std::lock_guard<std::mutex>`, the mutex is automatically locked when the guard is created and unlocked when the guard goes out of scope, providing a convenient and exception-safe way to manage the mutex.

!!! The code snippet:

```cpp
while (getline(inFile, line)) {
    std::cout << line << std::endl;
}
```

is part of the `readData` method in the `DataLogger` class. This loop reads each line from an input file and prints it to the standard output (usually the console). Let's break down the functionality step by step:

### Detailed Explanation

1. **`while` Loop**:
   ```cpp
   while (getline(inFile, line))
   ```
   - This is a `while` loop that continues to execute as long as the condition `getline(inFile, line)` is true.
   - `getline(inFile, line)` is a standard library function that reads a line of text from the input stream `inFile` and stores it in the string `line`.

2. **`getline` Function**:
   - The `getline` function reads characters from the input stream `inFile` until it encounters a newline character (`'\n'`) or the end of the file (EOF).
   - Each line read is stored in the variable `line`.
   - `getline` returns a reference to the input stream `inFile`. In the context of a `while` loop, it evaluates to `true` if a line was successfully read and `false` if the end of the file is reached or an error occurs.

3. **Loop Body**:
   ```cpp
   std::cout << line << std::endl;
   ```
   - Inside the loop, the line read from the file is printed to the standard output using `std::cout`.
   - `std::cout` is the standard character output stream in C++ (usually the console).
   - `<<` is the stream insertion operator, which outputs the value of `line` to `std::cout`.
   - `std::endl` is an output stream manipulator that inserts a newline character and flushes the output buffer. This ensures that each line is printed on a new line in the console.

### Context in the `readData` Method

This loop is part of the `readData` method in the `DataLogger` class:

```cpp
void readData() {
    std::lock_guard<std::mutex> guard(logMutex);
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        while (getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    }
}
```

### Purpose and Functionality

1. **Locking with `std::lock_guard<std::mutex>`**:
   - Before accessing the file, a `std::lock_guard<std::mutex>` (`guard`) is used to lock the mutex (`logMutex`). This ensures that only one thread can execute the `readData` method at a time, preventing race conditions.

2. **Opening the File**:
   - `std::ifstream inFile(filename);` opens the file specified by `filename` for reading.
   - The `if (inFile.is_open())` check ensures that the file is successfully opened before attempting to read from it.

3. **Reading and Printing Lines**:
   - `std::string line;` declares a string variable to hold each line read from the file.
   - The `while (getline(inFile, line))` loop reads each line from the file until EOF is reached.
   - Inside the loop, each line is printed to the console using `std::cout`.

4. **Closing the File**:
   - `inFile.close();` explicitly closes the file after all lines have been read. While the file will automatically be closed when the `std::ifstream` object goes out of scope, explicitly closing it is a good practice for clarity and ensuring resources are released promptly.

### Example Usage

For example, if the file contains the following lines:

```
First line
Second line
Third line
```

The `readData` method will print:

```
First line
Second line
Third line
```

Each line from the file is read and printed to the console in the same order. This allows the user to view the contents of the file line by line.

!!! Daily Challenge:
* Create a Logger class with methods to log different types of data (int, float, string) using templates.
* Write a program that reads sensor data in one thread and logs it in another thread using the Logger class.
* Implement error handling in the Logger class to handle file I/O errors.
