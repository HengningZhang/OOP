#include<string>
#include<vector>
#include "Nobles.h"

class Lord;
class Protector {
public:
	Protector(const std::string& name, float strength);
	float getStrength();
	bool getState();
	std::string getName();
	void setStrength(float newstrength);
	void setLord(Lord* newlord);
	Lord* getLord();
	void fired();
	virtual void battleCry() = 0;
	bool quit();
private:
	std::string name;
	float strength;
	Lord* lord;
};
class Wizard :public Protector {
	using Protector::Protector;
	void battleCry();
};
class Warrior :public Protector {
	using Protector::Protector;
	virtual void makeSound() = 0;
	void battleCry();
};
class Archer : public Warrior {
	using Warrior::Warrior;
	void makeSound();
};
class Swordsman : public Warrior {
	using Warrior::Warrior;
	void makeSound();
};
