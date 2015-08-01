/*
  Recitation 09
  CS1124
  Aidan Collins
 
  Focus: Copy Control.  Uses dynamic array of pointers.
 */

#include <string>
#include <iostream>
using namespace std;

class Position {
public:
    Position(const string& aTitle, double aSalary)
	: title(aTitle), salary(aSalary) {}
    string getTitle() const {return title;}
    double getSalary() const {return salary;}
    void changeSalaryTo(double d) {salary = d;}
private:
    string title;
    double salary;
}; // class Position

class Entry {
public:
    Entry(const string& aName, unsigned aRoom, unsigned aPhone,
	  Position& aPosition) 
	: name(aName), room(aRoom), phone(aPhone), pos(&aPosition) {
    }
    friend ostream& operator<<( ostream& os, const Entry& e ) {
        os << e.name << ' ' << e.room << ' ' << e.phone;
        return os;
    } // operato<<
    string getName() const {return name;}
    unsigned getPhone() const {return phone;}
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
public:
    Directory()
	: capacity(2), size(0), entries(new Entry*[2] )
    {
        // Should we do this?  What do you think?
        for (size_t i = 0; i < capacity; i++) {
            entries[i] = nullptr;
        } // for
    } // Directory()

    Directory(const Directory& anotherDir){
        entries = new Entry*[anotherDir.capacity];

        for(size_t i = 0; i < anotherDir.size; ++i){
            entries[i] = new Entry(*anotherDir.entries[i]);
        }

        size = anotherDir.size;
        capacity = anotherDir.capacity;
    }

    ~Directory() {
        for(size_t i = 0; i < size; ++i){
            delete entries[i];
        }
        
        delete [] entries;
    }

    Directory& operator=(const Directory rhs){
        if(this != &rhs){
            for(size_t i = 0; i < size; ++i){
            delete entries[i];
             }
            
            delete [] entries;
            entries = new Entry*[rhs.capacity];
            
            for(size_t i = 0; i < rhs.size; ++i){
            entries[i] = new Entry(*rhs.entries[i]);
            }
            capacity = rhs.capacity;
            size = rhs.size;

        }
        return *this;
    } 

    friend ostream& operator<<(ostream& os, const Directory& dir){
        os << "Entries";
        for(size_t i = 0; i < dir.size; ++i){
            os << *(dir.entries[i]) << "; ";
        }
        os << endl;
        return os;
    }

    unsigned operator[] (const string& name){
        for(size_t i = 0 ; i < size; ++i){
            if(entries[i]->getName() == name)
                return entries[i]->getPhone();
        }
    }
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if( size == capacity )	{
            Entry** temp = entries;
            entries = new Entry*[ capacity *= 2 ];
            for(size_t i = 0; i < size ; ++i){
                entries[i] = temp[i];
               
            }
            delete [] temp;
           

        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add
    //size_t getSize() const {return size;}
private:	
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
	
    // Model as if there are these four kinds 
    // of position in the problem:
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
	
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d2 << endl;
    //cout << d2.getSize() << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;
    cout << d3 << endl;
    cout << d2["Gallagher"];
	
} // main