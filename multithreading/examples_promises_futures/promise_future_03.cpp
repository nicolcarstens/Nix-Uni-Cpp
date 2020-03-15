/******************************************************************
 * 
 *   Promises and Futures thread examples 03 - wait() vs get()
 *   Based on Udacity Cpp NanoDegree course work, March 2020  
 *   run > g++ -std=c++17 -pthread promise_future_03.cpp && ./a.out
 * 
 *   -> wait() will block until future is ready!
 *   -> does not get() immediately
 *   -> wait_for() will block either for specified timeout or till 
 *      result becomes available 
 * 
 *   Additional info:
 *   -> https://www.modernescpp.com/index.php/promise-and-future
 *   -> http://www.cplusplus.com/reference/future/promise/
 *   -> http://www.cplusplus.com/reference/future/promise/set_value/
 *   -> https://en.cppreference.com/w/cpp/thread/future
 * 
 ******************************************************************/

#include <iostream>
#include <thread>
#include <future>
#include <cmath>

void computeSqrt(std::promise<double> && prms, double input)
{
    // simulate work being done for 2 seconds 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    double output = sqrt(input);
    prms.set_value(output);
}

int main()
{
    // define input data
    double inputData = 42.0;

    // create promise and future 
    std::promise<double> thePromise;
    std::future<double> theFuture = thePromise.get_future();

    // start thread and pass promise as argument 
    // note: inputData called by value thus copy arrives at function
    std::thread t(computeSqrt,std::move(thePromise),inputData);

// Student task STARTS here =======================================

    // auto status = theFuture.wait_for(std::chrono::milliseconds(3000));
    auto status = theFuture.wait_for(std::chrono::milliseconds(1000));

    if (status == std::future_status::ready) // result is ready
    {
        std::cout << "Result = " << theFuture.get() <<  std::endl;
    }
    else if (status == std::future_status::timeout || status == std::future_status::deferred)
    {
        std::cout << "Result unavailable \n";
    }

// Student task ENDS here =========================================

    // thread barrier 
    t.join(); 

    return 0; 
}

/******************************************************************
 * 
 * [OUTPUT if theFuture.wait_for(std::chrono::milliseconds(1000))]
 * 
 * > Result unavailable
 * 
 * [OUTPUT if theFuture.wait_for(std::chrono::milliseconds(3000))]
 * 
 * > Result = 6.48074
 * 
 ******************************************************************/