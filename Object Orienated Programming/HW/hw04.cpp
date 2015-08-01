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
	void setEmployed(bool b){ employed = b;}
	bool getEmployed() const {return employed;}
	void display() const
	{
		cout << name << ": " << strength << endl;
	}
private:
	string name;
	int strength;
	bool employed = false;
	


};

class Noble
{
public:
	Noble (string name) : name(name) {}
	void hire(Warrior& warrior)
	{
		warriors.push_back(&warrior);
		warrior.setEmployed(true);
	}
	void fire(Warrior& warrior)
	{
		for(size_t i= 0; i < warriors.size(); ++i)
		{
			if(warriors[i] == &warrior)
			{
				warriors[i] = warriors[warriors.size()-1];
				warriors.pop_back();
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
	string getName() const {return name;}
private:
	vector<Warrior*> warriors;
	string name;
};



	int main() {
	ifstream ifs("nobleWarriors.txt");	// reads in file
	if(!ifs) {cout << "file not read\n"; exit(1); } 

	string word;
	vector<Noble*> nobles;
	vector<Warrior*> warriors;
	while(ifs >> word)
	{
		if(word == "Noble")
		{
			string nobleName;
			ifs >> nobleName;
			nobles.push_back(new Noble(nobleName));
		}
		if(word == "Warrior")
		{	
			string warriorName;
			int strength;
			ifs >> warriorName >> strength;
			warriors.push_back(new Warrior(warriorName, strength));

		}
		if(word == "Hire")
		{
			string n,w;
			ifs >> n >> w;
			size_t nobleIndex, warriorIndex;
			for( nobleIndex = 0 ; nobleIndex < nobles.size(); ++nobleIndex)
			{
				if(nobles[nobleIndex]->getName() == n)
					break;
			}
			for( warriorIndex = 0; warriorIndex < warriors.size() ; ++warriorIndex)
			{
				if(warriors[warriorIndex]->getName() == w)
					break;
			}
			nobles[nobleIndex]->hire(*warriors[warriorIndex]);
		}

		if(word == "Fire")
		{
			string n,w;
			ifs >> n >> w;
			size_t nobleIndex, warriorIndex;
			for( nobleIndex = 0 ; nobleIndex < nobles.size(); ++nobleIndex)
			{
				if(nobles[nobleIndex]->getName() == n)
					break;
			}
			for( warriorIndex = 0; warriorIndex < warriors.size() ; ++warriorIndex)
			{
				if(warriors[warriorIndex]->getName() == w)
					break;
			}
			nobles[nobleIndex]->fire(*warriors[warriorIndex]);
		}

		if(word == "Status")
		{
			cout << "Status\n====\nNobles:\n";
			for(Noble* n : nobles)
			{
				n->display();
			}
			cout << "Unemployed Warriors:\n";
			for(Warrior* w : warriors)
			{
			 	if(!w->getEmployed())
			 		w->display();
			}
		}

		if (word == "Battle")
		{
			string noble1Name, noble2Name;
			size_t noble1Index, noble2Index;
			ifs >> noble1Name >> noble2Name;
			for(noble1Index = 0; noble1Index < nobles.size(); ++noble1Index)
			{
				if(nobles[noble1Index]->getName() == noble1Name)
					break;
			}
			for(noble2Index = 0; noble2Index < nobles.size(); ++noble2Index)
			{
				if(nobles[noble2Index]->getName() == noble2Name)
					break;
			}
			nobles[noble1Index]->battle(*nobles[noble2Index]);

		}

		if (word == "Clear")
		{
			for(size_t i = 0; i < nobles.size() ; ++i)
			{
				nobles[i] = NULL;
			}
			for(size_t i = 0; i < warriors.size(); ++i)
			{
				warriors[i] = NULL;
			}
			warriors.clear();
			nobles.clear();
		}
}
}


