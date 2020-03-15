/******************************************************************
 * 
 *   Promises and Futures thread examples 04 - passing exceptions
 *   Based on Udacity Cpp NanoDegree course work, March 2020  
 *   run > g++ -std=c++17 -pthread promise_future_04.cpp && ./a.out
 * 
 ******************************************************************/

#include <iostream>
#include <thread>
#include <future>
#include <cmath>
#include <memory>

void divideByNumber(std::promise<double> && prms, double num, double denom)
{
    // simulate work being done for 0.5 seconds 
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    try
    {
        if (denom == 0)
            throw std::runtime_error("Exception from thread: Division by zero!!");
        else
        {
            prms.set_value(num/denom);
        }   
    }
    catch(...)
    {
        prms.set_exception(std::current_exception());
    }
}

int main()
{
    // create promise and future 
    std::promise<double> thePromise;
    std::future<double> theFuture = thePromise.get_future();

    // define input data
    double num = 42.0, denom = 0.21;
    std::thread t(divideByNumber,std::move(thePromise),num,denom);

    // retreive result within try-catch-block 
    try
    {
        double result = theFuture.get();
        std::cout << "The Result = " << result << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    // thread barrier 
    t.join(); 

    return 0; 
}

/******************************************************************
 * 
 * [OUTPUT if denom = 0.0]
 * 
 * > Exception from thread: Division by zero!!
 * 
 * [OUTPUT if denom = 0.21]
 * 
 * > The Result = 200
 * 
 ******************************************************************/