// Aidan Collins 
// ac5152
//Read fiile and print lines then count the words in the file

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(){
	ifstream ifs;
	ifs.open("imput.txt");

	if(!ifs)
	{
		exit(1);
	}

	string line;
	while(getline(ifs, line))
	{
		cout << line << "\n";
	}
	ifs.close();
	ifs.open("imput.txt");
	int count = 0;
	string word;
	while(ifs >> word)
	{
		count++;
	}

	cout << count << "\n";

}
