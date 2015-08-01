#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include <fstream>
using namespace std;

class Instrument
{
public:
	virtual void makeSound() const = 0;
	virtual void play() const = 0;
};
void Instrument::makeSound() const
{
	cout << "To make a sound ... ";
}

class Brass : public Instrument
{
public:
	Brass(int mouthpeice) : mouthpeice(mouthpeice) {}

	void makeSound() const = 0;
private:
	int mouthpeice;

};

void Brass::makeSound() const 
{
	Instrument::makeSound();
	cout << "blow on a mouthpeice of size " << mouthpeice << endl;
}


class String : public Instrument
{
public:
	String(int pitch) : pitch(pitch) {}
	
	void makeSound() const = 0;

private:
	int pitch;
};

void String::makeSound() const 
{
	Instrument::makeSound();
	cout << "bow a string wiht pitch " << pitch << endl;
}


class Percussion : public Instrument
{
public:
	void makeSound() const = 0;
};
void Percussion::makeSound() const
{
	Instrument::makeSound();
	cout << "hit me!\n";
}

class Trumpet : public Brass
{
public:
	Trumpet(int mouthpeice) : Brass(mouthpeice){}
	void makeSound() const
	{
		Brass::makeSound();
	}
	void play() const
	{
		cout << "Toot";
	}
};

class Trombone : public Brass
{
public:
	Trombone(int mouthpeice) : Brass(mouthpeice) {}
	void makeSound() const
	{
		Brass::makeSound();
	}
	void play() const
	{
		cout << "Blat";
	}
};

class Violin : public String
{
public:
	Violin(int pitch) : String(pitch) {}
	void makeSound() const
	{
		String::makeSound();
	}
	void play() const
	{
		cout << "Screech";
	}
};

class Cello : public String
{
public:
	Cello(int pitch) : String(pitch) {}
	void makeSound() const
	{
		String::makeSound();
	}
	void play() const
	{
		cout << "Squawk";
	}

};

class Drum : public Percussion
{
public:
	void makeSound() const
	{
		Percussion::makeSound();
	}
	void play() const
	{
		cout << "Boom";
	}

};

class Cymbal : public Percussion
{
public:
	void makeSound() const
	{
		Percussion::makeSound();
	}
	void play() const
	{
		cout << "Crash";
	}
};

class MILL
{
public:
	Instrument* loanOut()
	{
		for (size_t index = 0; index < instruments.size(); ++index)
		{
			if(instruments[index] != NULL)
			{
				Instrument* temp = instruments[index];
				instruments[index] = NULL;
				return temp;
			}
		}
		return NULL;
	}
	void receiveInstr(Instrument& ins)
	{
		ins.makeSound();
		for (size_t i = 0; i < instruments.size(); ++i)
		{
			if(instruments[i] == NULL)
			{
				instruments[i] = &ins;
				return;
			}
		}
		instruments.push_back(&ins);
	}
	void dailyTestPlay()
	{
		for(Instrument* i : instruments)
		{
			if(i != NULL)
			{
				i->makeSound();
			}
		}
	}

private:
	vector<Instrument*> instruments;
};

class Musician {
public:
	Musician() : instr( NULL ) {}
	void acceptInstr( Instrument & i ) { instr = &i; }
	Instrument* giveBackInstr( ) { 
		Instrument* tmp(instr); 
		instr = NULL;
		return tmp;
	}
	void testPlay() const {
		if( instr )
			instr->makeSound(); 
		else
			cerr << "have no instr\n";
	}

	void play() const
	{
		if(instr)
			instr->play();
	}
private:
	Instrument* instr;
};

class Orch
{
public:
	void addPlayer(Musician& m)
	{
		if(musicians.size() < 25)
		{
			musicians.push_back(&m);
		}

	}

	void play() const
	{
		for (Musician* m : musicians)
		{
			m->play();
		}
		cout << endl;
	}
private:
	vector<Musician*> musicians;
};

// PART TWO
int main()
{
	// The initialization phase

	Drum drum;
	Cello cello(673);
	Cymbal cymbal;
	Trombone tbone( 4 );
	Trumpet trpt( 12 ) ;
	Violin violin( 567 ) ;

	MILL mill;
	mill.receiveInstr( trpt );
	mill.receiveInstr( violin );
	mill.receiveInstr( tbone );
	mill.receiveInstr( drum );
	mill.receiveInstr( cello );
	mill.receiveInstr( cymbal );

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
	sue.acceptInstr( *mill.loanOut() );
	orch.addPlayer(sue);

	//Ralph gets an instrument from the MIL2.
	ralph.acceptInstr( *mill.loanOut() );

	//Mary gets an instrument from the MIL2 and joins the orchestra.
	mary.acceptInstr( *mill.loanOut() );
	orch.addPlayer(mary);

	//Ralph returns his instrument to the MIL2.
	mill.receiveInstr( *ralph.giveBackInstr() );

	//Jody gets an instrument from the MIL2 and joins the orchestra.
	jody.acceptInstr( *mill.loanOut() );
	orch.addPlayer(jody);

	// morgan gets an instrument from the MIL2
	morgan.acceptInstr( *mill.loanOut() );

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Ralph joins the orchestra.
	orch.addPlayer(ralph);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();
	
	// bob gets an instrument from the MIL2
	bob.acceptInstr( *mill.loanOut() );

	// ralph gets an instrument from the MIL2
	ralph.acceptInstr( *mill.loanOut() );

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Morgan joins the orchestra.
	orch.addPlayer(morgan);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

} // main

