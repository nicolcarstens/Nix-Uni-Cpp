/******************************************************************************

Author: Udacity
File:   smart pointers convert / release / get  
Goal:   Little sandbox on Smart Pointers 
Keys:   Smart Pointers, get, release, delete

*******************************************************************************/

#include <iostream>
#include <memory>

int main()
{
    // construct a unique pointer
    std::unique_ptr<int> uniquePtr(new int);
    
    // shared pointer from unique pointer
    std::shared_ptr<int> sharedPtr1 = std::move(uniquePtr);

    // shared pointer from weak pointer
    std::weak_ptr<int> weakPtr(sharedPtr1);
    std::shared_ptr<int> sharedPtr2 = weakPtr.lock();

    // raw pointer from shared (or unique) pointer   
    int *rawPtr = sharedPtr2.get();
    // ILLEGAL : delete rawPtr;

    // construct a 2nd unique pointer
    std::unique_ptr<int> uniquePtr2(new int);    
    int *rawPtr2 = uniquePtr2.release();
    // int *rawPtr2 = uniquePtr2.get();
    delete rawPtr2;
        
    return 0;
}