#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
//Hengning Zhang hz1704 HW03:Battlegamewithclass

//construct the warrior class
//weapon class in private
class Warrior {
	
public:
	Warrior(const string& thename, const string& weaponname, int strength) :
		warriorname(thename),arm(weaponname,strength)
	{}
	friend ostream& operator<<(ostream& os, const Warrior& awarrior) {
		os << "Warrior: "<< awarrior.warriorname <<" Weapon: "<< awarrior.arm;
		return os;
	}
	const string& getname() const {
		return warriorname;
	}
	int getstrength() const{
		return arm.getstrength();
	}
	void setstrength(int thestrength) {
		arm.setstrength(thestrength);
	}
private:
	string warriorname;
	class Weapon {
	public:
		Weapon(const string& weaponname, int strength):
			name(weaponname),strength(strength)
		{}
		friend ostream& operator<<(ostream& os, const Weapon& aweapon) {
			os << aweapon.name << "," << aweapon.strength;
			return os;
		}
		int getstrength() const {
			return strength;
		}
		void setstrength(int newstrength) {
			strength = newstrength;
		}
		
	private:
		string name;
		int strength;
	};
	
	Weapon arm;

};

//the battle function, takes the names of two warriors and alters the two warrior objects
void battle(vector<Warrior>& warriors, const string& warrior1, const string& warrior2) {
	int warriorindex1;
	int warriorindex2;
	cout << warrior1 << " battles " << warrior2 << endl;
	for (size_t i = 0;i < warriors.size();i++) {
		if (warriors[i].getname() == warrior1) {
			warriorindex1 = i;
		}
		if (warriors[i].getname() == warrior2) {
			warriorindex2 = i;
		}
	}
	if (warriors[warriorindex1].getstrength() == 0 && warriors[warriorindex2].getstrength() == 0) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
		return;
	}
	if (warriors[warriorindex1].getstrength() == 0) {
		cout << "He is dead, " << warriors[warriorindex2].getname() << endl;
		return;
	}
	if (warriors[warriorindex2].getstrength() == 0) {
		cout << "He is dead, " << warriors[warriorindex1].getname() << endl;
	}
	else {
		if (warriors[warriorindex1].getstrength() > warriors[warriorindex2].getstrength()) {
			int damage = warriors[warriorindex2].getstrength();
			warriors[warriorindex1].setstrength(warriors[warriorindex1].getstrength() - damage);
			warriors[warriorindex2].setstrength(warriors[warriorindex2].getstrength() - damage);
			cout << warriors[warriorindex1].getname() << " defeats " << warriors[warriorindex2].getname() << endl;
		}
		else {
			int damage = warriors[warriorindex1].getstrength();
			warriors[warriorindex1].setstrength(warriors[warriorindex1].getstrength() - damage);
			warriors[warriorindex2].setstrength(warriors[warriorindex2].getstrength() - damage);
			if (warriors[warriorindex1].getstrength() == 0) {
				cout << "Mutual Annihilation: " << warriors[warriorindex1].getname()<< " and " << warriors[warriorindex2].getname() << " died at each others' hand" << endl;
			}
			else {
				cout << warriors[warriorindex2].getname() << " defeats " << warriors[warriorindex1].getname() << endl;
			}
		}
	}
}
//reads the file and executes the commands
void execute(const string& filename) {
	ifstream reader(filename);
	string type;
	string name;
	string armname;
	string battle1;
	string battle2;
	int strength;
	vector<Warrior> warriors;
	while (reader >> type) {
		if (type == "Warrior") {
			reader >> name >> armname >> strength;
			warriors.emplace_back(name, armname, strength);
		}
		if (type == "Status") {
			for (size_t i = 0;i < warriors.size();i++) {
				cout << warriors[i] << endl;
			}
		}
		if (type == "Battle") {
			reader >> battle1 >> battle2;
			battle(warriors, battle1, battle2);
		}
	}
	
}
int main() {
	execute("battle.txt");
}