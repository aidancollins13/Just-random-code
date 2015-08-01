#include <iostream> 
#include <vector>

struct Node{
	Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
	int data;
	Node* next;
};

class Polynomial{
public:
	Polynomial(int deg, vector<int>& coeff) :deg(deg) {
		if(coeff.size() == 0) head = NULL;

		else{
			head = new Node(coeff[coeff.size()-1]);
			node* p = head;
			for(size_t i =coeff.sie()-2; i >= 0; --i){
				p->next = new Node(coeff[i]);
				p = p->next;
			}
		}
	}
private:
	Node* head;
	int deg;
};