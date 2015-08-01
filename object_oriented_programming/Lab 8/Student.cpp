#include "Student.h"
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly{
	Student::Student(const string& name) :name(name){}
	void Student::dropCourse(const Course*& c)
	{
		for(size_t i = 0; i < courses.size(); ++i){
			if(courses[i] == c)
			{
				courses[i] = courses[courses.size()];
				courses.pop_back();
			}
		}
	}
	bool Student::addCourse(const Course*& c)
	{
		for(Course* count : courses)
		{
			if(count == c)
				return false;
		}
		courses.push_back(c);
		return true;
	}
}