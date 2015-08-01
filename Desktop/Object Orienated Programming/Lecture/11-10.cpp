#include <iostream>
#include <string>
using namespace std;

/*	class Node{
	public:
		Node(int data = 0, Node* next = nullprt) : data(data), next(next){}
		int getData() const {return data;}
		void setData(int data){this->data = data;}
		Node* getNext() const {return next;}
		void setNext(Node* node) {this->next = next;}
	private:
		int data;
		Node* next;
}
*/

struct Node{
	Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
	int data;
	Node* next;
};

/*
	display
	length
	insert
	remove 
	search
	clear
	duplicate 
	getAt
*/

void listDisplay(Node* headPtr){
	Node* p = headPtr;
	while(p){
		cout << p->data << " ";
		p = p->next;    //Bump the pointer
	}
	cout << endl;
}

int listLength(Node* headPtr){
	Node* p = headPtr;
	int count = 0;
	while(p){
		++count;
		p = p->next;   //Bump the pointer
	}
	return count;
}

Node* listFindTail(Node* headPtr){
	Node* p = headPtr;
	if(headPtr){
		while(p->next){
			p = p->next;   //Bump the pointer
		}
	}
	return p;
}

void listAddTail(Node*& headPtr, int data){
	if(!headPtr){
		headPtr= new Node(data);
	}
	else{
		listFindTail(headPtr)->next = new Node(data);
	}
}

void listAddHead(Node*& headPtr, int data){
	headPtr = new Node(data, headPtr);
}

void listAdd(Node* prior, int data){
	 prior->next = new Node(data, prior->next);
}

void listRemoveHead(Node*& headPtr){
	if(headPtr){
		Node* temp = headPtr->next;
		delete headPtr;
		headPtr = temp;
	}
}

void listRemove(Node* prior){
	if(!prior || !prior->next) return;
	Node* theOneAfter = prior->next->next;
	delete prior->next;
	prior->next = theOneAfter;
}

void listRemoveTail(Node*& headPtr){
	if(!headPtr) return;
	if(!headPtr->next) {
		delete headPtr;
		headPtr = NULL;
	Node* p = headPtr;
	while(p->next->next){
		p = p->next;
	}
	delete p->next;
	p->next = NULL;
}
}

Node* listDuplicate(Node* headPtr){
	if(headPtr == NULL) return headPtr;
	Node* p = headPtr->next;
	Node* result = new Node(headPtr->data);
	Node* last = result;
	while(p){
		last->next = new Node(p->data);
		p = p->next;
		last = last->next;
	}
	return result;
}


void listClear(Node*& headPtr){
	while(headPtr) listRemoveHead(headPtr);
}

