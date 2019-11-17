//Hengning Zhang 
//hz1704
//hw4


#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Noble;
//create the warrior class
class Warrior {
public:
	//constructor
	Warrior(const string& thename, int thestrength);
	bool getstate() const;
	void switchstate(Noble* thenoble);
	bool runaway();
	int getstrength() const;
	const string& getname() const;
	void losestrength(double x);

	

private:
	string name;
	int strength;
	bool state;
	Noble* employer;
};

//define the noble class
class Noble {
	//define the output operator
	friend ostream& operator<<(ostream& os, const Noble& thenoble);
	
public:
	Noble(const string& thename);
	bool hire(Warrior& thewarrior);
	bool fire(Warrior& thewarrior);
	bool lose(Warrior* thewarrior);
	bool alivestatus() const;
	void execute();
	const string& getname() const;
	int gettotalstrength() const;
	void settotalstrength(int x);
	void changevector(double x);
	void battle(Noble& anoble);


	

private:
	string name;
	vector<Warrior*> warriors;
	bool deadoralive;
	int totalstrength;
};

ostream& operator<<(ostream& os, const Noble& thenoble) {
	os << thenoble.name << " has an army of " << thenoble.warriors.size() << " " << endl;;
	for (size_t i = 0;i < thenoble.warriors.size();i++) {
		os <<"          "<< (*thenoble.warriors[i]).getname() << ":" << (*thenoble.warriors[i]).getstrength() << " "<<endl;

	}

	os << endl;
	return os;
}
Warrior::Warrior(const string& thename, int thestrength) { name = thename;strength = thestrength;state = false; employer = nullptr; }

//define the methods used to get hiredstate, switch hiredstate, get strength, get name, decrease strength
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

//constructor
Noble::Noble(const string& thename) { name = thename; deadoralive = true; totalstrength = 0; }

//define the methods for hire, fire, alivestatus, execute, getname, getstrength, set strength, and battle
bool Noble::hire(Warrior& thewarrior) {
	if (deadoralive == false) {
		cout << name << " is already dead! Dead man cannot hire!" << endl;
		return false;
	}
	if (thewarrior.getstrength() != 0) {
		if (thewarrior.getstate() == false) {
			thewarrior.switchstate(this);
			Warrior* warriorp = &thewarrior;
			warriors.push_back(warriorp);
			totalstrength = totalstrength + thewarrior.getstrength();
			return true;
		}
		else {
			cout << thewarrior.getname() << " has already been hired" << endl;
			return false;
		}

	}
	cout << thewarrior.getname() << " is already dead" << endl;
	return false;
}
bool Noble::fire(Warrior& thewarrior) {
	if (deadoralive == false) {
		cout << name << " is already dead! Dead man cannot fire!" << endl;
		return false;
	}
	bool found = false;
	for (size_t i = 0;i < warriors.size() - 1;i++) {
		if (found == true) {
			warriors[i] = warriors[i + 1];
		}
		else {
			if (warriors[i] == &thewarrior) {
				cout << "You don't work for me anymore! " << thewarrior.getname() << "!";
				cout << "--" << name << endl;
				thewarrior.switchstate(this);
				totalstrength = totalstrength - thewarrior.getstrength();
				found = true;
				warriors[i] = warriors[i + 1];
			}

		}

	}
	warriors.pop_back();
	return true;
}
bool Noble::lose(Warrior* thewarrior) {
	bool found = false;
	for (size_t i = 0;i < warriors.size() - 1;i++) {
		if (found == true) {
			warriors[i] = warriors[i + 1];
		}
		else {
			if (warriors[i] == thewarrior) {
				thewarrior->switchstate(this);
				totalstrength = totalstrength - thewarrior->getstrength();
				found = true;
				warriors[i] = warriors[i + 1];
			}

		}

	}
	warriors.pop_back();
	return true;
}
bool Noble::alivestatus() const {
	if (deadoralive == true) {
		return true;
	}
	else {
		return false;
	}
}
void Noble::execute() {
	deadoralive = false;
}
const string& Noble::getname() const {
	return name;
}
int Noble::gettotalstrength() const {
	return totalstrength;
}
void Noble::settotalstrength(int x) {
	totalstrength = x;
}

//changes the warriors' stats
void Noble::changevector(double x) {
	for (size_t i = 0;i < warriors.size();i++) {
		(*warriors[i]).losestrength(x);
	}
}
//the most important part, decides the results of battles
void Noble::battle(Noble& anoble) {
	cout << name << " battles " << anoble.getname() << endl;
	if (anoble.alivestatus() == false && deadoralive == false) {
		cout << "yuck, they're both dead!" << endl;
		return;
	}
	if (deadoralive == false) {
		cout << "he is dead, " << anoble.getname() << endl;
		return;
	}
	if (anoble.alivestatus() == false) {
		cout << "he is dead, " << name << endl;
	}
	else {
		int strength1 = totalstrength;
		int strength2 = anoble.gettotalstrength();
		if (strength1 == strength2) {
			totalstrength = 0;
			anoble.settotalstrength(0);
			changevector(0.0);
			cout << name << "has been executed" << endl;
			anoble.changevector(0.0);
			execute();
			anoble.execute();
			cout << "mutual annihilation! " << name << " and " <<
				anoble.getname() << " died at each other's hand" << endl;
			return;
		}
		if (strength1 > strength2) {
			double changer;
			changer = 1.0 - (double)anoble.gettotalstrength() / totalstrength * 1.0;
			totalstrength = totalstrength - anoble.gettotalstrength();
			anoble.settotalstrength(0);
			changevector(changer);
			anoble.changevector(0.0);
			anoble.execute();
			cout << name << " defeats " << anoble.getname() << endl;
			return;
		}
		else {
			double changer;
			changer = 1.0 - (double)totalstrength / anoble.gettotalstrength() * 1.0;
			anoble.settotalstrength(anoble.gettotalstrength() - totalstrength);
			totalstrength = 0;
			changevector(0.0);
			anoble.changevector(changer);
			execute();
			cout << anoble.getname() << " defeats " << name << endl;
		}
	}

}

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;

	cheetah.runaway();
	cout << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}
//int main() {
//
//	Noble art("King Arthur");
//	Noble lance("Lancelot du Lac");
//	Noble jim("Jim");
//	Noble linus("Linus Torvalds");
//	Noble billie("Bill Gates");
//
//	Warrior cheetah("Tarzan", 10);
//	Warrior wizard("Merlin", 15);
//	Warrior theGovernator("Conan", 12);
//	Warrior nimoy("Spock", 15);
//	Warrior lawless("Xena", 20);
//	Warrior mrGreen("Hulk", 8);
//	Warrior dylan("Hercules", 3);
//
//	jim.hire(nimoy);
//	lance.hire(theGovernator);
//	art.hire(wizard);
//	lance.hire(dylan);
//	linus.hire(lawless);
//	billie.hire(mrGreen);
//	art.hire(cheetah);
//
//	cout << "==========\n"
//		<< "Status before all battles, etc.\n";
//	cout << jim << endl;
//	cout << lance << endl;
//	cout << art << endl;
//	cout << linus << endl;
//	cout << billie << endl;
//	cout << "==========\n";
//
//	art.fire(cheetah);
//	cout << art << endl;
//
//
//	art.battle(lance);
//	jim.battle(lance);
//	linus.battle(billie);
//	billie.battle(lance);
//
//	cout << "==========\n"
//		<< "Status after all battles, etc.\n";
//	cout << jim << endl;
//	cout << lance << endl;
//	cout << art << endl;
//	cout << linus << endl;
//	cout << billie << endl;
//	cout << "==========\n";
//
//}