/******************************************************************
 * 
 *   Promises and Futures thread examples 01 - first the basics!
 *   Based on Udacity Cpp NanoDegree course work, March 2020  
 *   run > g++ -std=c++17 -pthread promise_future_01.cpp && ./a.out  
 * 
 *   Additional info:
 *   -> https://thispointer.com/c11-multithreading-part-3-carefully-pass-arguments-to-threads/
 * 
 ******************************************************************/

#include <iostream>
#include <thread>

void printMessage(std::string message)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "Thread 1: " << message << std::endl;
}

int main()
{
    // define message
    std::string message = "My Message";

    // start thread using variadic templates
    std::thread t1(printMessage, message);

    // start thread using a lambda
    std::thread t2([message] {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // simulate work 
        std::cout << "Thread 2: " << message << std::endl;
    });

    // thread barrier 
    t1.join();
    t2.join();

    return 0; 
}