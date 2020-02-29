/******************************************************************************

Little own practice writing Rule of 5 example
VERY silly and artificial ... focus: moving & copying unique pointers!

... with a dash of color ...
https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <memory>

using namespace std;

// TODO: LOOOOOAAAAADS to to !! cout << operator overload, etc.

#define cBLK  "\033[1;30m"   /*  black   */
#define cRED  "\033[1;31m"   /*  red     */
#define cGRN  "\033[1;32m"   /*  green   */
#define cYEL  "\033[1;33m"   /*  yellow  */
#define cBLU  "\033[1;34m"   /*  blue    */
#define cMAG  "\033[1;35m"   /*  magenta */
#define cCYN  "\033[1;36m"   /*  cyan    */
#define cWIT  "\033[1;37m"   /*  white   */

class animal {
private:
    // TODO: add text, example a name / string and char array
    static int index; // class static variable index for object number
    int* pDataID;     // DO NOT COPY this field - remains unique from contruction till terminnation
    int* pAge;
    int legs;
public:
    animal() : legs(0) {
        pDataID = new int(index);
        cout << cGRN << "CONstructed default animal (index "<< *this->pDataID << ")...\n" << cWIT;
        index++;
        pAge = new int(0);
    }
        
    animal(int aLegs, int aAge) : legs(aLegs) {
        pDataID = new int(index);
        cout << cGRN << "CONstructed default animal with legs (index "<< *this->pDataID << ")...\n" << cWIT;
        index++;
        pAge = new int(aAge);
    }
    
    ~animal() {
        cout << cRED << "DEstructing default animal (index "<< *this->pDataID << ")...\n" << cWIT;
        
        if (this->pAge != nullptr){
            cout << cBLU << "Delete pAge\n" << cWIT;
            delete this->pAge;
        } else {
            cout << cBLU << "DO NOT Delete pAge\n" << cWIT;
        }
        
        if (this->pDataID != nullptr){
            cout << cBLU << "Delete pDataID\n" << cWIT;
            delete this->pDataID;
        } else {
            cout << cBLU << "DO NOT Delete pDataID\n" << cWIT;
        }
    }
    
    void printAnimalIndex(){
        if (pDataID == nullptr){
            cout << "I have no point - cant print *pDataID\n";
        } else {
            cout << "My index = " << *pDataID << "\n";
        }
    }
    
    void printAnimalIndex_CONST_FUNC() const{
        if (pDataID == nullptr){
            cout << "I have no point - cant print *pDataID\n";
        } else {
            cout << "My index = " << *pDataID << "\n";
        }
    }
    
    
    void printAnimalAge(){
        if (pAge == nullptr){
            cout << "I have no point - cant print *pAge\n";
        } else {
            cout << "My age = " << *pAge << "\n";
        }
    }
    
    void setAnimalAge(int aAge){
        if (pAge == nullptr){
            cout << "I have no point - cant set *pAge\n";
        } else {
            *pAge = aAge;
        }
    }
    
    // COPY constructor
    animal(const animal &source){
        this->pDataID = new int(index); index++;
        cout << cGRN << "COPY constructed animal (index " << *this->pDataID << ")...\n" << cWIT;
        cout << cGRN << "COPY animal "<< *source.pDataID << " to "<< *this->pDataID << "...\n" << cWIT;
        this->legs = source.legs;
        int temp = *source.pAge;
        this->pAge = new int(temp);
    }
    
    // MOVE constructor
    animal(animal &&source){
        this->pDataID = new int(index); index++;
        cout << cGRN << "MOVE constructed animal (index "<< *this->pDataID << ")...\n" << cWIT;
        cout << cGRN << "MOVE animal "<< *source.pDataID << " to "<< *this->pDataID << "...\n" << cWIT;
        this->legs = source.legs;
        source.legs = 0;
        this->pAge = source.pAge;
        source.pAge = nullptr;
        cout << "... got this far\n";
    }
    
    animal &operator=(const animal &source){
        // TODO: ADD BOILER CODE for self assignement prevention
        cout << "COPY ASSIGNMENT operator\n" << cWIT;
        // *this->pDataID = *source.pDataID;  <<== Should one copy index too? no..
        
        this->legs = source.legs;

        *this->pAge = *source.pAge;
    }
    
