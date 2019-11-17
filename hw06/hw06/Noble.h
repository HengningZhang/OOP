#ifndef NOBLE
#define NOBLE
#include <iostream>
#include <string>
#include <vector>
#include "Warrior.h"

namespace WarriorCraft {
	class Warrior;

	class Noble {
		//define the output operator
		friend std::ostream& operator<<(std::ostream& os, const Noble& thenoble);

	public:
		Noble(const std::string& thename);
		bool hire(Warrior& thewarrior);
		bool fire(Warrior& thewarrior);
		bool lose(Warrior* thewarrior);
		bool alivestatus() const;
		void execute();
		const std::string& getname() const;
		int gettotalstrength() const;
		void settotalstrength(int x);
		void changevector(double x);
		void battle(Noble& anoble);




	private:
		std::string name;
		std::vector<Warrior*> warriors;
		bool deadoralive;
		int totalstrength;
	};


}
#endif