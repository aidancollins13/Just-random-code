#include <iostream>
#include <vector>
using namespace std;



class PrintedMaterial {
public:
	PrintedMaterial(unsigned pages): numberOfPages(pages) {}

	virtual void displayNumPages() const = 0;
private:
	unsigned numberOfPages;
};

void PrintedMaterial::displayNumPages() const {
	cout << numberOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
	Magazine(unsigned pages) : PrintedMaterial(pages) {}
	void displayNumPages() const { PrintedMaterial::displayNumPages();}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book (unsigned pages) : PrintedMaterial(pages) {}
	void displayNumPages() const { PrintedMaterial::displayNumPages();}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook(unsigned pages, unsigned iPages) : Book(pages), numOfIndexPages(iPages) {}
	void displayNumPages() const
	{
		cout << numOfIndexPages << endl;
		PrintedMaterial::displayNumPages();
	}
protected:
private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel(unsigned pages) : Book(pages) {}
	void displayNumPages() const { PrintedMaterial::displayNumPages();}
protected:
private:
};

void displayNumPages( const PrintedMaterial& pm)
{
	pm.displayNumPages();
}


// tester/modeler code
int main()
{
	vector<PrintedMaterial*> things;
	TextBook t(10,1);
	Novel n(12);
	Magazine m(11);
	things.push_back(&t);
	things.push_back(&n);
	things.push_back(&m);
		
//PrintedMaterial* pmPtr;
//pmPtr = &t;
// instead of putting an actual PrintedMaterial
// object into the vector, we put a pointer to
// a PrintedMaterial object (t) into a vector
// of pointers-to-PrintedMaterial
// (that is, pointers to the Base class)
// we'll be "managing" our objects by using
// pointers to PrintedMaterial values.
	
//pmPtr->displayNumPages();

	//t.displayNumPages();
	//n.displayNumPages();
	for (PrintedMaterial* pm : things)
	{
		pm->displayNumPages();
	}
}