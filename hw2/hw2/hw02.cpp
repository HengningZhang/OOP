#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//construct a warrior struct to pair the information
struct Warrior {
	string name;
	int strength;
};

//read the warrior information and store them in a vector of warrior
//then it would return the vector
vector<Warrior> initializewarriors(const string& filename) {
	ifstream reader(filename);
	vector<Warrior> warriors;
	string readtype;
	string readname;
	int readstrength;
	while (reader >> readtype >> readname >> readstrength) {
		Warrior awarrior;
		awarrior.name = readname;
		awarrior.strength = readstrength;
		warriors.push_back(awarrior);
	}

	return warriors;
}

//the battle part, decides who win the battle and does the output
void battle(vector<Warrior>& warriors, const string& warriorone, const string& warriortwo) {
	int warriorindex1;
	int warriorindex2;
	for (size_t i = 0;i < warriors.size();i++) {
		if (warriors[i].name == warriorone) {
			warriorindex1 = i;
		}
		if (warriors[i].name == warriortwo) {
			warriorindex2 = i;
		}
	}
	cout << warriors[warriorindex1].name << " battles " << warriors[warriorindex2].name<<endl;
	if (warriors[warriorindex1].strength == 0 && warriors[warriorindex2].strength == 0) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
		return;
	}
	if (warriors[warriorindex1].strength == 0) {
		cout << "He is dead, " << warriors[warriorindex2].name << endl;
		return;
	}
	if (warriors[warriorindex2].strength == 0) {
		cout << "He is dead, " << warriors[warriorindex1].name << endl;
	}
	else {
		if (warriors[warriorindex1].strength > warriors[warriorindex2].strength) {
			int damage = warriors[warriorindex2].strength;
			warriors[warriorindex1].strength = warriors[warriorindex1].strength - damage;
			warriors[warriorindex2].strength = warriors[warriorindex2].strength - damage;
			cout << warriors[warriorindex1].name << " defeats " << warriors[warriorindex2].name << endl;
		}
		else {
			int damage = warriors[warriorindex1].strength;
			warriors[warriorindex1].strength = warriors[warriorindex1].strength - damage;
			warriors[warriorindex2].strength = warriors[warriorindex2].strength - damage;
			if (warriors[warriorindex1].strength == 0) {
				cout << "Mutual Annihilation: " << warriors[warriorindex1].name << " and " << warriors[warriorindex2].name << " died at each others' hand" << endl;
			}
			else {
				cout << warriors[warriorindex2].name << " defeats " << warriors[warriorindex1].name << endl;
			}
		}
	}
}

//prints the current status of all the warriors in the vector
void status(const vector<Warrior>& warriors) {
	for (size_t i = 0;i < warriors.size();i++) {
		cout << "Warrior " << warriors[i].name << " " << warriors[i].strength << endl;
	}
}

//read the part after the declaration of warriors
//then execute the commands
int main() {

	vector<Warrior> warriors = initializewarriors("battle.txt");
	string read1;
	string read2;
	string read3;
	string line;
	ifstream reader("battle.txt");
	for (size_t i = 0;i < warriors.size();i++) {
		getline(reader, line);
	}

	while (reader>>read1) {
		if (read1 == "Status") {
			status(warriors);
		}
		else {
			reader >> read2 >> read3;
			battle(warriors, read2, read3);
		}
	}
}