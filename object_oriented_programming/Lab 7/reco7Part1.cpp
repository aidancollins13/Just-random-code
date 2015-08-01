
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
};

class Trombone : public Brass
{
public:
	Trombone(int mouthpeice) : Brass(mouthpeice) {}
	void makeSound() const
	{
		Brass::makeSound();
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
};

class Cello : public String
{
public:
	Cello(int pitch) : String(pitch) {}
	void makeSound() const
	{
		String::makeSound();
	}

};

class Drum : public Percussion
{
public:
	void makeSound() const
	{
		Percussion::makeSound();
	}

};

class Cymbal : public Percussion
{
public:
	void makeSound() const
	{
		Percussion::makeSound();
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
private:
	Instrument* instr;
};


// PART ONE
int main()
{

   cout << "Define some instruments ----------------------------------------\n";
   Drum drum;
   Cello cello(673);
   Cymbal cymbal;
   Trombone tbone( 4 );
   Trumpet trpt( 12 ) ;
   Violin violin( 567 ) ;
  
  /// use the debugger to look at the mill
   cout << "Define the MILL ------------------------------------------------\n";
   MILL mill;
  
   cout << "Put the instruments into the MILL ------------------------------\n";
   mill.receiveInstr( trpt );
   mill.receiveInstr( violin );
   mill.receiveInstr( tbone );
   mill.receiveInstr( drum );
   mill.receiveInstr( cello );
   mill.receiveInstr( cymbal );
  
   cout << "Daily test -----------------------------------------------------\n";
   cout << endl;
   cout << "dailyTestPlay()" << endl;
   mill.dailyTestPlay();
   cout << endl;
  
  cout << "Define some Musicians-------------------------------------------\n";
   Musician j;
  Musician jj;
  Musician q;
  	
   cout << "TESTING: q.acceptInstr( *mill.loanOut() );-----------------------\n";
   q.testPlay();	
   cout << endl;
   q.acceptInstr( *mill.loanOut() );
   cout << endl;
   q.testPlay();
   cout << endl;
   cout << "dailyTestPlay()" << endl;
   mill.dailyTestPlay();
  
   cout << endl << endl;
  
   q.testPlay();	
   cout << endl;
   mill.receiveInstr( *q.giveBackInstr() );
   j.acceptInstr( *mill.loanOut() );
   q.acceptInstr( *mill.loanOut() );
   cout << endl;
   q.testPlay();
   cout << endl;
   j.testPlay();
   cout << endl;
   cout << "dailyTestPlay()" << endl;
   mill.dailyTestPlay();
  
   cout << "TESTING: mill.receiveInstr( *q.giveBackInstr() ); -------------\n";
  
   // fifth
   mill.receiveInstr( *q.giveBackInstr() );
   cout << "TESTING: mill.receiveInstr( *j.giveBackInstr() ); -------------\n";
   mill.receiveInstr( *j.giveBackInstr() );

  
   cout << endl;
   cout << "dailyTestPlay()" << endl;
   mill.dailyTestPlay();
   cout << endl;
  
   cout << endl;

}

