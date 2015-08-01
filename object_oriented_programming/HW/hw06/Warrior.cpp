#include "Warrior.h"
#include "Noble.h"
using namespace std;
namespace WarriorCraft{

	Warrior::Warrior (const string& name, int strength) : name(name), strength(strength){}

	string Warrior::getName() const {return name;}

	int Warrior::getStrength() const 
		{
			return strength;
		}
	void Warrior::setStrength(int s) {
		strength = s;
	}	
	void Warrior::setNoble(Noble* n) {noble = n;}

	void Warrior::runaway(){
		noble->remove(*this);
		cout << name << " flees in terror, abandoning his lord, " << noble->getName() << endl;

	}

}