
#ifndef REGISTRAR_H
#define REGISTRAR_H
#include <string>
#include <vector>

namespace BrooklynPoly{
	class Student;
	class Course;
	class Registrar{
	public:
		bool addCourse(const std::string& cName);
		bool addStudent(const std::string& sName);
		void cancelCourse(const std::string& cName);
		void enrollStudentInCourse(const std::string& sName, const std::string& cName);

	private:
		std::vector<Student*> students;
		std::vector<Course*> courses;
	};
}
#endif