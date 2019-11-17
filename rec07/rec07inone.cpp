/*
  rec07
  Starter Code for required functionality
  Yes, you may add other methods.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
	friend ostream& operator<<(ostream& os, const Course& rhs);
public:
	// Course methods needed by Registrar
	Course(const string& courseName);
	const string& getName() const;
	bool addStudent(Student*);
	void removeStudentsFromCourse();
private:
	string name;
	vector<Student*> students;
};

class Student {
	friend ostream& operator<<(ostream& os, const Student& rhs);
public:
	// Student methods needed by Registrar
	Student(const string& name);
	const string& getName() const;
	bool addCourse(Course*);

	// Student method needed by Course
	void removedFromCourse(Course*);

private:
	string name;
	vector<Course*> courses;
};


class Registrar {
	friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
	Registrar();
	bool addCourse(const string&);
	bool addStudent(const string&);
	bool enrollStudentInCourse(const string& studentName,
		const string& courseName);
	bool cancelCourse(const string& courseName);
	void purge();

private:
	size_t findStudent(const string& thename) const;
	size_t findCourse(const string& thename) const;

	vector<Course*> courses;
	vector<Student*> students;
};
Registrar::Registrar() {}

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
		if (findCourse(thename)!=courses.size()) {
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
			cout << thename<<" already exists!" << endl;
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
		for (size_t i = findCourse(courseName);i < courses.size()-1;i++) {
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
int main() {

	Registrar registrar;

	cout << "No courses or students added yet\n";
	cout << registrar << endl;

	cout << "AddCourse CS101.001\n";
	registrar.addCourse("CS101.001");
	cout << registrar << endl;

	cout << "AddStudent FritzTheCat\n";
	registrar.addStudent("FritzTheCat");
	cout << registrar << endl;

	cout << "AddCourse CS102.001\n";
	registrar.addCourse("CS102.001");
	cout << registrar << endl;

	cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
	registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
	cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
	registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
	cout << registrar << endl;

	cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
	cout << "Should fail, i.e. do nothing, "
		<< "since Bullwinkle is not a student.\n";
	registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
	cout << registrar << endl;

	cout << "CancelCourse CS102.001\n";
	registrar.cancelCourse("CS102.001");
	cout << registrar << endl;

	/*
	// [OPTIONAL - do later if time]
	cout << "ChangeStudentName FritzTheCat MightyMouse\n";
	registrar.changeStudentName("FritzTheCat", "MightyMouse");
	cout << registrar << endl;

	cout << "DropStudentFromCourse MightyMouse CS101.001\n";
	registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
	cout << registrar << endl;

	cout << "RemoveStudent FritzTheCat\n";
	registrar.removeStudent("FritzTheCat");
	cout << registrar << endl;
	*/

	cout << "Purge for start of next semester\n";
	registrar.purge();
	cout << registrar << endl;
}
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
ostream& operator<<(ostream& os, const Student& rhs) {
	os << rhs.name << ": ";
	if (rhs.courses.size() == 0) {
		os << "None" << endl;
	}
	else {
		for (size_t i = 0;i < rhs.courses.size();i++) {
			os << rhs.courses[i]->getName()<<" ";
		}
		os << endl;
	}
	return os;
}
ostream& operator<<(ostream& os, const Registrar& rhs) {
	os << "Registrar's Report" << endl;
	os << "Courses: "<<endl;
	for (size_t i = 0;i < rhs.courses.size();i++) {
		os << *rhs.courses[i];
	}
	os << "Students: "<<endl;
	for (size_t i = 0;i < rhs.students.size();i++) {
		os << *rhs.students[i];
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
	size_t a;
	for (size_t i = 0;i < courses.size();i++) {
		if (courses[i]->getName() == thecourse->getName()) {
			a = i;
		}
	}
	for (size_t i=a;i < courses.size()-1;i++) {
		courses[i] = courses[i + 1];
	}
	courses.pop_back();
}