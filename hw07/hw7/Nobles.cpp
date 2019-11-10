//Hengning Zhang 
//hw07 
//hz1704
#include "Nobles.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;
//methods of nobles, including getters, setters and fire, hire, battle, battlecry
namespace WarriorCraft {
	Noble::Noble(const string& name, float strength = 0) :name(name), life(true), strength(strength) {}
	bool Noble::getLife() {
		return life;
	}
	float Noble::getStrength() {
		return strength;
	}
	string Noble::getName() {
		return name;
	}

	void Noble::setStrength(float newstrength) {
		strength = newstrength;
	};
	//this is the battle function, which is mainly the same with the previous assignments
	//except for the battlecrys which calls the protectors' battlecrys
	void Noble::battle(Noble& noble) {
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
			battleCry();
			noble.battleCry();
			float strength1 = this->strength;
			float strength2 = noble.strength;
			if (strength1 == strength2) {
				setStrength(0.0);
				noble.setStrength(0.0);
				setDerivedStrength(0.0);
				noble.setDerivedStrength(0.0);
				life = false;
				noble.life = false;
				cout << "Mutual annihilation," << name << " and " << noble.name
					<< "died at each other's hand!" << endl;
				return;
			}
			if (strength1 > strength2) {
				setStrength(strength1 - strength2);
				noble.setStrength(0.0);
				noble.setDerivedStrength(0.0);
				noble.life = false;
				cout << name << " defeats " << noble.name << endl;
				return;
			}
			else {
				noble.setStrength(strength2 - strength1);
				setStrength(0.0);
				setDerivedStrength(0.0);
				life = false;
				cout << noble.name << " defeats " << name << endl;
				return;
			}

		}
	}

	Lord::Lord(const string& name) :Noble(name) {}

	//hire and fire are also almost the same with previous assignments
	bool Lord::hires(Protector& servant) {
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
	bool Lord::fire(Protector& servant) {
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
				setStrength(getStrength() - servant.getStrength());
				return true;
			}

		}
		return false;
	}
	//this is important in this assignment because there are two kinds of nobles
	//lords require setDerivedStrength while the fighting nobles do not
	//therefore I wrote this method
	void Lord::setDerivedStrength(float newstrength) {
		for (size_t i = 0; i < protectors.size(); i++) {
			float oldstrength = protectors[i]->getStrength();
			protectors[i]->setStrength(oldstrength * (newstrength / oldstrength));
		}
	}
	void Lord::battleCry() {
		for (size_t i = 0; i < protectors.size(); i++) {
			protectors[i]->battleCry();
		}
	}
	void PersonWithStrengthToFight::setDerivedStrength(float newstrength) {}
	void PersonWithStrengthToFight::battleCry() {
		cout << "UGH!!!" << endl;
	}
}