    animal &operator=(animal &&source){
        // TODO: ADD BOILER CODE for self assignement prevention
        cout << "MOVE ASSIGNMENT operator\n" << cWIT;
        
        // *this->pDataID = *source.pDataID;  <<== Should one move index too? no..
        
        this->legs = source.legs;
        source.legs = 0;
        
        delete this->pAge;
        this->pAge = source.pAge;
        source.pAge = nullptr;
    }
    
};

int animal::index = 0;

// chop up animals - SANDBOX!!
// test pass by value vs pass by reference for OBJECTs and POINTERS
// ... including smart pointers and raw pointers and lvalue references

// RECEIVING OBJECTS ... NOT POINTERS ...

//==============================================
//  copyChop_0_(msPiggy);             <<== call by value, thus copy constructor
//  copyChop_0_(std::move(msPiggy));  <<== calls move constructor
//==============================================
void copyChop_0_(animal object){
   // should also look into a version that keeps pointer or object const!?
    cout << cYEL << "OBJECT CHOP 0 -> ENTER\n" << cWIT;
    
    cout << "OBJECT Chopping \n";
    object.printAnimalIndex();
    
    cout << cYEL << "OBJECT CHOP 0 -> EXIT!!\n" << cWIT;
}

//==============================================
//  chopChop_1_(msPiggy);             <<== no constructor required!
//  chopChop_1_(std::move(msPiggy));  <<== NOT ALLOWED!! have to call with lvalue
//==============================================
void chopChop_1_(animal &object){
   // should also look into a version that keeps pointer or object const!?
    cout << cYEL << "OBJECT - lvalue ref [&a] - CHOP 1 -> ENTER\n" << cWIT;
    
    cout << "OBJECT Chopping \n";
    object.printAnimalIndex();
    
    cout << cYEL << "OBJECT - lvalue ref [&a] - CHOP 1 -> EXIT!!\n" << cWIT;
}

//==============================================
// No copy or move required - lvalue reference
//==============================================
void chopChop_2_(animal &&object){
   // should also look into a version that keeps pointer or object const!?
    cout << cYEL << "OBJECT - rvalue ref [&&a] - CHOP 2 -> ENTER\n" << cWIT;
    
    cout << "OBJECT Chopping \n";
    object.printAnimalIndex();
    
    cout << cYEL << "OBJECT - rvalue ref [&&a] - CHOP 2 -> EXIT!!\n" << cWIT;
}

void testObjTransfer(int testCase){
    // should be using enum!!
    
    cout << cCYN << "Test Object Transfer Test Case " << testCase << "\n" << cWIT;

    cout << cMAG  "-------- OBJECT Chop Scope - PRE ENTER -------- \n" << cWIT;
    {
        cout << cMAG  "-------- OBJECT Chop Scope - ENTER -------- \n" << cWIT;
        // miss Piggy goes in and out of scope... how cool is that?
        animal msPiggy;
        
        // now less pass miss Piggy
        if (testCase == 0) {
            //copyChop_0_(msPiggy);               // <<== call by value, thus COPY constructor
            copyChop_0_(std::move(msPiggy));  // <<== calls MOVE constructor
            
        } else if (testCase == 1) {
            chopChop_1_(msPiggy);                // no constructor required!
            // chopChop_1_(std::move(msPiggy));  // <<== NOT ALLOWED!! have to call with lvalue
            
        } else if (testCase == 2) {
            chopChop_2_(std::move(msPiggy));    // no constructor required!
            // chopChop_2_(msPiggy);            //  <<== NOT ALLOWED!! have to call with rvalue
            
        } else {
            cout << cRED << "WHAT SHOULD I DO WITH THIS PIG??? \n" << cWIT;
        }
        cout << cMAG  "-------- OBJECT Chop Scope - EXIT -------- \n" << cWIT;
    }
    cout << cMAG  "-------- OBJECT Chop Scope - POST EXIT -------- \n" << cWIT;
}

