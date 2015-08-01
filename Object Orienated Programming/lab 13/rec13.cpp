//44-5-14
#include <iostream>
#include <climits>
using namespace std;

struct Node{
	Node(int data = 0, Node* next = NULL) : data(data), next(next) {}
	int data;
	Node* next;
};

void listDisplay(Node* headPtr){
	Node* p = headPtr;
	while(p){
		cout << p->data << " ";
		p = p->next;    //Bump the pointer
	}
	cout << endl;
}


struct TNode {
  TNode(int data = 0, TNode *left = NULL, TNode *right = NULL)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
	if(!root) return INT_MIN;
	int maxValue = INT_MIN;
	if(root->data > maxValue) maxValue = root->data;
	if(max(root->left) > maxValue) maxValue = max(root->left); 
	if(max(root->right) > maxValue) maxValue = max(root->right);
	return maxValue;
}

int tSum(TNode* root){
	if(!root) return 0;
	return root->data + tSum(root->right) + tSum(root->left);
}

int intToBin(int n){
	if(n < 2) cout <<n;

	else{
		intToBin(n/2);
		cout << n%2;
	}
}

Node* listSum(Node*& list1, Node*& list2){
	if(!list1) return NULL;

	return new Node(list1->data + list2->data, listSum(list1->next,list2->next));
}

Node* copy(Node* headPtr){
	if(!headPtr) return NULL;

	return new Node(headPtr->data, copy(headPtr->next));
}

int cstringSum(char* c){
	if(c[0] == '\0') return 0;

	return c[0] + cstringSum(c+1);

}	

int binaraySearch(char* array, char target, int begin, int end){
	if(begin >= end) return -1;
	if(array[(begin+end)/2] == target) return(begin+end)/2;
	else if(array[(begin+end)/2] >  target) return binaraySearch( array, target, begin, (begin+end)/2);
	else if(array[(begin+end)/2] < target) return binaraySearch(array, target, (begin+end)/2, end);

	
}

int main(){
	//intToBin(8);
	//cout << endl;

	Node* list = new Node(2);
	Node* list2 = new Node(1);

	list->next = new Node(5);
	list2->next = new Node(2);
	listDisplay(list);
	listDisplay(list2);

	Node* list3 = copy(list);
	listDisplay(list3);

  TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(5, &d, &e);
   cout << tSum(&f) << endl;

	// char cstring[4] = "abc";
	// cout << cstringSum(cstring) << endl;

	// char q[6] = "abcde";
	// cout << binaraySearch(q, 'b', 0,6 ) << endl;
}