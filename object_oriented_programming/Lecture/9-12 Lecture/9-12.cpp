//Aidan Collins
//9-12-14
//Lab 2

#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <fstream>
using namespace std;

struct HC 
{
	int numC, numH;
	vector<string> name;
};

void readAndProcessfile(ifstream& ifs, vector<HC>& molicules);
size_t searchHC(vector<HC>& molicules, int numC, int numH);

void displayMolicules(vector<HC>& molicules);

int findMax(vector<HC>& molicules);
int main()
{
	vector<HC> molicules;
	ifstream ifs("hydrocarbons.txt") ;
	if(!ifs)
	{
		cout << "could not read file"<< endl;
		exit(1);
	}
	readAndProcessfile(ifs, molicules);
	
;	displayMolicules(molicules);


}

void readAndProcessfile(ifstream& ifs, vector<HC>& molicules)
{
	string name;
	int numC, numH;
	char junk;

	while(ifs >> name >> junk >> numC >> junk >> numH)
	{
		size_t index = searchHC(molicules,numC,numH);
		
		if(index = molicules.size())
		{
			HC hydrocarbon;
			hydrocarbon.numC = numC;
			hydrocarbon.numH =numH;
			hydrocarbon.name.push_back(name);

			molicules.push_back(hydrocarbon);
		}

		else
		{
			molicules[index].name.push_back(name);
		}
	}
}

size_t searchHC(vector<HC>& molicules, int numC , int numH)
{
	
	for(size_t i = 0; i < molicules.size() ; ++i)
	{
		if((molicules[i].numC = numC) && (molicules[i].numH = numH))
			return i;
	}
	return molicules.size();

}

int findMax(vector<HC>& molicules)
{
	int max = 1;
	for(HC& x : molicules)
	{
		if(x.numC > max)
			max = x.numC;
	}
	return max;
}

void displayMolicules(vector<HC>& molicules)
{
	int max = findMax(molicules); 

	for (int i = 0 ; i< max; ++i)
	{
		for(HC x : molicules)
		{
			if(x.numC = i)
			{
				cout << "C " << x.numC << "H " << x.numH << endl;
				for(string& s : x.name)
				{
					cout << s << ", ";
				}
				cout << "/n/n/n";

			}
		}
	}

}