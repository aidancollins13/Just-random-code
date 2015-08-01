#include "Registrar.h"
#include "Student.h"
#include "Course.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

namespace BrooklynPoly {
	
	
		
		bool Registrar::addCourse(const string& cName) {
	
			for(Course*& c : courses){
				if(c->getName() == cName)
					return false;
			}
			Course* temp = new Course(cName);
			courses.push_back(temp);
			return true;

		}

		bool Registrar::addStudent(const string& sName) {
			for(Student*& s : students){
				if(s->getName() == sName)
					return false;
			}
			Student* temp = new Student(sName);
			students.push_back(temp);
			return true;
		}

		void Registrar::cancelCourse(const string& sName){
			for(size_t i = 0; i < courses.size(); ++ i){
				
				if(courses[i]->getName() == sName){
					delete courses[i];
					courses[i] = courses[courses.size()];
					courses.pop_back();
					for (Student*& s: students){
						s->dropCourse(courses[i]);
					}
				}
			}
		}

		void Registrar::enrollStudentInCourse(const string& sName, const string& cName){
			Course* pc;
			Student* ps;
			for(Student*& s : students){
				if(s->getName() == sName)
					ps = s;
			}
			for(Course*& c : courses){
				if(c->getName() == cName)
					pc = c;
			}
			ps->addCourse(pc);
			pc->addStudent(ps);

		}

		 
}