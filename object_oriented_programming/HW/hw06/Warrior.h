#include <string>
#ifndef WARRIOR_H
#define WARRIOR_H
namespace WarriorCraft{
	class Noble;

	class Warrior{
	public:
		Warrior(const std::string& name, int strength);
		std::string getName() const;
		int getStrength() const;
		void setStrength(int s);
		void setNoble(Noble* n);
		void runaway();
	private:
		std::string name;
		int strength;
		Noble* noble;
	};

}
#endif