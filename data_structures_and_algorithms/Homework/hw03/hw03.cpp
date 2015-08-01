//Aidan Collins

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <stdlib.h>
#include <math.h>
#include <functional>
using namespace std;
//Question 1
template <class Object>
class Vector
{
public:
    explicit Vector( int initSize = 0 )
    : theSize( initSize ), theCapacity( initSize + SPARE_CAPACITY )
    { objects = new Object[ theCapacity ]; }
    
    ~Vector( )
    { delete [ ] objects; }

    bool empty( ) const
    { return size( ) == 0; }
    
    int size( ) const
    { return theSize; }
    
    int capacity( ) const
    { return theCapacity; }
    
    Object & operator[]( int index )
    { return objects[ index ]; }
    
    // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;
    
    iterator begin( )
    { return &objects[ 0 ]; }
    const_iterator begin( ) const
    { return &objects[ 0 ]; }
    
    iterator end( )
    { return &objects[ size( ) ]; }
    const_iterator end( ) const
    { return &objects[ size( ) ]; }
    
    
    const Object & operator[]( int index ) const
    { return objects[ index ]; }
    
    void reserve( int newCapacity );
    
    void push_back( const Object & x );

    Vector & operator=(const Vector & rhs );
    
    static const int SPARE_CAPACITY = 16;

    
	Vector<Object>::iterator erase( Vector<Object>::iterator vItr){
		vItr = ++vItr;
		for(Vector<Object>::iterator i = vItr; i++ !=this->end; i++){
			i = ++i;
		}
		this->pop_back();
		theSize--;
		return vItr;
	} 
    
private:
    int theSize;
    int theCapacity;
    Object * objects;
};



template <class Object>
void Vector<Object>::push_back( const Object & x )
{
    if( theSize == theCapacity )
        reserve( 2 * theCapacity + 1 );
    objects[ theSize++ ] = x;
}


template <class Object>
void Vector<Object>::reserve( int newCapacity )
{
    
    if ( newCapacity <= theCapacity ) return;
    // never decrease the capacity
    
    Object* p = new Object[ newCapacity];
    for( int k = 0; k < theSize; k++ )
        p[ k ] = objects[ k ];
    
    delete [ ] objects;
    objects = p;
    theCapacity = newCapacity;
}

template <class Object>
Vector<Object> & Vector<Object>::operator=( const Vector<Object> & rhs )
{
    if( this != &rhs )
    {
        delete [ ] objects;
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        
        objects = new Object[ theCapacity ];
        for( int k = 0; k < size( ); k++ )
            objects[ k ] = rhs.objects[ k ];
    }
    return *this;
}

double degrad(double d) {
   return d * M_PI / 180;
}


// Code below is adapted from http://www.movable-type.co.uk/scripts/latlong.html
// FYI: That website has an applet that computes the haversine distance. 
// It also has a link that will show the locations on a map,
// with a line between them.
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


//Question 2
template<class Object>
bool hasDuplicate(Vector<Object> v){
	set<Object> s;
	for(int i = 0; i < v.size(); i++){
		s.insert(v[i]);
	}
	return(v.size() == s.size());
}

template<class iterator, class pred, class op>
int preform_if(iterator itrStart, iterator itrEnd, pred p, op o){
	int count = 0;
	for(iterator itr = itrStart; itr!= itrEnd; ++itr){
		if(pred(*itr)) {
			count++;
		}
	}
	return count;
}

class isStopOnRoute{
public:
	isStopOnRoute(char route) : route(route){}
	bool operator()(trainStopData t){
	return (t.get_id()[0] == route);
			
	}
private:
	char route;
};

class isSubwayStop{
public:
	isSubwayStop(const string& stopId) : stopId(stopId){}
	bool operator()(trainStopData t){
		return (t.get_id() == stopId);
	}
private:
	string stopId;
};

class isSubwayStopNearX{
public:
	isSubwayStopNearX(double lat, double lon, double d) : latitude(lat), longitude(lon), d(d){}
	bool operator()(trainStopData t){
		return (d <= haverdist(latitude, longitude, t.get_latitude(), t.get_longitude()));
	}
private:
	double latitude, longitude, d;
};

class printTrianStopInfo{
public:
	void operator()(trainStopData t){
		cout << "Station id: " << t.get_id() << endl;
		cout << "Station name: " << t.get_stop_name() << endl;
		cout << "Station latitude and longitude : " << t.get_latitude() << ", " << t.get_longitude() <<endl;
	}
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

	int command = 0;
while (command != 4){
	cout << "Please enter a command.\n Enter '1' to print out all information about all stops on a specific route.\n Enter '2' to print out information about a specific train stop.\n Enter '3' to print out all train stops within a certain distance.\n Enter '4' to quit. \n\n";
	cin >> command;

	if (command == 1){
		char route;
		bool routeExists = false;
		cout << "Please enter a trian route.(case sensitive)\n";
		cin >> route;
		isStopOnRoute r(route);
		printTrianStopInfo print;
		for(int i = 0; i < v.size(); ++i){
			if (r(v[i])) {
				print(v[i]);
				cout << "===========================\n"; 
				routeExists = true;
			}
		}
		if(!routeExists) cout << "There are no stops on that route.\n";
	}

	if (command == 2){
		string id;
		bool stopExists = false;
		cout << "Please enter a train stop by its ID.(case snsitive)\n";
		cin >> id;
		isSubwayStop s(id);
		printTrianStopInfo print;
		for(int i = 0; i < v.size(); ++i){
			if(s(v[i])){
				print(v[i]);
				stopExists = true;
			}
		}
		if(!stopExists) cout << "There is no stop with that ID.\n =======================================\n";
 	}

	if (command == 3){
		double lat, lon, d;
		bool areStops = false;
		cout << "Please enter the latitude then longitude then the the distance from that point you want to check for stops in.\n";
		cin >> lat;
		cin >> lon;
		cin >> d;
		isSubwayStopNearX s(lat,lon,d);
		printTrianStopInfo print;
		for(int i = 0 ; i < v.size() ; ++i){
			if(s(v[i])){
				print(v[i]);
				cout << "===================================\n";
				areStops = true;
			}
		}
		if(!areStops) cout << "There are no stops withing that distance of that point.\n";
	}

}
}
