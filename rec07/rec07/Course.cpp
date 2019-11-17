#include "Course.h"
#include "Student.h"
#include <iostream>
using namespace std;

namespace BrooklynPoly {
	ostream& operator<<(ostream& os, const Course& rhs) {
		os << rhs.name << ": ";
		if (rhs.students.size() == 0) {
			os << "None" << endl;
		}
		else {
			for (size_t i = 0;i < rhs.students.size();i++) {
				os << rhs.students[i]->getName();
			}
			os << endl;
		}
		return os;
	}
	Course::Course(const string& courseName) :
		name(courseName) {}
	const string& Course::getName() const {
		return name;
	}
	bool Course::addStudent(Student* astudent) {
		for (size_t i = 0;i < students.size();i++) {
			if (students[i] == astudent) {
				cout << astudent->getName() << " is already enrolled in " << name << endl;
				return false;
			}
		}
		students.push_back(astudent);
		astudent->addCourse(this);
		return true;
	}
	void Course::removeStudentsFromCourse() {
		for (size_t i = 0;i < students.size();i++) {
			students[i]->removedFromCourse(this);
		}
		students.clear();
	}
}
