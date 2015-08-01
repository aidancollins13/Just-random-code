#include <iostream>
#include <string>
#include <vector>
using namespace std;
//Aidan Collins
//11/7/14

class Noble{
public:
	Noble(const string& name) : name(name){}

	
	string getName() const { return name;}

	virtual void reduceStrength(int s){}

	virtual int getStrength(){}

	virtual void battle(Noble& otherNoble) {
		if(this->getStrength() == 0 && otherNoble.getStrength() == 0){
		cout << "Oh, NO!  They're both dead! Yuck!\n";
	}
	else if(this->getStrength() == 0){
		cout << "He's dead, " << name << endl;
	}

	else if(otherNoble.getStrength() == 0){
		cout << "He's dead, " << otherNoble.getName() << endl;
	}
	else{
		cout << name << " battles " << otherNoble.getName(); 
	}
	}

private:
	string name;
};


class Protector{
public:
	Protector(const string& name, int strength) : name(name) , strength(strength){}

	int getStrength() const {return strength;}

	void reduceStrength(int i) {strength -= i;}

	void setNoble(Noble* n){ noble = n;}

	string getName() {return name;}

	Noble* getNoble() {return noble;}

	virtual void display(){};

private:
	string name;
	int strength;
	Noble* noble;
};

class Wizard : public Protector{
public:
	Wizard(const string& name, int strength) : Protector(name, strength){}

	void displa1y(){
		cout << "POOF\t";
	}
};

class Warrior : public Protector{
public:
	Warrior(const string& name, int strength) : Protector(name, strength){}
	virtual void display() = 0;
};

void Warrior::display() {
	cout << this->getName() << "says: Take that in the name of my lord, " << (this->getNoble())->getName();
}

class Archer : public Warrior{
public:
	Archer(const string& name, int strength) : Warrior(name, strength){}
	void display(){
		cout << "CLANG! ";
		Warrior::display();
	}
};

class Swordsman : public Warrior{
public:
	Swordsman(const string& name, int strength) : Warrior(name, strength){}
	void display(){
		cout << "CLANG!";
		Warrior::display();
	}
};




class PersonWithStrengthToFight : public Noble{
public:
	PersonWithStrengthToFight(const string& name, int s) : strength(s), Noble(name){}

	int getStrength() const {return strength;}

	void reduceStrength(int s) {
		strength -= s;
		if(strength < 0)
			strength = 0;
	}	

	void battle(Noble& otherNoble){
		Noble::battle(otherNoble);
		int temp = strength;
		this->reduceStrength(otherNoble.getStrength());
		otherNoble.reduceStrength(temp);
	}

private:
	int strength;
	
};

class Lord : public Noble{
public:
	Lord(const string& name) : Noble(name){}

	void hires(Protector& protector){
		protectors.push_back(&protector);

		protector.setNoble(this);
	}

	void battle(Noble& otherNoble){
		Noble::battle(otherNoble);
		int temp = this->getStrength();
		this->reduceStrength(otherNoble.getStrength());
		otherNoble.reduceStrength(temp);
		for(Protector* p : protectors){
			p->display();
		}
	}

	int getStrength() const {
		int strength;
		for(Protector* p : protectors){
			strength += p->getStrength();
		}
		return strength;
	}

	void reduceStrength(int i){

		for(size_t index = 0; index < protectors.size(); ++index){
			while(i > 0){
				if(protectors[index]->getStrength() > i){
					protectors[index]->reduceStrength(i);
					i = 0;
				}
				else {
					i -= protectors[index]->getStrength();
					protectors[index]->reduceStrength(protectors[index]->getStrength());
				}
			}
		}
	}
private:
	vector<Protector*> protectors;
};


int main(){
	Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    joe.battle(randy);	
    joe.battle(sam);	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    janet.battle(barclay);	
    janet.hires(samantha);	
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);	
    sam.battle(barclay);	
    joe.battle(barclay);
}