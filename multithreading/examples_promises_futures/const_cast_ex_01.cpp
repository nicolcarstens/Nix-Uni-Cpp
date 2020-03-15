/******************************************************************************
 * 
 * const_cast<> Here be Dragons! 
 * https://www.tutorialspoint.com/const-cast-in-cplusplus-type-casting-operators
 * ... inspired by ... 
 * https://thispointer.com/c11-multithreading-part-3-carefully-pass-arguments-to-threads/
 * 
 ******************************************************************************/
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
    printf("Hello World\n");
    
    // CAUTION: compiler could optimize out the x = 50 constant since 
    //          expects that constant wont change
    //          getting different behavior between debugger and normal Run
    //          remove volatile and see the effect!
    //          my opinion? const_cast<> is a BAD idea => don't say something
    //          is constant unless it really is!! DC is DC. Not slow AC!! 
    
    // volatile const int x = 50;
    // volatile const int* y = &x;

    const int x = 50;
    const int* y = &x;
    
    cout << "y address = " << y << endl;
    cout<<"old value of *y is "<<*y<<"\n";
    cout << "y address = " << y << endl;
    int* z=const_cast<int *>(y);
    cout << "y address = " << y << endl;
    *z=100;
    cout<<"new value of *y is "<<*y<< " with address of y = " << y << endl;
    cout<<"and value of x is "<<x<< " with address of x = " << &x << std::endl;

    return 0;
}
