//Hengning Zhang 
//hw07 
//hz1704
#ifndef NOBLES
#define NOBLES
#include<string>
#include<vector>
#include "Protector.h"
//Prototypes for the nobles classes
namespace WarriorCraft {
	class Protector;
	class Noble {
	public:
		Noble(const std::string& name, float strength);
		bool getLife() const;
		float getStrength() const;
		std::string getName() const;
		virtual void setDerivedStrength(float newstrength) = 0;
		void setStrength(float newstrength);
		virtual void battleCry() = 0;
		void battle(Noble& noble);
	private:
		bool life;
		float strength;
		std::string name;
	};



	class Lord :public Noble {
	public:
		Lord(const std::string& name);
		bool hires(Protector& servant);
		bool fire(Protector& servant);
		void setDerivedStrength(float newstrength);
		void battleCry();
	private:
		std::vector<Protector*> protectors;
	};

	class PersonWithStrengthToFight : public Noble {
	public:
		using Noble::Noble;
		void setDerivedStrength(float newstrength);
		void battleCry();
	};
}


#endif