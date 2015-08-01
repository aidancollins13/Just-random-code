#include<String>
#include<map>
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
int main(){
	ifstream ifs;
	ifs.open("Letter_point_value.txt");
	if(!ifs) cout <<"error\n";
	int num;
	char l;
	string line;
	vector<int> v;
        while(ifs >> line)
	    cout << line;
	for(int j = 0; j < v.size(); j++)
	    cout << v[j] << endl;
}
