//Aidan Collins
// 3/11/15
//Homework 4
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <stdlib.h>
#include <math.h>
#include <functional>
#include <limits>

using namespace std;
//Question 1
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

double degrad(double d) {
   return d * M_PI / 180;
}

double haverdist(double lat1, double longit1, double lat2, double longit2)
{
     double r = 6371;
     double dlat = degrad(lat2 - lat1);
     double dlongit = degrad(longit2 - longit1);
     double a = sin(dlat/2)*sin(dlat/2)+
        cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit/2)*sin(dlongit/2);
     double c = 2*atan2(sqrt(a),sqrt(1-a));
     return r*c;
}

template <class Compareable, class Iterator>
Iterator select_item(Iterator start, Iterator end, Compareable pred){
	Iterator tmp_itr = end;
	for( ; start != end; start++){
		if(pred(*start)) tmp_itr = start;
	}
	return tmp_itr;
}

class closest_stop
{
public:
	closest_stop(double lon, double lat) : longitude(lon), latitude(lat), shortest_dist(numeric_limits<double>::max()) {}
	bool operator()(const trainStopData& t) {

		double dist = haverdist(latitude, longitude, t.get_latitude(), t.get_longitude());
		if(dist < shortest_dist){
			shortest_dist = dist;
		}
	}
private:
	double longitude, latitude, shortest_dist;
};

//Question 2
template<class Object>
Object summation(Object x,int n){
	if(n == 0) return x;
	Object tmp = Object();
	summation(tmp + (x+1), n-1);
}

//Question 3
void recur(int n){
	if(n>0){
		recur(n-1);
		cout << n;
		recur(n-1);
	}	
}
void myRecFunc(int n)
{
cout << n << ": ";
if (n < 1) return;
myRecFunc(n/2);
myRecFunc(n/2);
for (int i = 1; i < n; ++i)
cout << "*";
cout << endl;
}
//Question 4
template<class Object>
Object sumVectorRecur(typename vector<Object>::const_iterator left,typename vector<Object>::const_iterator right){
	if(left == right -1) return *left;
	typename vector<Object>::const_iterator mid = left + (right - left)/2;
	return sumVectorRecur<Object>(left, mid) + sumVectorRecur<Object>(mid, right);
}
template<class Object>
Object sumVector(const vector<Object> & a){
	typename vector<Object>::const_iterator begin = a.begin();
	typename vector<Object>::const_iterator end = a.end();
	typename vector<Object>::const_iterator mid = a.begin() + (end-begin)/2;
	if(begin == end-1) return *begin;
	return sumVectorRecur<Object>(begin,mid) + sumVectorRecur<Object>(mid,end);
}

//Question 5
void permute(string & str, int low, int high){
	if(low == high) cout << str << endl;
	else{
		for(int i = low; i < high; ++i){
			swap(str[low],str[i]);
			permute(str,low+1,high);
			swap(str[low], str[i]);
		}
	}
	
}
void permute(const string & str){
		string temp = str;
	 permute(temp, 0,str.length());
	
}

//Question 6
template <class RandItr>
void mergeSort(RandItr start, RandItr end){
	int sz = end-start;
	typedef typename iterator_traits<RandItr>::value_type Object;

	vector<Object> tmp(sz);

	mergeSort(tmp.begin(),start,end);
}

template<class RandItr>
void mergeSort(RandItr begin, RandItr start, RandItr end){
	if(start != end){
		RandItr mid = start + (end - start)/2;
		mergeSort(begin, start, mid);
		mergeSort(begin, mid, end);
		merge(start,mid,mid,end,begin);
	}
}

//Questoin 7
class meFirst{
public:
	meFirst(const string& s) : me(s){}
	bool operator()(const Student& s1, const Student& s2){
		if(s2.get_name() == me) return false;
		if(s1.get_name() == me) return true;
		return(s1.get_name() < s2.get_name())
	}
private:
	string me;
};

int main(){
//Question 1
// vector<trainStopData> v;
// int command = 0;
// while (command != 5){
// 	cout << "Please enter a command.\n Enter '1' to print out all information about all stops on a specific route.\n Enter '2' to print out information about a specific train stop.\n Enter '3' to print out all train stops within a certain distance.\n Enter '4' to find the stop within a shortest distance.\n Enter '5' to quit. \n\n";
// 	cin >> command;

// 	if(command = 4)	{
// 		vector<trainStopData>::iterator start,end,iter;
// 		double lat, lon;
// 		cout << "Enter a latatitude\n";
// 		cin >> lat;
// 		cout << "Enter a longitude\n";
// 		cin >> lon;
// 		iter = select_item(v.begin(), v.end(), closest_stop(lat,lon));
// 		if(iter!=v.end()) cout << "The closest stop is " << iter->get_stop_name() << ".\n";

// 	}
// 	}

//Question 3
recur(5);
cout << endl;

//Question 4
vector<int> a (1);
 a[0] = -9;
// a[1] = 12;
// a[2] = 8;
cout << sumVector(a) << endl;

string str = "abc";
permute(str);
cout << endl;
myRecFunc(4);
cout << endl;
}