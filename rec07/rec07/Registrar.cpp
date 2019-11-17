#include "Registrar.h"
#include "Course.h"
#include "Student.h"
using namespace std;

namespace BrooklynPoly {
	Registrar::Registrar() {};
	ostream& operator<<(ostream& os, const Registrar& rhs) {
		os << "Registrar's Report" << endl;
		os << "Courses: " << endl;
		for (size_t i = 0;i < rhs.courses.size();i++) {
			os << *rhs.courses[i];
		}
		os << "Students: " << endl;
		for (size_t i = 0;i < rhs.students.size();i++) {
			os << *rhs.students[i];
		}
		return os;
	}
	size_t Registrar::findStudent(const string& thename) const {
		for (size_t i = 0;i < students.size();i++) {
			if (students[i]->getName() == thename) {
				return i;
			}
		}
		return students.size();
	}
	size_t Registrar::findCourse(const string& thename) const {
		for (size_t i = 0;i < courses.size();i++) {
			if (courses[i]->getName() == thename) {
				return i;
			}
		}
		return students.size();
	}
	bool Registrar::addCourse(const string& thename) {
		for (size_t i = 0;i < courses.size();i++) {
			if (findCourse(thename) != courses.size()) {
				cout << thename << " already exists!" << endl;
				return false;
			}
		}
		courses.push_back(new Course(thename));
		return true;
	}
	bool Registrar::addStudent(const string& thename) {
		for (size_t i = 0;i < students.size();i++) {
			if (findStudent(thename) != students.size()) {
				cout << thename << " already exists!" << endl;
				return false;
			}
		}
		students.push_back(new Student(thename));
		return true;
	}
	bool Registrar::enrollStudentInCourse(const string& studentName,
		const string& courseName) {

		if (findCourse(courseName) != courses.size()) {
			if (findStudent(studentName) != students.size()) {
				courses[findCourse(courseName)]->addStudent(students[findStudent(studentName)]);
				return true;
			}
			else {
				cout << studentName << " does not exist!" << endl;
				return false;
			}
		}
		else {
			cout << courseName << " does not exist!" << endl;
			return false;
		}


	}
	bool Registrar::cancelCourse(const string& courseName) {

		if (findCourse(courseName) != courses.size()) {
			courses[findCourse(courseName)]->removeStudentsFromCourse();
			for (size_t i = findCourse(courseName);i < courses.size() - 1;i++) {
				courses[i] = courses[i + 1];
			}
			courses.pop_back();

			return true;
		}
		else {
			cout << courseName << " does not exist!" << endl;
			return false;
		}

	}
	void Registrar::purge() {
		for (size_t i = 0;i < courses.size();i++) {
			delete courses[i];
		}
		for (size_t i = 0;i < students.size();i++) {
			delete students[i];
		}
		courses.clear();
		students.clear();
	}
}
