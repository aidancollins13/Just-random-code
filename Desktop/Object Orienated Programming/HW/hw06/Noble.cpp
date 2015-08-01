#include "Noble.h"
#include "Warrior.h"
using namespace std;
namespace WarriorCraft{

	Noble::Noble (string name) : name(name) {}
	void Noble::hire(Warrior& warrior)
	{
		warriors.push_back(&warrior);
		warrior.setNoble(this);
	}

	void Noble::fire(Warrior& warrior)
	{
		for(size_t i= 0; i < warriors.size(); ++i)
		{
			if(warriors[i] == &warrior)
			{
				warriors[i] = warriors[warriors.size()-1];
				warriors.pop_back();
				cout << warriors[i]->getName() << ", you're fired! --" << name << endl;
			}
		}
	}

	void Noble::remove(Warrior& warrior){
		for(size_t i= 0; i < warriors.size(); ++i)
		{
			if(warriors[i] == &warrior)
			{
				warriors[i] = warriors[warriors.size()-1];
				warriors.pop_back();
			}
		}
	}

	void Noble::battle(Noble& n)
	{
		cout << name << " battles " << n.name << endl;
		int s1 = 0;
		int s2 = 0;
		for(Warrior* w : warriors)
		{
			s1 += w->getStrength();
		}


		for(Warrior* w : n.warriors)
		{
			s2 += w->getStrength();
		}

		if(s1 == 0 && s2 == 0)
		{
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if(s2 == 0)
		{
			cout << "He's dead " << name << endl;
		}
		else if(s1 == 0)
		{
			cout << "You can't challenge someone to battle when you are dead." << endl;
		}
		else if( s1 > s2)
		{
			cout << name << " defeats " << n.name << endl;
			for(size_t i = 0; i < n.warriors.size(); ++i)
			{
				n.warriors[i]->setStrength(0);
			}

			for(size_t i = 0; i < warriors.size(); ++i)
			{
				warriors[i]->setStrength(s1-s2);
			}

		}
		else
		{
			cout << n.name << " defeats " << name << endl;
			for(size_t i = 0; i < warriors.size(); ++i)
			{
				warriors[i]->setStrength(0);
			}
			
				for(size_t i = 0; i < n.warriors.size(); ++i)
			{
				n.warriors[i]->setStrength(s2-s1);
			}

		}


	}

	string Noble::getName() const {return name;}
	vector<Warrior*> Noble::getWarriors() const {return warriors;}


ostream& operator<<(ostream& os, const Noble& n){
	os << n.getName() << " has an army of " << n.getWarriors().size() << endl;
	for(Warrior* w : n.getWarriors()){
		os <<"\t";
		os << w->getName() << ": " << w->getStrength() << endl;
	}
	return os;
}

}