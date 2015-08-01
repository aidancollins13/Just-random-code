#include <iostream>
#include <string>
class Entry;
class Position;
class Directory {
public:
    Directory();

    Directory(const Directory& anotherDir);

    ~Directory();

    Directory& operator=(const Directory rhs);

    friend std::ostream& operator<<(std::ostream& os, const Directory& dir);

    unsigned operator[] (const std::string& name);

    void add(const std::string& name, unsigned room, unsigned ph, Position& pos) ;
private:	
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory
