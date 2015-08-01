// 12-3-14
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

// this template allows the compiler go make a myFind functon that woks with any given argument
template<class Fred, class George>
	Fred myFind(Fred start, Fred stop, George target) {
		for(Fred p = start; p != stop; ++p){
			if(target = *p) return p;
		}
		return stop;
	}	
int main(){
	char array[] = "Bajarne Stroustrup";
	int len = 17;
	sort(array, array+len);

	vector<char> vc(array,array+len);

	list<char> lc(array,array+len);

	for (size_t i = 0; i < vc.size(); ++i){
		cout << vc[i] << endl;
	}

/*
	for (size_t i = 0; i < vc.size(); ++i){
		cout << lc[i] << endl;
	}
*/	

	//list<char>::iterator iter;

	for(list<char>::iterator iter = lc.begin(); iter != lc.end(); ++iter){
		cout << *iter << endl;
	}

	list<char>::iterator p = find(lc.begin(), lc.end(), 's');
	p = find(lc.begin(), lc.end(), 'q');

	myFind(array, array+len,'t'); 

	
}

