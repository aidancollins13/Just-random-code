#include "Course.h"
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly{
	Course::Course(const string& name) : name(name) {}
	bool Course::addStudent( Student*& s)
	{
		for(Student*& count : students){
			if(count == s)
				return false;
		}
		students.push_back(s);
	}
	void Course::dropStudents(){
		
		students.clear();
	}
	string Course::getName() const {return name;}

}