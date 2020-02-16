/******************************************************************************

Author: Deb Haldar 
Date:   15 May 2016
File:   smart pointers 10 mistakes 
Goal:   Little sandbox on Smart Pointers 
Keys:   Smart Pointers 
From:   https://www.acodersjourney.com/top-10-dumb-mistakes-avoid-c-11-smart-pointers/

NOTE:   I'm an aviation nut. Could not reset this class! Thanks Deb!! 

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>

using namespace std;

class Aircraft
{
private:
	string m_model;

public:

	int m_flyCount;

	weak_ptr<Aircraft> myWingMan;

	void Fly()
	{
		cout << "Aircraft type" << m_model << "is flying !" << endl;
	}

	Aircraft(string model)
	{
		m_model = model;
		cout << "Aircraft type " << model << " is created" << endl;
	}

	Aircraft()
	{
		m_model = "Generic Model";
		cout << "Generic Model Aircraft created." << endl;
	}

	~Aircraft()
	{
		cout << "Aircraft type  " << m_model << " is destroyed" << endl;
	}

};

int main()
{
	shared_ptr<Aircraft> pMaverick = make_shared<Aircraft>("F-22");
	shared_ptr<Aircraft> pIceman = make_shared<Aircraft>("F-14");

	pMaverick->myWingMan = pIceman;
	pIceman->m_flyCount = 17;

	pIceman.reset(); // destroy the object managed by pIceman

	cout << pMaverick->myWingMan.lock()->m_flyCount << endl; // ACCESS VIOLATION

	return 0;
}