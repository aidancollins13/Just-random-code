
#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
namespace BrooklynPoly{
	class Student;

	class Course{
	public:
		Course(const std::string& name);
		bool addStudent(Student*& s);
		void dropStudents();
		std::string getName() const;

	private:
		std::string name;
		std::vector<Student*> students;

	};
}

#endif