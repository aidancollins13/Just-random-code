#include <cstdlib> // To allow NULL if no other includes
#include <iostream>
#include <string>
using namespace std;
struct Node {
	Node(int data = 0, Node* link = NULL) : data(data), next(link) {}
	int data;
	Node* next;
};

class Sequence{
public:
	Sequence() : headptr(NULL), curr(NULL){}

	Sequence(const Sequence& otherSequence){
		// cout<<"const";
		// cout<<otherSequence.headptr->data;
		headptr = new Node(otherSequence.headptr->data);
		curr = new Node(otherSequence.curr->data);
		Node* p = otherSequence.headptr;
		Node* q = headptr;
		while(p->next)
		{
			q->next = new Node(p->next->data);
			p = p->next;
			q = q->next;
		}
	}

	~Sequence(){this->clear();}

	void clear(){
		
			Node* p = headptr;
			while(p){
				Node* temp;
				temp = p->next;
				delete p;
				p = temp;
			}

			curr = NULL;
			headptr = NULL;
		
	}


	Sequence& operator=(const Sequence& rhs){
		if(&rhs != this){
			this->clear();
			headptr = new Node(rhs.headptr->data);
			curr = new Node(rhs.curr->data);
			Node* p = rhs.headptr;
			Node* q = headptr;
			while(p->next)
			{
				q->next = new Node(p->next->data);
				p = p->next;
				q = q->next;
			}
		}
	}

	bool valid(){
		return(curr);
	}

	void reset() { 
		if(this->valid()) curr = headptr;
	}

	void add(int data){
		if(this->valid()){
			Node* temp;
			temp = curr->next;
			curr->next = new Node(data);
			curr->next->next = temp;
			curr = curr->next;
		}
		else{
			headptr = new Node(data);
			curr = headptr;
		}
	}

	void remove(){
		if(this->valid()){
			Node* p = headptr;
			while(p->next != curr){
				p = p->next;
			}
			Node* temp;
			p->next = curr->next;
			temp = curr->next;
			delete curr;
			curr = temp;
		}
	}

	int data(){
		if(this->valid()) return curr->data;
	}

	void next(){
		if(this->valid()){
			curr = curr->next;
		}
	}

	
	
	void display(){
		Node* p = headptr;
		while(p){
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}

private:
	Node* headptr;
	Node* curr;
};


int main() {
  Sequence s;
  for (int i = 0; i < 6; ++i) s.add(i);
  s.display();
  cout << "==========\n";



  Sequence s2 (s);
  s2.display();

  Sequence s3;


   s3 = s;

   s3.display();

   cout << "==================\n";
  s.reset();
  for (int i = 0; i < 3; ++i) s.next();
  s.add(42);
  s.display();
  cout << "==========\n";
  s.reset();
  for (int i = 0; i < 2; ++i) s.next();
  s.remove();
  s.display();
  cout << "==========\n";
  s.clear();
  s.display();
  cout << "==========\n";

  
}