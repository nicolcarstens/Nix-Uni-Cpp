/******************************************************************
 * 
 *   Threads vs Tasks - example 01 - Starting threads with async
 *   Based on Udacity Cpp NanoDegree course work, March 2020  
 *   run > g++ -std=c++17 -pthread threads_vs_tasks_01.cpp && ./a.out
 * 
 *   Notes:
 *   -> Promise-Future approach is very cumbersome
 *   -> Going to look at std::async() instead of std::thread()
 * 
 ******************************************************************/

#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

double divByNumber(double num, double denom)
{
    // Simulate work of 0.5 seconds 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (denom == 0)
        throw std::runtime_error("Exception from thread: Division by zero!");

    return num/denom; 
}

int main()
{
    // use async to start a task 
    double num = 42.0, denom = 0.0; 
    std::future<double> theFuture = std::async(divByNumber, num, denom); 

    // retreive result within a try-catch-block
    try 
    {
        double result = theFuture.get();
        std::cout << "Result = " << result << std::endl;
    }
    catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }

    // Note: no join() required 

    return 0; 
}

/******************************************************************
 * 
 * [OUTPUT with denom = 2.0]
 * 
 * > Result = 21 
 * 
 * [OUTPUT with denom = 0.0]
 * 
 * > Exception from thread: Division by zero! 
 * 
 ******************************************************************/