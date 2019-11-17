#include <string>
#include <iostream>
#include <vector>
using namespace std;



class Section {
	class Student {
		friend ostream& operator<<(ostream& os, const Student& astudent) {
			os << "Name: " << astudent.name << ",Grades: ";
			for (size_t i = 0;i < astudent.grades.size();i++) {
				os << astudent.grades[i] << " ";
			}
			os << endl;
			return os;
		}
	public:
		Student(const string& thename) {
			name = thename;
			grades = {};
			for (int i = 0;i < 14;i++) {
				grades.push_back(-1);
			}
		}

		const string& getname() const {
			return name;
		}
		const vector<int>& getgrades() const {
			return grades;
		}
		void setgrade(int grade, int week) {
			for (size_t i = 0;i < grades.size();i++) {
				if (i == week) {
					grades[i] = grade;
				}
			}
		}
	private:
		string name;
		vector<int> grades;
	};
	class Timeslot {
		friend ostream& operator<<(ostream& os, const Timeslot& atime) {
			cout << "Time slot : [Day: " << atime.day << " Start time : " << atime.time << "] ";
			return os;
		}
	public:
		Timeslot(const string& theday, int thetime) { day = theday; time = thetime; }
		

	private:
		string day;
		int time;
	};
	friend ostream& operator<<(ostream& os, const Section& asection) {
		cout << "Section: " << asection.name << ", " << asection.timeslot << "Students:";
		if (asection.students.size() == 0) {
			os << " None" << endl;
		}
		else {
			os << endl;
			for (size_t i = 0;i < asection.students.size();i++) {
				os << *asection.students[i] << endl;
			}

		}
		return os;
	}
public:
	Section(const string& thename, const string theday, int thenumber) : name(thename), timeslot(theday, thenumber) {}

	

	Section(const Section& rhs) : name(rhs.name), timeslot(rhs.timeslot), students(rhs.students) {
		for (size_t i = 0;i < students.size();i++) {
			students[i] = new Student(*rhs.students[i]);
		}
	}
	~Section() {
		cout << "deleting section " << name<<endl;
		for (size_t i = 0;i < students.size();i++) {
			cout << "deleting " << (*students[i]).getname() << endl;
			delete students[i];
		}
		students.clear();
	}
	void addStudent(string studentname) {
		students.push_back(new Student(studentname));
	}
	void changegrade(const string& thename, int grade, int week) {
		for (size_t i = 0;i < students.size();i++) {
			if ((*students[i]).getname() == thename) {
				(*students[i]).setgrade(grade, week);
			}
		}
	}
private:
	
	
	string name;
	Timeslot timeslot;
	vector<Student*> students;
};


class LabWorker {
	friend ostream& operator<<(ostream& os, LabWorker aworker) {
		os << aworker.name << " has ";
		if (aworker.section == nullptr) {
			os << "no section." << endl;
		}
		else {
			os << *aworker.section << endl;
		}

		return os;
	}
public:
	LabWorker(const string& thename) : hired(false), name(thename),section(nullptr) {}
	
	void addSection(Section& asection) {
		if (hired == false) {
			section = &asection;
			hired = true;
		}
		else {
			cout << name << " is hired" << endl;
		}

	}

	void addGrade(const string& thename, int grade, int week) {
		(*section).changegrade(thename, grade, week-1);
	}
private:
	bool hired;
	string name;
	Section* section;

};

void doNothing(Section  sec) {
	cout << sec << endl;;
}

int main() {

	cout << "Test 1: Defining a section\n";
	Section secA2("A2", "Tuesday", 16);
	cout << secA2 << endl;

	cout << "\nTest 2: Adding students to a section\n";
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");

	cout << secA2 << endl;

	cout << "\nTest 3: Defining a lab worker.\n";
	LabWorker moe("Moe");
	cout << moe << endl;

	cout << "\nTest 4: Adding a section to a lab worker.\n";
	moe.addSection(secA2);
	cout << moe << endl;

	cout << "\nTest 5: Adding a second section and lab worker.\n";
	LabWorker jane("Jane");
	Section secB3("B3", "Thursday", 11);
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
	jane.addSection(secB3);
	cout << jane << endl;
	
	cout << "\nTest 6: Adding some grades for week one\n";
	moe.addGrade("John", 17, 1);
	moe.addGrade("Paul", 19, 1);
	moe.addGrade("George", 16, 1);
	moe.addGrade("Ringo", 7, 1);
	cout << moe << endl;

	cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
	moe.addGrade("John", 15, 3);
	moe.addGrade("Paul", 20, 3);
	moe.addGrade("Ringo", 0, 3);
	moe.addGrade("George", 16, 3);
	cout << moe << endl;
	
	cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
		<< "those students (or rather their records?)\n";
	
	cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
		<< "then make sure the following call works properly, i.e. no memory leaks\n";
	doNothing(secA2);
	cout << "Back from doNothing\n\n";

}