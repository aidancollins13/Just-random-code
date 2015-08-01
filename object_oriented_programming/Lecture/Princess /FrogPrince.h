#ifndef FROGPRINCE_H
#define FROGPRINCE_H

#include <string>

class Princess;

class FrogPrince{
public:
	FrogPrince(const std::string& name) : name(name), spouce(NULL){};
	void display() const;
	std::string getName() cosnt {return name;}
private:
	std::string name;
	Princess* spouce;

};

#endif