void testKittens(void){
    
    cout << cCYN << "VERSION 1 for testing basic Copy/Move Construct and Assignment\n" << cWIT;

    {
    cout << "Creating Amy\n";
    
    animal amy;
    amy.printAnimalIndex();
    amy.printAnimalAge();
    amy.setAnimalAge(19);
    amy.printAnimalAge();
    
    cout << "Creating Tegan\n";
    
    animal tegan(amy);
    tegan.printAnimalAge();
    tegan.printAnimalIndex();
    amy.setAnimalAge(23);
    
    cout << "Creating Tee\n";
    
    animal tee(std::move(tegan));
    tee.printAnimalAge();
    tee.printAnimalIndex();
    
    cout << "Creating John\n";
    
    animal john(2,20);
    john.printAnimalIndex();
    }

    cout << "Now we switch to Copy and Move assignement testing... \n";
    
    cout << "Create cat1 ...............\n";
    animal cat1(11,11);
    cat1.printAnimalIndex();
    cat1.printAnimalAge();
    
    cout << "Create cat2 ...............\n";
    animal cat2(22,22);
    cat2.printAnimalIndex();
    cat2.printAnimalAge();
    
    cout << "COPY Cat1 to Cat2  >>>>>>>>>>>>>>>>>\n";
    cat2 = cat1;
    cout << "For cat2: \n";
    cat2.printAnimalIndex();
    cat2.printAnimalAge();
    cout << "For cat1: \n";
    cat1.printAnimalIndex();
    cat1.printAnimalAge();
    
    cout << "Create cat3 ...............\n";
    animal cat3(33,33);
    cat3.printAnimalIndex();
    cat3.printAnimalAge();
    
    cout << "Create cat4 ...............\n";
    animal cat4(44,44);
    cat4.printAnimalIndex();
    cat4.printAnimalAge();
    
    cout << "MOVE Cat3 to Cat4 >>>>>>>>>>>>>>>>>\n";
    cat4 = std::move(cat3);
    cout << "For cat3: ... kittie is part gone!!\n";
    cout << "NB: that does not mean destructor has been called on cat3!!\n";
    cat3.printAnimalIndex();
    cat3.printAnimalAge();
    cout << "For cat4: \n";
    cat4.printAnimalIndex();
    cat4.printAnimalAge();
}

//==============================================
// chopPtrChop_0_(ptrMissPiggy); // <<== call
// chopPtrChop_0_(ptrMissPiggy.get()); // <<== call
// chopPtrChop_0_(std::move(ptrMissPiggy));  // <<== CANT DO THIS
//==============================================
void chopPtrChop_0_(animal *ptr){
   // should also look into a version that keeps pointer or object const!?
    cout << cYEL << "POINTER - (animal *ptr) - CHOP 0 -> ENTER\n" << cWIT;
    
    cout << "POINTER Chopping \n";
    ptr->printAnimalIndex();
    
    cout << cYEL << "POINTER - (animal *ptr) - CHOP 0 -> EXIT!!\n" << cWIT;
}

//==============================================
//==============================================
void chopPtrChop_1_(unique_ptr<animal> ptr){
   // should also look into a version that keeps pointer or object const!?
    cout << cYEL << "POINTER - (unique_ptr<animal> ptr) - CHOP 1 -> ENTER\n" << cWIT;
    
    cout << "POINTER Chopping \n";
    ptr->printAnimalIndex();
    
    cout << cYEL << "POINTER - (unique_ptr<animal> ptr) - CHOP 1 -> EXIT!!\n" << cWIT;
}

//==============================================
// NB: need to call printAnimalIndex_CONST_FUNC()
//     rather than printAnimalIndex()
// Because of const animal ...
// You have to PROMISE NOT to change ANYTHING
//==============================================
void chopPtrChop_3_(const animal *ptr){
    // should also look into a version that keeps pointer or object const!?
    
    cout << cYEL << "POINTER - (const animal *ptr) - CHOP 3 -> ENTER\n" << cWIT;
    
    cout << "POINTER Chopping \n";
    ptr->printAnimalIndex_CONST_FUNC();
    
    cout << cYEL << "POINTER - (const animal *ptr) - CHOP 3 -> EXIT!!\n" << cWIT;
}

//==============================================
// NB: need to call printAnimalIndex_CONST_FUNC()
//     rather than printAnimalIndex()
// Because of const animal ...
// You have to PROMISE NOT to change ANYTHING
//==============================================
void chopPtrChop_4_(const animal * const ptr){
    // should also look into a version that keeps pointer or object const!?
    
    cout << cYEL << "POINTER - (const animal * const ptr) - CHOP 4 -> ENTER\n" << cWIT;
    
    cout << "POINTER Chopping \n";
    ptr->printAnimalIndex_CONST_FUNC();
    
    cout << cYEL << "POINTER - (const animal * const ptr) - CHOP 4 -> EXIT!!\n" << cWIT;
}

