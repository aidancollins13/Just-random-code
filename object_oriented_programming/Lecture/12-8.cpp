#include <exception>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>
using namespace std;
	class Cat{}:

	void foo(int x){
		assert(x <= 120);// returns an error. only used for testing.  if you put #NDEBUG all asserts will dissapear form compiled code
		if(x > 120){
		cerr << "Some effor message\n";
		throw exception();
	}
	}
int mian(){
	try{

		//this will try the code in it and gives code a chance to work without this

		vector<int> v;
		v.at(17) = 42;
	}
	catch(out_of_range& ex) {cerr 
							<< "Cought an out of range exception\n";}
	catch(exception& ex) {cerr << "Caught an exception: " 
							<< ex.what() << enxl;}

	cerr << "Leaving main\n ";

	try{
		foo(200);
	}

	catch(exception& ex) {cerr ex.what() << endl;}
	catch(...) {cerr << "We got an exception but we don't know what\n";}


}