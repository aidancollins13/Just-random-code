#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <fstream>
using namespace std;

struct Warrior  // creates a worrior struct
{
	string name;
	int strength;
	

};

Warrior makeWarrior(ifstream& ifs);
void printStatus(const vector<Warrior>& warriors);
void battle(string& name1, string& name2,  vector<Warrior>& warriors);

int main()
{
	ifstream ifs("warriors.txt");	// reads in file
	if(!ifs) {cout << "file not read\n"; exit(1); } 

	string command, name1, name2;
	vector<Warrior> warriors;
	while(ifs >> command)  // reads the first wird of every line then decides what to do based on what word it is
		if (command == "Warrior"){
			
			warriors.push_back(makeWarrior(ifs));  // adds the new warrior to the vector of warriors
		}
		else if (command == "Status"){
			printStatus(warriors); // calls the print status function
		}

		else if (command == "Battle")
		{
			ifs >> name1 >> name2;   //reads the names of the warriors battleing
			battle(name1,name2, warriors); //calls the battle function
		}

	}


Warrior makeWarrior(ifstream& ifs){  // makes a warrior and returns it 
	
	Warrior temp;
	string name;
	int strength;
	ifs >> name >> strength;

	temp.name = name;
	temp.strength = strength;
	

	return temp;

}

void printStatus(const vector<Warrior>& warriors){ // prints out all of the warrior's name and strength in the vector 
		cout << "There are " << warriors.size() << " swarriors." << endl;
		for (const Warrior& currnetWarrior : warriors)
		{
			cout << "Warrior: " << currnetWarrior.name << ", strength: " << currnetWarrior.strength << endl;
		}
}

void battle(string& name1, string& name2, vector<Warrior>& warriors)
{
	size_t index1, index2;
	for(size_t i = 0; i < warriors.size(); ++i)  // this loop searches for the warriors by nname then saves the index of the
	{
		if(warriors[i].name == name1){
			index1 = i;
		}
		if(warriors[i].name == name2){
			index2 = i;
		}

	}

	cout << name1 << " battles " << name2 << ".\n";

	if(warriors[index1].strength <= 0 && warriors[index2].strength <= 0){
		cout << "Dead men cannot fight." << endl;
	}

	else if(warriors[index1].strength <= 0){ // checks to see if the 1st warrior is alive
		cout << "A dead man cannot challenge someone." << endl;
	}
	else if(warriors[index2].strength <= 0){ // checks to see if the 2nd warrior is alive
		cout << "You cannot start a fight with someone  who is dead." << endl;
	}

	else
	{
		int temp;
		temp = warriors[index1].strength;	
		warriors[index1].strength -= warriors[index2].strength;    ///changes their strength then prints who has won
		warriors[index2].strength -= temp;

		if(warriors[index1].strength < 0){warriors[index1].strength = 0;}// makes sure there are no negative strengths 
		if(warriors[index2].strength < 0){warriors[index2].strength = 0;}

		if(warriors[index2].strength == 0) 					//displays the winner or that it was a draw 
		{
			cout << name1 << " has won! Defeating " << name2 << endl;
		
		}
		else if(warriors[index1].strength == 0)
		{
			cout << name2 << " has won! Defeating " << name1 << endl;
			
		}

		else 
		{
			cout << "They die by eachother's hand.\n";
		}


	}

}