#ifndef WARRIOR
#define WARRIOR
#include <string>
#include "Noble.h"

namespace WarriorCraft {
	class Noble;
	class Warrior {
	public:
		Warrior(const std::string& thename, int thestrength);
		bool getstate() const;
		void switchstate(Noble* thenoble);
		bool runaway();
		int getstrength() const;
		const std::string& getname() const;
		void losestrength(double x);



	private:
		std::string name;
		int strength;
		bool state;
		Noble* employer;
	};
}

#endif