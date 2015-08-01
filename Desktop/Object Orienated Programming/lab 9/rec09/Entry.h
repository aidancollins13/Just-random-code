#include <iostream>
#include <string>
class Position;

class Entry{
public:
	Entry(const std::string& aName, unsigned aRoom, unsigned aPhone,
		  Position& aPosition); 

	friend std::ostream& operator<<( std::ostream& os, const Entry& e );

	std::string getName() const;
	
	unsigned getPhone() const;
private:
    std::string name;
    unsigned room;
    unsigned phone;
    Position* pos;

};
