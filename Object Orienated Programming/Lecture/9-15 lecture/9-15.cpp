#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <fstream>
using namespace std;

class Person   // in a struct everything is public defualtly, the oppisite is true for a class.
{
public:
	Person(const string&, theName, int theAge) :name (theName) {  //for non-primitives you need to use the initilization list for primitives it doesn't matter
		//name = theName;
		age = theAge;
	}

	void setName(const string& theName) {name = theName;}
	string getName() const { return name;}
	int getAge() const {return age;}
private:
	string name;
	int age;
};

void displayPerson(const Person& aPerson)
{
	cout << "Name: " << aPerson.getName() << ", age: " << aPerson.getAge(); << ".\n";
}


int main()
{
	Person john("John", 17);
	//Person mary;
	Person mary("Mary", 22);
}