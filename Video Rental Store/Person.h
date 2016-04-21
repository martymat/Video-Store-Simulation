//Person.h

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

using namespace std;

class Person {
private:
	string phoneNum;
	string name;
public:
	//General constructor
	Person() { name = " "; phoneNum = " "; }

	//Constructor initializer
	Person(string thePhoneNumber, string theName) :
		phoneNum(thePhoneNumber), name(theName) {}

	//Returns name
	string getName() { return name; }

	//Sets person's name
	void setName(string inName) { name = inName; }

	//Returns person's phone number
	string getPhoneNum() { return phoneNum; }

	//Sets person's phone number
	void setPhoneNum(string inPhoneNum) { phoneNum = inPhoneNum; }

	// Prints out person's info *virtual function*
	virtual void printInfo() {
		cout << "\t" << name << " " << phoneNum << endl;
	}
};

#endif PERSON_H