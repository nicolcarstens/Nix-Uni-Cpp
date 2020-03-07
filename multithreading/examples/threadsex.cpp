// Little demo/example code for threads 
// compile using >> g++ threadsex.cpp -pthread 

#include <iostream>
#include <thread>

void threadFunction()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work 
    std::cout << "Finished work 1 in thread\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // simulate work 
    std::cout << "Finished work 2 in thread\n";
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

    // OPTIONAL - using join() as barrier 
    t.join();

    // do something in main()
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work 1 in main\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout << "Finished work 2 in main\n";

    // wait for thread to finish
    // t.join(); 

    return 0;   
}