#include <iostream>
#include <fstream>
#include <string>
using namespace std;



class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& thewarrior) {
		os << "		" << name << ": " << strength << endl;
		return os;
	}
public:
	Warrior(const string& thename, int thestrength, hired = false)
		: name(thename);strength(thestrength);hired(hired) {}
	bool getstatus() {
		return hired;
	}
	void switchstate() {
		if (hired==false) {
			hired = true;
		}
		else {
			hired = false;
		}
	}
private:
	string name;
	int strength;
	bool hired;
};

class Noble {
	friend ostream& operator<<(ostream& os, const Noble& thenoble) {
		os << name << " has an army of " << warriors.size() << endl;
		for (size_t i = 0;i < warriors.size();i++) {
			os << warriors[i] << endl;
		}
	}
	return os;
public:
	Noble(const string& thename, int thesize = 0)
		:name(thename); size(thesize); warriors(new Warrior* [1]){}
	string getname() const {
		return name;
	}

	int getsize() const {
		return size;
	}
private:
	Warrior** warriors;
	string name;
	int size;
};

class World {
	friend ostream& operator<<(ostream& os, const World& theworld) {
		os << "Nobles:" << endl;
		for (size_t i = 0;i < nobles.size();i++) {
			os << (*nobles[i]).getname() << " has an army of " << (*nobles[i]).getsize() << endl;
		}
		
		cout << "Unemployed Warrior:" << endl;

		if (warriors.size_t == 0){
			cout << "NONE";
		}
		else {
			for (size_t i = 0;i < warriors.size();i++) {
				os << (*warriors[i]) << endl;
			}
		}
		
		return os;
	}
public:
	void addnoble(const Noble& thenoble) {
		nobles.push_back(new thenoble);
	}
	void addwarrior(const Warrior& thewarrior) {
		warriors.push_back(new thewarrior);
	}
private:
	Noble** nobles;
	Warrior** warriors;
};

int main() {
	string firstword;
	string name;
	int strength;
	World world;
	ifstream reader("nobleWarriors.txt");
	while reader(reader >> firstword) {
		if (firstword == "Noble") {
			reader >> name;
			world.addnoble(Noble(name));
		}
		if (firstword == "Warrior") {
			reader>>name>>strength;
			world.addwarrior(Warrior(name, strength));
		}
		if (firstword == "Status") {
			cout << world << endl;
		}
	}
}