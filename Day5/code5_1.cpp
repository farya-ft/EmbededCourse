#include <iostream>
#include <thread>

// Function to be executed by a thread
void threadFunction(int threadId) {
 for (int i = 0; i < 5; ++i) {
     std::cout << "Thread " << threadId << " executing" << std::endl;
 }
}

int main() {
  std::thread t1(threadFunction, 1);
  std::thread t2(threadFunction, 2);

   t1.join();
   t2.join();

   /*threadFunction(1);
    threadFunction(2);*/


  return 0;
}

/*
    threadFunction(1);
    threadFunction(2);
In this version, the threadFunction is called twice sequentially in the main function.
 This means that threadFunction(1) completes all its executions before threadFunction(2) starts.
 This is a single-threaded approach.*/

 /*In this version, two threads (t1 and t2) are created to execute threadFunction concurrently. 
 The std::thread class from the <thread> library is used to create and manage these threads. 
 Each thread runs threadFunction simultaneously, allowing parallel execution.*/