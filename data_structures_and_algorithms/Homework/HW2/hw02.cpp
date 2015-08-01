//Aidan Collins

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;

class trainStopData{
public:
	trainStopData(string& id, string& name, double lat, double lon) 
				: stop_id(id), stop_name(name), stop_lat(lat), stop_lon(lon){}

	string get_id() const {return stop_id;}
	string get_stop_name() const {return stop_name;}
	double get_latitude() const {return stop_lat;}
	double get_longitude() const {return stop_lon;}

private:
	string stop_id, stop_name;
	double stop_lat, stop_lon;

};

int main(){
	vector<trainStopData> v;
	ifstream myfile("MTA_train_stop_data.txt");
	string line;
	getline(myfile,line);
	while(getline(myfile,line)){
		string id,name;
		double lat,lon;

		int posa = line.find_first_of(',');
		id = line.substr(0,posa);

		int posb = line.find_first_of(',',posa+2);
		name = line.substr(posa+2, posb-posa-2);

		posa = line.find_first_of(',' ,posb+2);
		lat = stod((line.substr(posb+2,posa-posb-2)));
		
		posb = line.find_first_of(',', posa);
		posa = line.find_first_of(',', posb+1);
		lon = stod(line.substr(posb+1, posa-posb-1));
		
		v.push_back(trainStopData(id,name,lat,lon));	
	}
		
		//cout << id << endl << name << endl << lat << endl << lon << endl;
}