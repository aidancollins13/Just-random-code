//Aidan Collins 
//hw05
//4/8/15
#include<string>
#include<iostream>
using namespace std;

template<class Object>
class LList;

template<class Object>
class LListItr;

template<class Object>
class LListNode
{

    LListNode(const Object & element = Object(), LListNode * n = nullptr ):element( element ),next( n ){}

    
    Object element;
    LListNode * next;
    
    friend class LList<Object>;
    friend class LListItr<Object>;

};

template<class Object>
class LListItr
{
public:
    LListItr():current(nullptr){}
    
    LListItr  & operator++(){
	current = current->next;
	return *this;
    }
    LListItr  operator++(int){
    	LListItr temp = current;
	current = current->next;
	return temp;
    }
    
    bool operator==(const LListItr & rhs){
    	return (this->current == rhs.current);
    }
    bool operator!=(const LListItr & rhs){
	return (this->current != rhs.current);
    }
    
    Object & operator*(){
    	return current->element;
    }

private:
    LListItr ( LListNode<Object> * p ):current( p ){}

    LListNode<Object> * current;
    
    friend class LList<Object>;
};

template<class Object>
class LList
{
public:
    typedef LListItr<Object> iterator; // I added this typedef
    
    LList ( ):header( new LListNode<Object>() ),Size(0){ }
    
  // Using the STL method names for the methods above
    LListItr<Object> before_begin()
    { return LListItr<Object>( header ); }
    LListItr<Object> begin()
    { return LListItr<Object>( header->next ); }
    LListItr<Object> end()
    { return LListItr<Object>( LListItr<Object>( nullptr ) ); }
    
    void push_front( const Object & x );
    
    bool empty() { return header->next == nullptr; }
    
    int size();
    
    void pop_front();

    void remove( const Object & x );

    void remove_last(const Object & x);

    template<class Predicate>// This is how you create a template method within a class
    void remove_if( Predicate pred );

    LListItr<Object> erase_after( LListItr<Object> itr );
 

    
private:
    LListNode<Object> * header;
    int Size;
};

template <class Object>
void LList<Object>::push_front(const Object & x){
	header->next = new LListNode<Object>(x,header->next); 
	Size++;
}

template <class Object>
void LList<Object>::pop_front(){
	if(header->next){
		LListNode<Object> * oldNode = header->next;
		header->next = header->next->next;
		delete oldNode;
		Size--;
	}
}

template <class Object>
int LList<Object>::size(){
	return Size;
}

template <class Object>
LListItr<Object> LList<Object>::erase_after( LListItr<Object> itr ){	
	if((itr.current->next != nullptr)){
		LListNode<Object> * temp = itr.current->next;
		itr.current->next = itr.current->next->next;
		delete temp;
		Size--;
	}
}

template <class Object>
void LList<Object>::remove_last(const Object & x)
{
    	LListNode<Object> *result = nullptr;
	for(LListNode<Object> *p = header; p->next != nullptr; p = p->next){
		if(p->next->element == x)
		    result = p;
	}
	if(result != nullptr){
		LListNode<Object> *oldNode = result->next;
		result->next = result->next->next;
		delete oldNode;
		Size--;
	}
}

template<class Object> template< class Predicate> /* The signature for when you define the template method outside the class*/
void LList<Object>::remove_if( Predicate pred)
{
	for(LListItr<Object> begin = begin(); begin != end(); ++begin){
		if(pred(begin.node->next->element))
			erase_after(begin);
	}

}
int main(){

    LList<int> list;
    list.push_front(3);
    list.push_front(2);
    list.push_front(1); 

    for(LListItr<int> itr = list.begin(); itr != list.end(); ++itr)
	cout << *itr << endl;
    cout << list.size()<< endl;
    cout << "===============\n";
    cout << (list.begin() == list.end()) << " , " << (list.begin() != list.end()) << endl;
    cout << "===============\n";
 
    list.pop_front();

    for(LListItr<int> itr = list.begin(); itr != list.end(); ++itr)
	cout << *itr << endl;
    cout << list.size()<< endl;
    cout << "===============\n";

    list.push_front(3);
    list.remove_last(3);
    
    for(LListItr<int> itr = list.begin(); itr != list.end(); itr++)
	cout << *itr << endl;
    cout << "===============\n";


    list.erase_after(list.begin());

    for(LListItr<int> itr = list.begin(); itr != list.end(); ++itr)
	cout << *itr << endl;
} 
