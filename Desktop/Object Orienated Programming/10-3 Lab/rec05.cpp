#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <fstream>
using namespace std;

class TimeSlot
{
public:
	TimeSlot(const string& day, const int t) : day(day), t(t){}
	void display() const
	{
		if(t > 12)
		{
			cout << day << " " << t-12 << "PM " << endl;
		}
		else
		{
			cout << day << " " << t << "AM " << endl;
		}
	}
private:
	string day;
	int t;
};


class Student
{
public:
	Student(const string& name) : name(name), grades(13,-1)
	{

	}

	void addGrade(int grade, int index)
	{
		grades[index] = grade;
	}
	void displayGrades() const 
	{
		cout << "Student: " << name << "; Grades: ";
		for(int i : grades)
		{
			cout << i << " ";
		}
		cout << endl;
	}

	string getName() const {return name;}

	int getGrade(int index)
	{
		return grades[index];
	}
private:
	string name;
	vector<int> grades;
};

class Section
{
public:
	Section(const string& name, const string& day, const int time) : name(name), t(day,time) {}
	void addStudent(const string& name)
	{
		students.push_back(new Student(name));
	}
	void displayGrades() const
	{
		cout << "Section: " << name << "; ";
		t.display();
		for
			(Student* s : students)
		{

			s->displayGrades();
		}
		cout << "\n";	
	}
	void addGrade(const string& name, int grade, int index)
	{
		for(Student* s : students)
		{
			
			
			if(s->getName() == name)
			{
				s->addGrade(grade,index);
			}
		}
	}
	void reset()
	{
		for(Student* s : students)
		{
			delete s;
			s = NULL;
		}
		students.clear();
	}

	void displayAverageForWeek(int index)
	{
		double total = 0;
		double count = 0;
		for (Student* s : students)
		{
			if(s->getGrade(index) != -1){
			total += s->getGrade(index);
			++count;
			}
		}
		
		cout << "The average for week " << index << " is: " << (total/count)*10 << endl;
	}
private:
	vector<Student*> students;
	TimeSlot t;
	string name;

};




class LabWorker
{
public:
	LabWorker(const string& name) : name(name){}
	void addGrade(const string& name, int grade, int index)
	{
		section->addGrade(name,grade,index);
	}
	void displayGrades() const 
	{
		section->displayGrades();
	}
	void addSection(Section& sec)
	{
		section = &sec;
	}
	void displayAverageForWeek(int index)
	{
		section->displayAverageForWeek(index);
	}
private:
	string name;
	Section* section;
};




int main()  
{
	// lab workers
   LabWorker moe( "Moe" );
   LabWorker jane( "Jane" );
   
   // sections and setup and testing
   Section secA2( "A2", "Tuesday", 16 );
   //secA2.loadStudentsFromFile( "A2.txt" );
   secA2.addStudent("John");
   secA2.addStudent("George");
   secA2.addStudent("Paul");
   secA2.addStudent("Ringo");

   cout << "\ntest A2\n";    // here the modeler-programmer checks that load worked
   secA2.displayGrades();          // YOU'll DO THIS LATER AS: cout << secA2 << endl;
   moe.addSection( secA2 );
   moe.displayGrades();       // here the modeler-programmer checks that adding the Section worked
  
   Section secB3( "B3", "Thursday", 11 );
   //secB3.loadStudentsFromFile( "B3.txt" );
   secB3.addStudent("Thorin");
   secB3.addStudent("Dwalin");
   secB3.addStudent("Balin");
   secB3.addStudent("Kili");
   secB3.addStudent("Fili");
   secB3.addStudent("Dori");
   secB3.addStudent("Nori");
   secB3.addStudent("Ori");
   secB3.addStudent("Oin");
   secB3.addStudent("Gloin");
   secB3.addStudent("Bifur");
   secB3.addStudent("Bofur");
   secB3.addStudent("Bombur");

   cout << "\ntest B3\n";    // here the modeler-programmer checks that load worked
   secB3.displayGrades();          // YOU'll DO THIS LATER AS: cout << secB3 << endl;
   jane.addSection( secB3 );
   jane.displayGrades();      // here the modeler-programmer checks that adding Instructor worked


   // setup is complete, now a real world scenario can be written in the code
   // [NOTE: the modeler-programmer is only modeling joe's actions for the rest of the program]

   // week one activities  
   cout << "\nModeling week: 1\n";
   moe.addGrade( "John", 7, 1 );  
   moe.addGrade( "Paul", 9, 1 );  
   moe.addGrade( "George", 7, 1 );  
   moe.addGrade( "Ringo", 7, 1 );  
   cout << "End of week one\n";
   moe.displayGrades();

   // week two activities
   cout << "\nModeling week: 2\n";
   moe.addGrade( "John", 5, 2 );  
   moe.addGrade( "Paul", 10, 2 );  
   moe.addGrade( "Ringo", 0, 2 );  
   cout << "End of week two\n";
   moe.displayGrades();

   moe.displayAverageForWeek(2);

   //test that reset works  // NOTE: can we check that the heap data was dealt with?
   cout << "\ntesting reset()\n";
   secA2.reset();
   secA2.displayGrades();
   moe.displayGrades();

}
