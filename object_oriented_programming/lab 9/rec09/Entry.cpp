#include "Entry.h"
using namespace std;

Entry::Entry(const string& aName, unsigned aRoom, unsigned aPhone,
	  Position& aPosition) 
	: name(aName), room(aRoom), phone(aPhone), pos(&aPosition) {
    }

friend ostream& Entry::operator<<( ostream& os, const Entry& e ) {
        os << e.name << ' ' << e.room << ' ' << e.phone;
        return os;
    }

string Entry::getName() const {return name;}
unsigned Entry::getPhone() const {return phone;}