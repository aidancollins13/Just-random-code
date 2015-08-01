#include "Directory.h"
#include "Entry.h"
#include "Position.h"
using namespace std;

Directory::Directory()
	: capacity(2), size(0), entries(new Entry*[2] )
    {
        // Should we do this?  What do you think?
        for (size_t i = 0; i < capacity; i++) {
            entries[i] = nullptr;
        } // for
    } // Directory()

Directory::Directory(const Directory& anotherDir){
        entries = new Entry*[anotherDir.capacity];

        for(size_t i = 0; i < anotherDir.size; ++i){
            entries[i] = new Entry(*anotherDir.entries[i]);
        }

        size = anotherDir.size;
        capacity = anotherDir.capacity;
    }

Directory::~Directory() {
        for(size_t i = 0; i < size; ++i){
            delete entries[i];
        }
        
        delete [] entries;
    }

Directory& Directory::operator=(const Directory rhs){
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

unsigned Directory::operator[] (const string& name){
        for(size_t i = 0 ; i < size; ++i){
            if(entries[i]->getName() == name)
                return entries[i]->getPhone();
        }
    }

void Directory::add(const string& name, unsigned room, unsigned ph, Position& pos) {
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