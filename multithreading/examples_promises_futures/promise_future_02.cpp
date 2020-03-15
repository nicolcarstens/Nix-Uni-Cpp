/******************************************************************
 * 
 *   Promises and Futures thread examples 02
 *   Based on Udacity Cpp NanoDegree course work, March 2020  
 *   run > g++ -std=c++17 -pthread promise_future_02.cpp && ./a.out
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

void modifyMessage(std::promise<std::string> && prms, std::string message)
{
    // simulate doing work 
    std::this_thread::sleep_for(std::chrono::milliseconds(4000)); 

    // modify the message 
    std::string modifyMessageStr = message + " has been modified!";
    
    // set the promise... 
    prms.set_value(modifyMessageStr);
}

int main()
{
    // define message
    std::string messageToThread = "My Message";

    // create promise and future 
    // ... read var "a Promise" and "a Future" :-)
    std::promise<std::string> aPromise;
    std::future<std::string> aFuture = aPromise.get_future();  

    // start thread and pass promise as an argument 
    std::thread t(modifyMessage,std::move(aPromise),messageToThread);

    // print the original message to console 
    std::cout << "Original message from main: " << messageToThread << std::endl;

    // retrieve modified message via future and print to console
    // note: get() will block until data is available, 
    //       which happens when set_value is called 
    //       if get() is called a second time, and exception will be thrown
    std::string messageFromThread = aFuture.get();
    std::cout << "Modified message from the thread: " << messageFromThread << std::endl;

    // thread barrier 
    t.join();
    // t.detach();

    return 0; 
}

/******************************************************************
 * 
 * [OUTPUT]
 * 
 * > Original message from main: My Message
 * > Modified message from the thread: My Message has been modified!
 * 
 ******************************************************************/