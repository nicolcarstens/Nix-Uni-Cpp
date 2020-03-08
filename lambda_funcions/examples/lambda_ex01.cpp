//
// Simple Lambda function examples
// run >> g++ --std=c++11 lambda_ex01.cpp 
// 'auto' type specifier is a C++11 extension [-Wc++11-extensions]
// Copyright: Udacity 2020
//
// A Lambda is a function object (a "functor"), so it has a type and 
// can be stored and passed around. Its result object is called a 
// "closure", which can be called using the operator ().
//
// A lambda formally consists of three parts: 
//  => a capture list []
//  => a parameter list () 
//  => and a main part {}
// ... which contains the code to be executed when the Lambda is called.
// Note that in principal all parts could be empty.
//

#include <iostream>

int main()
{
    // create lambdas
    int id = 0; // Define an integer variable

    //auto f0 = []() { std::cout << "ID = " << id << std::endl; }; // Error: 'id' cannot be accessed

    id++;
    auto f1 = [id]() { std::cout << "ID = " << id << std::endl; }; // OK, 'id' is captured by value

    id++;
    auto f2 = [&id]() { std::cout << "ID = " << id << std::endl; }; // OK, 'id' is captured by reference

    //auto f3 = [id]() { std::cout << "ID = " << ++id << std::endl; }; // Error, 'id' may not be modified

    auto f4 = [id]() mutable { std::cout << "ID = " << ++id << std::endl; }; // OK, 'id' may be modified

    // execute lambdas
    f1();
    f2();
    f4();

    return 0;
}