/******************************************************************
 * 
 *   Threads vs Tasks - example 02 - deferred
 *   Based on Udacity Cpp NanoDegree course work, March 2020  
 *   run > g++ -std=c++17 -pthread threads_vs_tasks_02.cpp && ./a.out
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
    // Print system id of worker thread 
    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl; 

    // Simulate work of 0.5 seconds 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (denom == 0)
        throw std::runtime_error("Exception from thread: Division by zero!");

    return num/denom; 
}

int main()
{
    // Print system id of main thread 
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl; 

    // use async to start a task 
    double num = 42.0, denom = 0.0; 

    // Run with and without deferred
    std::future<double> theFuture = std::async(divByNumber, num, denom); 
    // std::future<double> theFuture = std::async(std::launch::deferred,divByNumber, num, denom);

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
 * [OUTPUT with std::async(std::launch::deferred,...]
 * 
 * > Main thread id = 140566419924800
 * > Worker thread id = 140566419924800 <- something like that
 * > xxx
 * 
 * [OUTPUT without deferred ]
 * 
 * > Main thread id = 139750195103552
 * > Worker thread id = 139750176925440 <- something like that
 * > xxx
 * 
 ******************************************************************/