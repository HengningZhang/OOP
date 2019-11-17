#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace WarriorCraft {
	Warrior::Warrior(const string& thename, int thestrength) { name = thename;strength = thestrength;state = false; employer = nullptr; }

	bool Warrior::getstate() const {
		return state;
	}
	void Warrior::switchstate(Noble* thenoble) {
		if (state == false) {
			state = true;
			employer = thenoble;
		}
		else {
			state = false;
			employer = nullptr;
		}
	}
	bool Warrior::runaway() {
		if (strength == 0) {
			cout << name << " is dead, he cannot runaway anymore" << endl;
			return false;
		}
		if (employer == nullptr) {
			cout << name << " is not hired, he cannot runaway from himself!" << endl;
			return false;
		}
		else {
			cout << name << " flees in terror, abandoning his lord," << employer->getname() << endl;
			employer->lose(this);
			employer = nullptr;
		}
	}
	int Warrior::getstrength() const {
		return strength;
	}
	const string& Warrior::getname() const {
		return name;
	}
	void Warrior::losestrength(double x) {
		strength = strength * x;
	}

}
