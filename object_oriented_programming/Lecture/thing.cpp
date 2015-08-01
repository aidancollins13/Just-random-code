#include <iostream>
#include <vector>
using namespace std;

class Preformer{
public:
	virtual void preform()=0;
};

class Actor : public Preformer{
public:
	Actor(const string& name) : name(name){}
	void preform(){
		cout << "I am " << name << endl;
	}
private:
	string name;
};

class Mime : public Preformer{
public:
	void preform(){
		cout << "blank\n";
	}
};

class Theater{
public:
	void hire(Preformer& p){
		preformers.push_back(&p);
	}
	void showtime(){
		for(Preformer* p : preformers){
			p->preform();
		}
	}
private:
	vector<Preformer*> preformers;
};

int main(){
	Actor a("aaa");
	Actor e("eee");
	Mime b,c,d;
	Theater t;
	t.hire(a);
	t.hire(b);
	t.hire(c);
	t.hire(d);
	t.hire(e);
	t.showtime();
}