#include <vector>
struct Node{
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

class Polynomial{
public:
	Polynomial(int deg, std::vector<int>& coeff);
private:
	Node* head;
	int deg;
};Z	
