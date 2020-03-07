// Little demo/example code for threads 
// compile using >> g++ threadsex.cpp -pthread 

#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // simulate work 
    std::cout << "Finished work in thread\n";
}

void printMachineInfo()
{
    std::cout << "Hello concurrent world from main! Thread ID = " << 
       std::this_thread::get_id << std::endl;

    unsigned int nCores = std::thread::hardware_concurrency();

    std::cout << "This Machines supports concurrency with " << nCores << " cores available" << std::endl;
}

int main()
{
    printMachineInfo();

    // create a thread 
    std::thread t(threadFunction);

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work in main\n";

    // wait for thread to finish
    t.join(); 

    return 0;   
}