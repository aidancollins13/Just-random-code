#include <iostream>
using namespace std;

class Foo{
public:
	Foo(int x) {p=new int(x);}
	void display() const {cout << *p << endl;}
	void setValue(int val) {*p = val;}
	//void cleanUp() {delete p;}
	~Foo() {delete p;}  //destructor. called when a foo object ceices to exist
	Foo(const Foo& someOtherFoo) {p = new int(*someOtherFoo.p); }
	Foo& operator=(const Foo& rhs) {
		if (this != &rhs){
			//free up the resource
			delete p;		
			p = new int(*rhs.p);
		}
		return *this;
	}

private: 
	int* p;
};

void doNothing(Foo anotherFoo) {}

Foo simpleFunc() {
	Foo aFoo(17);
	aFoo.display();
	doNothing(aFoo);

		Foo yetAnotherFoo(1);
	// aFoo.operator=(yetAnotherFoo);
	return aFoo;
	//	aFoo.cleanUp();

}

int main(){

	simpleFunc();
}
