/* 
 
 * Author: aidan
 *
 * Created on April 25, 2015, 10:39 AM
 */

#include <cstdlib>
#include<map>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<list>
#include <algorithm> 

using namespace std;

template< class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
    Comparable  element;
    BinaryNode *left;
    BinaryNode *right;
    int size;
    
    BinaryNode( const Comparable & theElement, BinaryNode *lt,
               BinaryNode *rt, int sz = 1 )
    : element( theElement ), left( lt ), right( rt ), size( sz ) { }
    
    friend class BinarySearchTree<Comparable>;
};
template <class Comparable>
class BinarySearchTree
{
public:
    typedef BinaryNode<Comparable> Node;
    
    BinarySearchTree( ) : root( NULL ) { } // Construct the tree.
    ~BinarySearchTree( ){ makeEmpty( ); } // Destructor for the tree.
    

    // add function declarations
    
    
    bool isEmpty( ) const { return root == NULL;}
    void makeEmpty( ) { makeEmpty( root ); }
    void insert( const Comparable & x ) { insert( x, root ); }
    const Comparable * find(const Comparable & x) 
        {return elementAt(find(x,root));} 
    void printBetween(const Comparable & low, const Comparable & high) const {
        printBetween( low, high, root);
    }
    void negateTree() {
        negateTree(root);
    }
    int CountNodesWithOneChild() const {
        return CoutnNodesWithOneChild(root);
    }
    int average_node_depth() const {
        return (depth(root->left) + depth(root->right))/root->size;
    }
    
private:
    Node * root;

    // add function declarations
    
    int treeSize( Node *t ) const { return t == NULL ? 0 : t->size; }
    Comparable const * elementAt( Node *t ) const;
    void insert( const Comparable & x, Node * & t );
    void makeEmpty( Node * & t ) const;
    Node * clone( Node *t ) const;
    Node * find(const Comparable & x, Node *t ) const ;
    void printBetween(const Comparable & low, const Comparable & high, Node * t) const{
        if(t != nullptr){
            if(t->element > high)
                printBetween(low,high,t->left);
            else if(t->element < low )
                printBetween(low,high,t->right);
            else {
                cout << t->element << " ";
                printBetween(low,high,t->right);
                printBetween(low,high,t->left);
            }
        }
    }
    void negateTree(Node * t){
        if( t != nullptr){
            t -> element = -t->element;
            Node * temp = t -> right;
            t -> right = t-> left;
            t -> left = temp;
            negateTree(t->right);
            negateTree(t->left);
        }
    }
    int CountNodesWithOneChild(Node * t){
        if(t == nullptr) return 0;
        else if (t-> left == nullptr && t->right !=nullptr)
            return 1 + CountNodesWithOneChild(right);
        else if(t->right == nullptr && t->left != nullptr)
            return 1 + CountNodesWithOneChild(left);
        else
            return CountNodesWithOneChild(left) + CountNodesWithOneChild(right);
    }
  
    int depth(Node*t){
        if(t == nullptr) return 0;
        return (1 + depth(t->right) + depth(t->left));
    }
    
};

template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::find(const Comparable & x, BinaryNode<Comparable> *t)const{
    while(t!=nullptr){
        if( x < t->element)
            t = t->left;
        else if(t->element < x)
            t = t->right;
        else 
            return t;
    }
    
    return nullptr;
}

template <class Comparable>
Comparable const * BinarySearchTree<Comparable>::elementAt( Node *t ) const
{
    if( t == NULL )
        return NULL;
    else
        return &(t->element);
}



template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x, Node * & t )
{
    if( t == NULL )
        t = new Node( x, NULL, NULL, 0 );
    else if( x < t->element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );
    else
        throw exception( );
    
    t->size++;
}



template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( Node * & t ) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
        t = NULL;
    }
    
}



int main() {
    map<string,int> stopMap;
    
    vector<string> int_to_stop_id;
    
    ifstream stopFile("MTA_train_stop_data.txt");
    if (!stopFile) {
    	cerr << "The file for train stop data cannot be found.\n";
    	exit(1);
    }
    string id;        
    string line;
    getline(stopFile, line);	
    int i =0;
    while (getline(stopFile, line)){
        id = line.substr(0,3);
        if(stopMap.find(id) == stopMap.end()){
            stopMap.insert(pair<string,int>(id,i));
            int_to_stop_id.push_back(id);
            i++;           
        }

    }

vector<list<int> > adjacent(stopMap.size());  
ifstream file("transfers.txt");
string sID;
string transfer;
int idNum;
getline(file,line);
while(getline(file,line)){
    sID = line.substr(0,3);
    transfer = line.substr(4,3);
    idNum = stopMap[sID];
    if(transfer != sID)
        adjacent[idNum].push_front(stopMap[transfer]);
    if(stopMap.find(int_to_stop_id[idNum+1]) != stopMap.end())
        adjacent[idNum].push_front(idNum+1);
    if(idNum > 0 && stopMap.find(int_to_stop_id[idNum-1]) != stopMap.end())
        adjacent[idNum].push_front(idNum-1);
    
}

}
