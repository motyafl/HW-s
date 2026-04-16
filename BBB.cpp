#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Course
{
private:
	int course_id;
	string course_name;
	string instructor_name;
	static inline int next_course_id = 1;
public:
	Course(string name, string instructor) : course_name{name}, instructor_name{instructor}, course_id{next_course_id++} {};

	int get_course_id() { return course_id; }
	string get_course_name() { return course_name; }
	string get_instructor_name() { return instructor_name; }

	void display_info() {
		cout << "Course Name: " << get_course_name() << "\n" << "Instructor Name: " << get_instructor_name() << endl;
	}
};

class Student
{
private:
	int student_id;
	string name;
	vector<Course*> enrolled_courses;
	static inline int next_student_id = 1;
public:
	Student(string name) : name{name}, student_id{next_student_id++} {};
	
	int get_student_id() { return student_id; }
	string get_name() { return name; }
	void enroll_course(Course* course) {
		enrolled_courses.push_back(course);
	}

	void display_info() {
		cout << "Name: " << get_name() << "\n" << "Number of courses: " << (enrolled_courses).size() << endl;
		for (int i = 0; i < (enrolled_courses).size(); i++) {
		    enrolled_courses[i]->display_info();
		}
	}

};

int main()
{
	Student Michael ("Michael");
	Student Dima ("Dima");
	Student Will ("Will");
	
	Course Calc1("Calc I", "Plotnikova A.");
	Course Calc2("Calc II", "Shaykin V.");
	Course Law1("Basics of Law", "Keating A.");
	Course Physics("Basics of Kinematics", "Anderson M.");
	
	Will.enroll_course(&Calc1);
	Will.enroll_course(&Physics);
	
	Michael.enroll_course(&Calc2);
    	Michael.enroll_course(&Physics);
    
	Will.display_info();
	cout << endl;
	
	Michael.display_info();
	cout << endl;
}


