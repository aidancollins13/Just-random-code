#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>

namespace BrooklynPoly{
	class Course;

	class Student{
	public:
		Student(const std::string& name);
		bool addCourse(const Course* c);
		void dropCourse(const Course* c);
		std::string  getName() const;
	private:
		std::string name;
		std::vector<Course*> courses;
	};
}

#endif 