/******************************************************************************

Little own practice writing Rule of 5 example 
VERY silly and artificial ...

... with a dash of color ...  
https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal

*******************************************************************************/
#include <stdio.h>
#include <iostream>

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
    static int index;
    int* pDataID;
    int* pAge;
    int legs;
public:
    animal() : legs(0) { 
        //cout << "\033[1;31mbold red text\033[0m\n";
        cout << cGRN << "CONstructed default animal\n" << cWIT; 
        pDataID = new int(index); 
        index++;
        pAge = new int(0);
    }
        
    animal(int aLegs, int aAge) : legs(aLegs) { 
        cout << cGRN << "CONstructed default animal with legs\n" << cWIT; 
        pDataID = new int(index); 
        index++;
        pAge = new int(aAge);        
    }  
    
    ~animal() { 
        cout << cRED << "DEstructing default animal (index "<< *this->pDataID << ")...\n" << cWIT;
        
        if (this->pAge != nullptr){
            cout << "Delete pAge\n";
            delete this->pAge;
        } else {
            cout << "DO NOT Delete pAge\n";
        }
        
        if (this->pDataID != nullptr){
            cout << "Delete pDataID\n";
            delete this->pDataID;
        } else {
            cout << "DO NOT Delete pDataID\n";
        }
    }
    
    void printAnimalIndex(){ 
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
        cout << cGRN << "COPY constructed animal\n" << cWIT;     
        this->pDataID = new int(index); index++;
        this->legs = source.legs;
        int temp = *source.pAge;
        this->pAge = new int(temp);
    } 
    
    // MOVE constructor 
    animal(animal &&source){
        cout << "MOVE constructed animal\n" << cWIT;     
        this->pDataID = new int(index); index++;
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

int main()
{
    printf("Hello Animal Farm\n");

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
    
    return 0;
}
