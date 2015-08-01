#include <string>
#include <iostream>
#include <vector>
#ifndef NOBLE_H
#define NOBLE_H	
namespace WarriorCraft{
	class Warrior;

	class Noble{
	public:
		Noble (std::string name);
		void hire(Warrior& warrior);
		void fire(Warrior& warrior);
		void battle(Noble& n);
		void remove(Warrior& warrior);
		std::string  getName() const;
		std::vector<Warrior*>  getWarriors() const;
	private:
		std::string name;
		std::vector<Warrior*> warriors;
	};

	std::ostream& operator<<(std::ostream& os, const Noble& n);
}

#endif