//==============================================
//==============================================
void chopPtrChop_5_(unique_ptr<animal> &ptr){
   // should also look into a version that keeps pointer or object const!?
    cout << cYEL << "POINTER - (unique_ptr<animal> &ptr) - CHOP 5 -> ENTER\n" << cWIT;
    
    cout << "POINTER Chopping \n";
    ptr->printAnimalIndex();
    
    cout << cYEL << "POINTER - (unique_ptr<animal> &ptr) - CHOP 5 -> EXIT!!\n" << cWIT;
}

//==============================================
//==============================================
void chopPtrChop_6_(unique_ptr<animal> &&ptr){
   // should also look into a version that keeps pointer or object const!?
    cout << cYEL << "POINTER - (unique_ptr<animal> &&ptr) - CHOP 6 -> ENTER\n" << cWIT;
    
    cout << "POINTER Chopping \n";
    ptr->printAnimalIndex();
    
    cout << cYEL << "POINTER - (unique_ptr<animal> &&ptr) - CHOP 6 -> EXIT!!\n" << cWIT;
}

void testMoveCopyUniquePointers(int testCase){
    // should be using enum!!

    cout << cCYN << "Move/Copy Unique Pointer ==>> Test Case = " << testCase << "\n" << cWIT;

    cout << cMAG  "-------- POINTER Chop Scope - PRE ENTER -------- \n" << cWIT;
    {
        cout << cMAG  "-------- POINTER Chop Scope - ENTER -------- \n" << cWIT;
        // miss Piggy goes in and out of scope... how cool is that?
        unique_ptr<animal> ptrMissPiggy = std::make_unique<animal>();
        
        // now less pass miss Piggy
        if (testCase == 0) {
            //=================================
            // CALL chopPtrChop_0_(animal *ptr)
            //=================================
            // chopPtrChop_0_(ptrMissPiggy); // <<== call
            // chopPtrChop_0_(ptrMissPiggy.get()); // <<== call
            // chopPtrChop_0_(std::move(ptrMissPiggy));  // <<== CANT DO THIS ?!
            
        } else if (testCase == 1) {
            //=============================================
            // CALL chopPtrChop_1_(unique_ptr<animal> ptr)
            //=============================================
            // chopPtrChop_1_(ptrMissPiggy);             // <<== CANT DO THIS ?!
            // chopPtrChop_1_(std::move(ptrMissPiggy));  // <<== GOOD
            //  chopPtrChop_1_(ptrMissPiggy.get());      // <<== CANT DO THIS ?!
            
        } else if (testCase == 3) {
            //=======================================
            // CALL chopPtrChop_3_(const animal *ptr)
            //=======================================
            // chopChop_3_(std::move(ptrMissPiggy));    //
            // chopChop_3_(ptrMissPiggy);               //  <<==

        } else if (testCase == 4) {
            //==============================================
            // CALL chopPtrChop_4_(const animal * const ptr)
            //==============================================
            // chopPtrChop_4_(ptrMissPiggy);             // <<==
            // chopPtrChop_4_(std::move(ptrMissPiggy));  // <<==
            // chopPtrChop_4_(ptrMissPiggy.get());       // <<==
            
        } else if (testCase == 5) {
            //================================
            // CALL (unique_ptr<animal> &ptr)
            //================================
            // chopPtrChop_5_(ptrMissPiggy);             // <<== ALL GOOD
            // chopPtrChop_5_(std::move(ptrMissPiggy));  // <<== MUST call with lvalue
            // chopPtrChop_5_(ptrMissPiggy.get());       // <<== NOT good -> raw vs smart pointer
            
        } else if (testCase == 6) {
            //=================================
            // CALL (unique_ptr<animal> &&ptr)
            //=================================
            // chopPtrChop_6_(ptrMissPiggy);             // <<== MUST call with rvalue ref
            // chopPtrChop_6_(std::move(ptrMissPiggy));  // <<== ALL GOOD
            // chopPtrChop_6_(ptrMissPiggy.get());       // <<== MUST call with rvalue ref
        } else {
            cout << cRED << "WHAT SHOULD I DO WITH THIS PIG??? \n" << cWIT;
        }
        cout << cMAG  "-------- POINTER Chop Scope - EXIT -------- \n" << cWIT;
    }
    cout << cMAG  "-------- POINTER Chop Scope - POST EXIT -------- \n" << cWIT;
}

int main()
{
    printf("Hello Animal Farm - BEGIN\n");
    
    // testKittens();
    
    //testObjTransfer(0);
    
    testMoveCopyUniquePointers(5);
    
    printf("Hello Animal Farm - END\n");
    
    return 0;
}
