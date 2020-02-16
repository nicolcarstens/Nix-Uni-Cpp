/******************************************************************************

https://cpppatterns.com/patterns/rule-of-five.html

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <utility>
#include <memory>

using namespace std;

class resource {
  int x = 0;
  // int RID = 999;
};

class foo
{
  
  public:
    static int counter;
  
    // CONSTRUCTOR - 0
    foo() : ptrR(new resource) {
        ID = foo::counter;
        foo::counter ++;
        cout << "Vanilla Constructor (0) Called for ID " << ID << "\n";
        cout << "this   = " << this << "\n";
    }
  
    // COPY CONSTRUCTOR - 1
    foo(const foo& other): ptrR(new resource{*(other.ptrR)})
    {
        cout << "BEGIN: this   = " << this << "\n";
        cout << "BEGIN: &other = " << &other << "\n";
        ID = foo::counter;
        foo::counter ++;
        cout << "Copy Constructor (1) Called for ID " << ID << "\n";
        cout << "END: this   = " << this << "\n";
        cout << "END: &other = " << &other << "\n";
    }
    
    // MOVE CONSTRUCTOR - 2
    foo(foo&& other) : ptrR(other.ptrR)
    {
        ID = foo::counter;
        //resource.RID = ID;
        foo::counter ++;
        cout << "Move Constructor (2) Called for ID " << ID << "\n";
        cout << "BEGIN: this   = " << this << "\n";
        cout << "BEGIN: &other = " << &other << "\n";
        other.ptrR = nullptr;
        cout << "END: this   = " << this << "\n";
        cout << "END: &other = " << &other << "\n";
    }
    
    // COPY ASSIGNMENT OPERATOR - 3
    foo& operator=(const foo& other)
    {
      // NB : NO COPYING ID NUMBER!! Old ID RETAINED
      cout << "Copy Assignement Operator (3) Called\n";
      cout << "BEGIN: this   = " << this << "\n";
      cout << "BEGIN: &other = " << &other << "\n";
      
      if (&other != this) {
        delete ptrR;
        ptrR = nullptr;
        ptrR = new resource{*(other.ptrR)};
      }

      cout << "END: this   = " << this << "\n";
      cout << "END: &other = " << &other << "\n";
      return *this;
    }
    
    // MOVE ASSIGNMENT OPERATOR - 4
    foo& operator=(foo&& other)
    {
      // NB : NO MOVING ID NUMBER!! Old ID RETAINED
      cout << "Move Assignement Operator (4) Called\n";
      cout << "BEGIN: this   = " << this << "\n";
      cout << "BEGIN: &other = " << &other << "\n";
      
      if (&other != this) {
        delete ptrR;
        ptrR = other.ptrR;
        other.ptrR = nullptr;
      }
      
      cout << "END: this   = " << this << "\n";
      cout << "END: &other = " << &other << "\n";
      return *this;
    }
    
    // DESTRUCTOR - DTOR - 5
    ~foo()
    {
      delete ptrR;
      cout << "Destructor (5) Called for ID " << ID << "\n";
    }
    
    void printID(string s){
        cout << "My name is " << s << " and my ID = " << ID << "\n";
    }

    void printResourcePointer(string s){
        if (ptrR!=nullptr){
            cout << "My name is " << s << " and my Resource Ptr = " << ptrR << "\n";
        } else {
            cout << "My name is " << s << " and my Resource Ptr is nullptr \n";
        }
    }
    
  private:
    resource* ptrR;
    int ID;
};

// Init object counter
int foo::counter = 0;

int main()
{
    printf("Hello rule-of-five World\n");
    
    cout << "======================= \n";
    cout << ">> foo f1; \n";
    foo f1;
    f1.printID("f1");

    cout << "======================= \n";
    cout << ">> foo f2(f1); \n";
    foo f2(f1);
    f2.printID("f2");
 
    cout << "======================= \n";
    cout << ">> foo f3 = f1; \n";
    foo f3 = f1;
    f3.printID("f3");
    
    cout << "======================= \n";
    cout << ">> f2 = f1; \n";
    f2 = f1;
    f2.printID("f2");
    f2.printResourcePointer("f2");
    f1.printID("f1");
    f1.printResourcePointer("f1");

    cout << "======================= \n";
    cout << ">> foo * ptrF3 = &f3 \n";
    foo * ptrF3 = &f3;
    cout << ">> ptrF3 = &f1; \n";
    ptrF3 = &f1;
    ptrF3->printID("ptrF3");
    f3.printID("f3");
    cout << "Don't be silly ;-) \n";
    
    cout << "======================= \n";
    f1.printResourcePointer("f1");
    cout << ">> foo f4(std::move(f1)); \n";
    foo f4(std::move(f1));
    f4.printID("f4");
    f4.printResourcePointer("f4");
    f1.printID("f1");
    f1.printResourcePointer("f1");
    cout << "&f4 = " << &f4 << "\n";
    cout << "&f1 = " << &f1 << "\n";
    cout << "std::move() is really a fancy cast... does break f1\n";
    
    cout << "======================= \n";

    cout << "easy one ... move assignment to f2 ... \n";
    f2 = foo();

    cout << "======================= \n";

    unique_ptr<foo> f5(new foo);
    f5->printID("f5");
    f5->printResourcePointer("f5");
    
    cout << "======================= \n";
    
    unique_ptr<foo> f6(new foo);
    f6->printID("f6");
    f6->printResourcePointer("f6");
    
    cout << "======================= \n";
 
    cout << "f5 = std::move(f6); \n";
    f5 = std::move(f6);
    
    f5->printID("f5");
    f5->printResourcePointer("f5");
    
    // f6 has died ... no more f6 ...
    // ILLEGAL : f6->printID("f6");
    // ILLEGAL : f6->printResourcePointer("f6");
    
    // But does that mean that no move assignment operator was required?!
    // It's like it was just normal pointer that was clever enough to
    // call the applicable Destructor
        
    cout << "======================= \n";
    
    return 0;
}
