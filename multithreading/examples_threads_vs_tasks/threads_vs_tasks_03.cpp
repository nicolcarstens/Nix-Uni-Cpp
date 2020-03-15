/******************************************************************
 * 
 *   Threads vs Tasks - example 03 - system load 
 *   Based on Udacity Cpp NanoDegree course work, March 2020  
 *   run > g++ -std=c++17 -pthread threads_vs_tasks_03.cpp && ./a.out
 * 
 ******************************************************************/

#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <vector>
#include <chrono>

void workerFunction(int n)
{
    // Print system id of worker thread 
    std::cout << "Worker thread id = " << std::this_thread::get_id() << std::endl; 

    // perform work
    for (int i = 0; i < n; ++i)
    {
        sqrt(12345.6789);
    } 
}

int main()
{
    // Print system id of main thread 
    std::cout << "Main thread id = " << std::this_thread::get_id() << std::endl; 

    // start time measurement
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    // launch various tasks 
    std::vector<std::future<void>> theFutures;
    int nLoops = 1e7, nThreads = 4;
    for (int i = 0; i < nThreads; ++i)
    {
        //theFutures.emplace_back(std::async(std::launch::async, workerFunction, nLoops));
        theFutures.emplace_back(std::async(std::launch::deferred, workerFunction, nLoops));
    }

    // wait for tasks to complete
    for (const std::future<void> &ftr : theFutures)
        ftr.wait();

    // stop time measurement and print execution time 
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Execution finished after " << duration << " microseconds\n"; 

    return 0; 
}

/******************************************************************
 * 
 * [OUTPUT using async]
 * 
 * > Main thread id = 140719603033920
 * > Worker thread id = 140719584855808
 * > Worker thread id = 140719559677696
 * > Worker thread id = 140719568070400
 * > Worker thread id = 140719576463104
 * > Execution finished after 92683 microseconds
 * 
 * [OUTPUT using deferred]
 * 
 * > Main thread id = 139696207181632
 * > Worker thread id = 139696207181632
 * > Worker thread id = 139696207181632
 * > Worker thread id = 139696207181632
 * > Worker thread id = 139696207181632
 * > Execution finished after 132659 microseconds
 * 
 *   ... not the complete story -> run nLoops = 10/1e7 as well ... 
 * 
 ******************************************************************/