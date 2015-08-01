#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <fstream>
using namespace std;

class Sandwich 
{
public:

	Sandwich(int tom = 2, int chs = 1, double must = .05, double may = 1) :bread (2), cheese (chs), tomato (tom), mustard (must), mayo (may)
	{
	}

	int getBread() const { return bread;}
	int getCheese() const {return cheese;}
	int getTomato() const {return tomato;}
	double getMustard() const {return mustard;}
	double getMayo() const {return mayo;}


	void setCheese(int c){cheese = c;}
	void setTomato(int t){tomato = t;}
	void setMustard(double mu){mustard = mu;}
	void setMayo(double ma){mayo = ma;}
	
	void display() const
	{
		cout << "Bread: " << bread << ", Cheese: " << cheese << ", Tomato: " << tomato
		<< ", mustard: " << mustard << ", Mayo: "  << mayo << endl;
	}	

private:
	const int bread;
	int cheese;
	int tomato;
	double mustard;
	double mayo;
};


class SandwichTruck
{
public:
	void checkBeforeLeaving() const
	{
		for(const Sandwich& currentSandwich : sandwiches)
		{
			currentSandwich.display();
		}
	}

	void insertSandwich(const Sandwich& s) 
	{
		sandwiches.push_back(s);
	}
private:
	vector<Sandwich> sandwiches;
};


int main()
{
	SandwichTruck truck1;

	Sandwich  customer1;
	truck1.insertSandwich(customer1);
	Sandwich customer2;
	customer2.setMustard(0);
	truck1.insertSandwich(customer2);
	
	Sandwich customer3(2,2);
	truck1.insertSandwich(customer3);
	Sandwich customer4;
	truck1.insertSandwich(customer4);

	truck1.checkBeforeLeaving();

	cout << "Customer 4's mustard is: " << customer4.getMustard() << endl;

}