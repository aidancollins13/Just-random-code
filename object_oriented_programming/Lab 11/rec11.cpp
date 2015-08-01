#include <cstdlib> // To allow NULL if no other includes
#include <iostream>
using namespace std;
struct Node {
	Node(int data = 0, Node* link = NULL) : data(data), link(link) {}
	int data;
	Node* link;
};

void listInsertHead(int entry, Node*& headPtr) {
	headPtr = new Node(entry, headPtr);
}


void listDisplay(Node* headPtr){
	Node* p = headPtr;
	while(p){
		cout << p->data << " ";
		p = p->link;    //Bump the pointer
	}
	cout << endl;
}

Node* listFindTail(Node* headPtr){
	Node* p = headPtr;
	if(headPtr){
		while(p->link){
			p = p->link;   //Bump the pointer
		}
	}
	return p;
}

Node* listFindNode(Node* headPtr, int entry){
	while(headPtr){
		if(headPtr->data == entry) return headPtr;
		headPtr = headPtr->link;
	}
	return NULL;
	
}

void listAddTail(Node*& headPtr, int data){
	if(!headPtr){
		headPtr= new Node(data);
	}
	else{
		listFindTail(headPtr)->link = new Node(data);
	}
}

void listSplice(Node* headPtr1, int prior, Node*& headPtr2){
	Node* temp = listFindNode(headPtr1, prior)->link;
	listFindNode(headPtr1, prior)->link = headPtr2;
	listFindTail(headPtr2)->link = temp;
}

Node* isSubList(Node* headPtr, Node* subList){
	Node* temp = subList;
	if(listFindNode(headPtr, temp->data)) {
		headPtr = listFindNode(headPtr, temp->data);

		while(headPtr->data == temp->data){
			if(!temp->link) return subList;
			headPtr = headPtr->link;
			temp = temp->link;
		}
	}

	return NULL;
}
int main()
{
	Node* list = new Node(1);
	listInsertHead(9, list);
	listInsertHead(7, list);
	listInsertHead(5, list);
	listDisplay(list);

	Node* temp = new Node(2);
	listInsertHead(3, temp);
	listInsertHead(6, temp);
	listDisplay(temp);
	
	listSplice(list, 7, temp);
	listDisplay(list);

	Node* list2 = new Node(2);
	listInsertHead(3, list2);
	listInsertHead(6, list2);
	listDisplay(list2);


	listDisplay(isSubList(list, list2));

	Node* list3 = new Node(3);
	listInsertHead(2, list3);
	listInsertHead(6, list3);
	listDisplay(list3);

	listDisplay(isSubList(list, list3));

	Node* list4 = new Node(2);
	listInsertHead(3, list4);
	listInsertHead(6, list4);
	listAddTail(list4, 77);
	listAddTail(list4, 77);
	listAddTail(list4, 77);
	listAddTail(list4, 77);
	listAddTail(list4, 77);
	listDisplay(list4);

	listDisplay(isSubList(list, list4));

}
