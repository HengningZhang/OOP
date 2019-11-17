//Hengning Zhang 
//hw07 
//hz1704
#include "Protector.h"
#include "Nobles.h"
#include<string>
#include<vector>
#include<iostream>
using namespace std;
//the methods for protectors, getters, setters and battlecrys
namespace WarriorCraft {
	class Lord;

	Protector::Protector(const string& name, float strength) : name(name), strength(strength), lord(nullptr) {}
	float Protector::getStrength() const{
		return strength;
	}
	bool Protector::getState() const{
		return (lord != nullptr);
	}
	string Protector::getName() const{
		return name;
	}
	void Protector::setStrength(float newstrength) {
		strength = newstrength;
	}
	void Protector::setLord(Lord* newlord) {
		lord = newlord;
	}
	Lord* Protector::getLord() const{
		return lord;
	}
	void Protector::fired() {
		lord = nullptr;
	}
	//the quit function
	//the fire function of nobles does not print anything in this assignment
	//so I just used Lord class's fire, as they get the same effect
	//errors are handled
	bool Protector::quit() {
		if (strength == 0) {
			cout << "Dead man cannot quit!" << endl;
			return false;
		}
		if (lord == nullptr) {
			cout << "unhired man cannot quit!" << endl;
			return false;
		}
		getLord()->fire(*this);
		return true;
	}
	void Wizard::battleCry() {
		cout << "POOF" << endl;
	}
	void Warrior::battleCry() {
		makeSound();
		cout << getName() << "says: Take that in the name of my lord: " << getLord()->getName() << endl;
	}
	void Archer::makeSound() {
		cout << "TWANG! ";
	}
	void Swordsman::makeSound() {
		cout << "CLANG! ";
	}
}
