 //Adian Collins 5 october 2014

#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <fstream>
using namespace std;

class Warrior  // defines the worrior class
{
public:
	Warrior(const string& name, int strength) : name(name), strength(strength)
	{}
	string getName() const {return name;}
	int getStrength() const 
		{
			return strength;
		}
	void print() const {
		cout << "Warrior: " << name << ", weapon: ";
		

	}

	void setStrength(int s) {
		strength = s;
	}
	void display() const
	{
		cout << name << ": " << strength << endl;
	}
private:
	string name;
	int strength;
	

};

class Noble
{
public:
	Noble (string name) : name(name) {}
	void hire(Warrior& warrior)
	{
		warriors.push_back(&warrior);
	}
	void fire(Warrior& warrior)
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
	void display() const
	{
		cout << name << " has an army of " <<  warriors.size() << endl;
		for(Warrior* w : warriors)
		{
			cout << "\t";
			w->display();
		}
	}
	void battle(Noble& n)
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

private:
	vector<Warrior*> warriors;
	string name;
};



	int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}

