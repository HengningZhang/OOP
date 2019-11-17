#include "Course.h"
#include "Student.h"
using namespace std;
namespace BrooklynPoly {
	Student::Student(const string& name) :
		name(name) {}
	const string& Student::getName() const {
		return name;
	}
	bool Student::addCourse(Course* thecourse) {
		for (size_t i = 0;i < courses.size();i++) {
			if (courses[i] == thecourse) {
				cout << name << " is already enrolled in " << thecourse << endl;
				return false;
			}
		}
		courses.push_back(thecourse);
		return true;
	}
	void Student::removedFromCourse(Course* thecourse) {
		bool exist=false;
		for (size_t i = 0;i < courses.size()-1;i++) {
			if (courses[i]->getName() == thecourse->getName()) {
				exist = true;
			}
			if (exist == true) {
				courses[i] = courses[i + 1];
			}
		}
		courses.pop_back();
	}
	ostream& operator<<(ostream& os, const Student& rhs) {
		os << rhs.name << ": ";
		if (rhs.courses.size() == 0) {
			os << "None" << endl;
		}
		else {
			for (size_t i = 0;i < rhs.courses.size();i++) {
				os << rhs.courses[i]->getName() << " ";
			}
			os << endl;
		}
		return os;
	}
}

