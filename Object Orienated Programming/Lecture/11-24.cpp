//Recursion
#include "11-10.cpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void recursiveFunction(){
	recursiveFunction();
}

int towersC(int n, char source, char target, char spare){
	if(n == 0) return 0;
	int count = 0;
	count = towersC(n-1, source, spare, target);
	// cout << "Move disk: " << n << " from spindle " << source << " to spindle "
	// << target << endl;	
	++count;
	count += towersC(n-1, spare, target, source);
	return count;

}

int factorial(int n){
	if(n == 1) return 1;
	return n * factorial(n-1);
}

int factorialIterative(int n){
	int total = 1;
	for(int i = n; i < 0; --i){
		total *= i;
	}
	return total;
}

int binarySearch(const vector<int>& v, int target, int low, int high){
	if (low > high) return -1;
	int mid = (low + high)/2;
	if(target == v[mid]) return mid;
	else if(low == high) return -1;
	else if(target < v[mid]) 
		return binarySearch(v, target, low, mid-1);
	else if(target > v[mid]) 
		return binarySearch(v, target, mid+1, high);
}

struct TreeNode{
	TreeNode(int data=0, TreeNode* left = NULL, 
		TreeNode* right = NULL) 
		: data(data), left(left), right(right){}
	int data;
	TreeNode* right, left;
};

int treeSum(TreeNode* root){
	if(!root) return 0;
	return root->data + treeSum(root->right) 
		+ treeSum(root->left);
}
int main(){
	//cout << towersC(200 ,'A', 'B', 'C') << endl;
	cout << factorial(5) << endl;
	vector<int> v = {13, 2, 8, 21, 5, 3, 1};
	// sort(v.begin(), v.end());
	// binarySearch(v, 7, 0, 6);
	
}
