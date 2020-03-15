/******************************************************************
 * 
 *   Data Races - example 03 - Deep Copy => Copy Constructor  
 *   Based on Udacity Cpp NanoDegree course work, March 2020  
 *   run > g++ -pthread data_races_03_copy.cpp && ./a.out
 * 
 ******************************************************************/

#include <iostream>
#include <thread>
#include <future>

class Vehicle
{
public:
    //default constructor
    Vehicle() : _id(0), _name(new std::string("Default Name"))
    {
        std::cout << "Vehicle #" << _id << " Default constructor called" << std::endl;
    }

    //initializing constructor
    Vehicle(int id, std::string name) : _id(id), _name(new std::string(name))
    {
        std::cout << "Vehicle #" << _id << " Initializing constructor called" << std::endl;
    }

    // copy constructor 
    Vehicle(Vehicle const &src)
    {
        std::cout << "Copy Construct in thread = " << std::this_thread::get_id() << std::endl; 

        // QUIZ: Student code STARTS here =================================
        _id = src._id;
        if (src._name != nullptr)
        {
            _name = new std::string;
            *_name = *src._name;
        }
        // QUIZ: Student code ENDS here ===================================

        std::cout << "Vehicle #" << _id << " copy constructor called" << std::endl;
    };

    // setter and getter
    void setID(int id) { _id = id; }
    int getID() { return _id; }
    void setName(std::string name) { *_name = name; }
    std::string getName() { return *_name; }

private:
    int _id;
    std::string *_name;
};

int main()
{
    std::cout << "Main thread = " << std::this_thread::get_id() << std::endl; 

    // create instances of class Vehicle
    Vehicle v0;                 // default constructor
    Vehicle v1(1, "Vehicle 1"); // initializing constructor

    // DEBUG ONLY 
    std::cout << "Done with first creates... \n";

    // launch a thread that modifies the Vehicle name
    std::future<void> ftr = std::async([](Vehicle v) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1500)); // simulate work
        std::cout << "Setname Vehicle 2 .. in lambda ..\n";
        v.setName("Vehicle 2");
    },v0);

    // DEBUG ONLY 
    std::cout << "Setname Vehicle 3... \n";

    v0.setName("Vehicle 3");

    // DEBUG ONLY 
    std::cout << "Start WAIT... \n";

    ftr.wait();
    std::cout << v0.getName() << std::endl;

    return 0;
}