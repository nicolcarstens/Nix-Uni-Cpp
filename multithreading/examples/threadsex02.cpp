// Little demo/example code for threads - #02
// compile using >> g++ threadsex02.cpp -pthread 

#include <iostream>
#include <thread>

class Vehicle
{
public: 
    void operator()()
    {
        std::cout << "Vehicle object has been created \n";
    }
};

int main()
{
    // create thread 
    // PROBLEM ==>>  std::thread t(Vehicle());  // C++'s most vexing parse 
    // ... ambiguous ... function def or variable declare? 
    // Solution? 3 options:

    std::thread t1( (Vehicle()) );  // Add an extra pair of parantheses
    std::thread t2 = std::thread(Vehicle()); // Copy Initialization 
    std::thread t3{ Vehicle() };    // Uniform Initialization with Braces  

    // do something in main I
    std::cout << "Finished working in main \n";

    // waiting for thread to finish
    t1.join(); 
    t2.join();
    t3.join();

    return 0;   
}