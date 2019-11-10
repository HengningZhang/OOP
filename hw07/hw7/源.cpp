#include<string>
#include<vector>
#include<iostream>
using namespace std;

class Lord;
class Protector {
public:
	Protector(const string& name, float strength) : name(name), strength(strength), lord(nullptr) {}
	float getStrength() {
		return strength;
	}
	bool getState() {
		return (lord != nullptr);
	}
	string getName() {
		return name;
	}
	void setStrength(float newstrength) {
		strength = newstrength;
	}
	void setLord(Lord* newlord) {
		lord = newlord;
	}
	Lord* getLord() {
		return lord;
	}
	void fired() {
		lord = nullptr;
	}
	virtual void battleCry() = 0;
private:
	string name;
	float strength;
	Lord* lord;
};

class Noble {
public:
	Noble(const string& name,float strength=0) :name(name),life(true),strength(strength) {}
	bool getLife() {
		return life;
	}
	float getStrength() {
		return strength;
	}
	string getName() {
		return name;
	}
	virtual void setDerivedStrength(float newstrength) = 0;
	void setStrength(float newstrength) {
		strength = newstrength;
	};
	virtual void battleCry() = 0;
	void battle(Noble& noble) {
		cout << name << " battles " << noble.name << endl;
		if (this == &noble) {
			cout << "He cannot battle himself!" << endl;
			return;
		}
		if (this->life == false && noble.life == false) {
			cout << "Oh,No!They're both dead!Yuck!" << endl;
			return;
		}
		if (this->life == false) {
			cout << "He is dead, " << noble.name << endl;
			return;
		}
		if (noble.life == false) {
			cout << "He is dead, " << this->name << endl;
			return;
		}
		else {
			int strength1 = this->strength;
			int strength2 = noble.strength;
			if (strength1 == strength2) {
				setStrength(0.0);
				noble.setStrength(0.0);
				life = false;
				noble.life = false;
				cout << "Mutual annihilation," << name << " and " << noble.name
					<< "died at each other's hand!" << endl;
				return;
			}
			if (strength1 > strength2) {
				setStrength(strength1 - strength2);
				noble.setStrength(0.0);
				noble.life = false;
				cout << name << " defeats " << noble.name << endl;
				return;
			}
			else {
				noble.setStrength(strength2 - strength1);
				setStrength(0.0);
				life = false;
				cout << noble.name << " defeats " << name << endl;
				return;
			}

		}
	}
private:
	bool life;
	float strength;
	string name;
};
class Wizard :public Protector {
	using Protector::Protector;
	void battleCry() {
		cout << "POOF" << endl;
	}
};
class Warrior :public Protector {
	using Protector::Protector;
	virtual void makeSound() = 0;
	void battleCry() {
		makeSound();
		cout << getName() << "says: Take that in the name of my lord: " << getLord()->getName() << endl;
	}
};
class Archer : public Warrior {
	using Warrior::Warrior;
	void makeSound() {
		cout << "TWANG! ";
	}
};
class Swordsman : public Warrior {
	using Warrior::Warrior;
	void makeSound() {
		cout << "CLANG! ";
	}
};
class Lord:public Noble {
public:
	using Noble::Noble;
	bool hires(Protector& servant) {
		if (getLife() == false) {
			cout << getName() << " is already dead! Dead man cannot hire!" << endl;
			return false;
		}
		if (servant.getStrength() != 0) {
			if (servant.getState() == false) {
				protectors.push_back(&servant);
				setStrength(getStrength() + servant.getStrength());
				servant.setLord(this);
				return true;
			}
			else {
				cout << servant.getName() << " has already been hired" << endl;
				return false;
			}

		}
		cout << servant.getName() << " is already dead" << endl;
		return false;
	}
	bool fire(Protector& servant) {
		if (getLife() == false) {
			cout << getName() << " is already dead! Dead man cannot fire!" << endl;
			return false;
		}
		for (size_t i = 0; i < protectors.size(); i++) {
			if (protectors[i] == &servant) {
				for (size_t j = i; j < protectors.size() - 1; j++) {
					protectors[j] = protectors[j + 1];
				}
				protectors.pop_back();
				servant.fired();
				return true;
			}

		}
		return false;
	}
	void setDerivedStrength(float newstrength) {
		for (size_t i = 0; i < protectors.size(); i++) {
			int oldstrength = protectors[i]->getStrength();
			protectors[i]->setStrength(oldstrength * (newstrength / oldstrength));
		}
	}
	void battleCry() {
		for (size_t i = 0; i < protectors.size(); i++) {
			protectors[i]->battleCry();
		}
	}
private:
	vector<Protector*> protectors;
};
class PersonWithStrengthToFight : public Noble{
public:
	using Noble::Noble;
	void setDerivedStrength(float newstrength){}
	void battleCry() {
		cout << "UGHHHHH" << endl;
	}
};


int main() {
	Lord sam("Sam");
	Archer samantha("Samantha", 200);
	sam.hires(samantha);
	Lord joe("Joe");
	PersonWithStrengthToFight randy("Randolf the Elder", 250);
	joe.battle(randy);
	joe.battle(sam);
	Lord janet("Janet");
	Swordsman hardy("TuckTuckTheHardy", 100);
	Swordsman stout("TuckTuckTheStout", 80);
	janet.hires(hardy);
	janet.hires(stout);
	PersonWithStrengthToFight barclay("Barclay the Bold", 300);
	janet.battle(barclay);
	janet.hires(samantha);
	Archer pethora("Pethora", 50);
	Archer thora("Thorapleth", 60);
	Wizard merlin("Merlin", 150);
	janet.hires(pethora);
	janet.hires(thora);
	sam.hires(merlin);
	janet.battle(barclay);
	sam.battle(barclay);
	joe.battle(barclay);
}