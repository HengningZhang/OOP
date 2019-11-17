
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Instrument {
public:
	virtual void makeSound() const = 0;
	virtual void play() const = 0;
private:
};

void Instrument::makeSound() const {
	cout << "To make a sound...";
}

class Brass :public Instrument {
public:
	Brass(unsigned size) :size(size) {};
	void makeSound() const {
		Instrument::makeSound();
		cout << "blow on a mouthpiece of size " << size << endl;
	}
private:
	unsigned size;

};

class Trumpet :public Brass {
	using Brass::Brass; 
	void play() const{
		cout << "TOOT" << endl;
	}
};
class Trombone :public Brass { 
	using Brass::Brass; 
	void play() const{
		cout << "BLAT" << endl;
	}
};

class String :public Instrument {
public:
	String(unsigned pitch) :pitch(pitch) {};
	void makeSound() const {
		Instrument::makeSound();
		cout << "bow a string with pitch " << pitch << endl;
	}
private:
	unsigned pitch;
};
class Violin :public String { 
	using String::String;
	void play() const{
		cout << "SCREECH" << endl;
	}
};
class Cello : public String { 
	using String::String; 
	void play() const{
		cout << "SQUAWK" << endl;
	}
};
class Percussion :public Instrument {
public:
	Percussion(){};
	void makeSound() const {
		Instrument::makeSound();
		cout << "hit me!" << endl;
	}
private:
};
class Drum :public Percussion {
	void play() const{
		cout << "BOOM" << endl;
	}
};
class Cymbal :public Percussion {
	void play() const{
		cout << "CRASH" << endl;
	}
};
class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << "have no instr\n";
    }
	void play() const{
		if (instr) instr->play();
	}

private:
    Instrument* instr;
};

class MILL {
public:
	MILL() {};
	
	void dailyTestPlay() {
		for (size_t i = 0;i < inventory.size();i++) {
			if (inventory[i] != nullptr) {
				inventory[i]->makeSound();
			}
		}
	}
	Instrument* loanOut() {
		for (size_t i = 0;i < inventory.size();i++) {
			if (inventory[i] != nullptr) {
				Instrument* temp = inventory[i];
				inventory[i] = nullptr;
				return temp;
			}
		}
		return nullptr;
	}
	void receiveInstr(Instrument& instr) {
		instr.makeSound();
		for (size_t i = 0;i < inventory.size();i++) {
			if (inventory[i] == nullptr) {
				inventory[i] = &instr;
				return;
			}
			
		}
		inventory.push_back(&instr);
	}
private:
	vector<Instrument*> inventory;
};
//// PART ONE
//int main() {
//
//     cout << "Define some instruments ------------------------------------\n";
//     Drum drum;
//     Cello cello(673);
//     Cymbal cymbal;
//     Trombone tbone(4);
//     Trumpet trpt(12) ;
//     Violin violin(567) ;
//  
//     // use the debugger to look at the mill
//     cout << "Define the MILL --------------------------------------------\n";
//     MILL mill;
//  
//     cout << "Put the instruments into the MILL --------------------------\n";
//     mill.receiveInstr(trpt);
//     mill.receiveInstr(violin);
//     mill.receiveInstr(tbone);
//     mill.receiveInstr(drum);
//     mill.receiveInstr(cello);
//     mill.receiveInstr(cymbal);
//  
//     cout << "Daily test -------------------------------------------------\n";
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//     cout << endl;
//  
//     cout << "Define some Musicians---------------------------------------\n";
//     Musician harpo;
//     Musician groucho;
//  	
//     cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
//     groucho.testPlay();	
//     cout << endl;
//     groucho.acceptInstr(mill.loanOut());
//     groucho.testPlay();
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//  
//    cout << endl << endl;
//	
//     groucho.testPlay();	
//     cout << endl;
//     mill.receiveInstr(*groucho.giveBackInstr());
//     harpo.acceptInstr(mill.loanOut());
//     groucho.acceptInstr(mill.loanOut());
//     cout << endl;
//     groucho.testPlay();
//     cout << endl;
//     harpo.testPlay();
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//  
//     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
//  
//     // fifth
//     mill.receiveInstr(*groucho.giveBackInstr());
//     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
//     mill.receiveInstr(*harpo.giveBackInstr());
//
//  
//     cout << endl;
//     cout << "dailyTestPlay()" << endl;
//     mill.dailyTestPlay();
//     cout << endl;
//  
//     cout << endl;
//}

class Orch {
public:
	void play() {
		for (Musician* person : people) {
			person->play();
		}
	}
	void addPlayer(Musician& person) {
		people.push_back(&person);
	}
private:
	vector<Musician*> people;
};
int main() {
	// The initialization phase

	Drum drum;
	Cello cello(673);
	Cymbal cymbal;
	Trombone tbone(4);
	Trumpet trpt(12);
	Violin violin(567);

	MILL mill;
	mill.receiveInstr(trpt);
	mill.receiveInstr(violin);
	mill.receiveInstr(tbone);
	mill.receiveInstr(drum);
	mill.receiveInstr(cello);
	mill.receiveInstr(cymbal);

	Musician bob;
	Musician sue;
	Musician mary;
	Musician ralph;
	Musician jody;
	Musician morgan;

	Orch orch;

	// THE SCENARIO

	//Bob joins the orchestra without an instrument.
	orch.addPlayer(bob);

	//The orchestra performs
	cout << "orch performs\n";
	orch.play();

	//Sue gets an instrument from the MIL2 and joins the orchestra.
	sue.acceptInstr(mill.loanOut());
	orch.addPlayer(sue);

	//Ralph gets an instrument from the MIL2.
	ralph.acceptInstr(mill.loanOut());

	//Mary gets an instrument from the MIL2 and joins the orchestra.
	mary.acceptInstr(mill.loanOut());
	orch.addPlayer(mary);

	//Ralph returns his instrument to the MIL2.
	mill.receiveInstr(*ralph.giveBackInstr());

	//Jody gets an instrument from the MIL2 and joins the orchestra.
	jody.acceptInstr(mill.loanOut());
	orch.addPlayer(jody);

	// morgan gets an instrument from the MIL2
	morgan.acceptInstr(mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Ralph joins the orchestra.
	orch.addPlayer(ralph);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	// bob gets an instrument from the MIL2
	bob.acceptInstr(mill.loanOut());

	// ralph gets an instrument from the MIL2
	ralph.acceptInstr(mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Morgan joins the orchestra.
	orch.addPlayer(morgan);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

} // main
