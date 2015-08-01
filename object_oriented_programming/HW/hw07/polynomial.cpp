#include "polynomial.h"
using namespace std;

Polynomial::Polynomial(int deg, vector<int>& coeff) :deg(deg) {
		if(coeff.size() == 0) head = nullptr;

		else{
			head = new Node(coeff[coeff.size()-1]);
			Node* p = head;
			for(size_t i = coeff.size()-2; i >= 0; --i){
				p->next = new Node(coeff[i]);
				p = p->next;
			}
		}
	}

int main(){
	vector<int> v;
	v.push_back(2);
	v.push_back(4);


	Polynomial p(2, v);
}