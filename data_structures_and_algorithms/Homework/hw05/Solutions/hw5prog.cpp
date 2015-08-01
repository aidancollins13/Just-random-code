/**********************************
* HOMEWORK 5 PROGRAMMING PORTION *
***********************************/


/**********************************
PROGRAMMING QUESTION 1
***********************************/

/** Given code from simplelist.txt -- Note: we modified it a bit **/

#include <exception>
#include <iostream>
#include <stack>
using namespace std;

//This is a simplification of the exception class.  In a real implementation 
//care would be taken to return the right error message.
template <class Object>
class LList;     // Incomplete declaration.
template <class Object>
class LListItr;  // Incomplete declaration.

// LListNode class
template <class Object>
class LListNode {
    LListNode( const Object & theElement = Object( ), LListNode * n = nullptr )
    : element( theElement ), next( n ) { }
    Object     element;
    LListNode *next;
    friend class LList<Object>;
    friend class LListItr<Object>;
};


// LList class
template <class Object>
class LList {
public:
		typedef LListItr<Object> iterator; // I added this typedef
    LList( ) ;
    ~LList( );
    bool isEmpty( ) const;
    void makeEmpty( );
    LListItr<Object> first( ) const;
    LListItr<Object> zeroth( ) const;
    void remove( const Object & x);
    void insert( const Object & x, const LListItr<Object> & p );
    void push_front( const Object& x );
    void pop_front();
    int size() const;
		void remove_last(const Object & x);
    template<class Predicate>// This is how you create a template method within a class
    void remove_if( Predicate pred );

    LListItr<Object> erase_after( LListItr<Object> itr );
    
    LListNode<Object>* findPrevious(const Object& x){
    	LListNode<Object> *t = header;
    	while(t->next && (t->next)->element != x){ t = t->next;}
    	if(t->next == nullptr) return nullptr;
    	return t;
    }
	
private:
    LListNode<Object> *header;
    int listSize;           /** ADDED AS PART OF THE SOLUTIONS **/

		bool remove_last(const Object & x, LListNode<Object>* ptr);
};
// LListItr class
template <class Object>
class LListItr {
public:
    LListItr( ) : current( nullptr ) { }
    LListItr<Object>   operator++();
    LListItr<Object>  operator++(int);
    
    Object & operator*( ) const;
    bool operator==(LListItr<Object> rhs) const;
    bool operator!=(LListItr<Object> rhs) const;
    bool isPastEnd( ) const { return current == nullptr; }
private:
    LListNode<Object> *current;    // Current position
    LListItr( LListNode<Object> *theNode )
    : current( theNode ) { }
    friend class LList<Object>; // Grant access to constructor
};

// Construct the list.
template <class Object>
LList<Object>::LList( ) : listSize(0) {
    header = new LListNode<Object>;
}

// Destructor.
template <class Object>
LList<Object>::~LList( ) {
    makeEmpty( );
    delete header;
}

// Test if the list is logically empty.
// Return true if empty, false, otherwise.
template <class Object>
bool LList<Object>::isEmpty( ) const {
    return header->next == nullptr;
}

// Make the list logically empty.
template <class Object>
void LList<Object>::makeEmpty( ) {
    while( !isEmpty( ) )
        remove( *first( ) );
}

// Return an iterator representing the header node.
template <class Object>
LListItr<Object> LList<Object>::zeroth( ) const {
    return LListItr<Object>( header );
}

// Return an iterator representing the first node in the list.
// This operation is valid for empty lists.
template <class Object>
LListItr<Object> LList<Object>::first( ) const {
    return LListItr<Object>( header->next );
}

// Insert item x after p.
template <class Object>
void LList<Object>::insert( const Object & x, const LListItr<Object> & p ) {
    if( p.current != nullptr ) {
        p.current->next = new LListNode<Object>( x, p.current->next );
    }
}

// Remove the first occurrence of an item x.
template <class Object>
void LList<Object>::remove( const Object & x ) {
    LListNode<Object> *p = findPrevious( x );
    if( p->next != nullptr ) {
        LListNode<Object> *oldNode = p->next;
        p->next = p->next->next;  // Bypass deleted node
        delete oldNode;
    }
}

/********************
 *	LList Methods	*
 *******************/

template <class Object>
void LList<Object>::push_front( const Object& x ) {
	header->next = new LListNode<Object>(x, header->next);
	// Note that listSize is a private member variable ADDED to the LList class
	listSize++;
}

template <class Object>
void LList<Object>::pop_front() {
	if(header->next != nullptr) {
		LListNode<Object>* tmp = header->next;
		header->next = header->next->next;
		delete tmp;
		// Note that listSize is a private member variable ADDED to the LList class
		listSize--;
	}
}

template <class Object>
int LList<Object>::size() const {
    // Note that listSize is a private member variable ADDED to the LList class
	return listSize;
}

template <class Object>
LListItr<Object> LList<Object>::erase_after(LListItr<Object> position){
	if(!position.current || !position.current->next)
		return LListItr<Object>();

	LListItr<Object> erasee = position.current->next;
	position.current->next = erasee.current->next;
	delete erasee.current;
	listSize--;
	return LListItr<Object>(position.current->next);
}

template<class Object> template< class Predicate> 
void LList<Object>::remove_if( Predicate pred){
	LListItr<Object> runner = zeroth(); 
	while(runner.current->next){
		if(pred(runner.current->next->element))
			erase_after(runner);
		else ++runner;			
	}
}


template <class Object>
bool LList<Object>::remove_last(const Object & x, LListNode<Object>* ptr){
		if(!ptr->next) 
			return false;
		
		if(remove_last(x, ptr->next))
			return true;
			
		if(ptr->next->element == x){
			erase_after(LListItr<Object>(ptr));
			return true;
		}
		
		return false;
}

template <class Object>
void LList<Object>::remove_last(const Object & x){
	remove_last(x, header);
}



/************************
 *	LListItr Methods	*
 ***********************/

//++itr
template<class Object>
LListItr<Object> LListItr<Object>::operator++( ) {
	if(current != nullptr)
		current = current->next;
	return *this;
}

//itr++
template<class Object>
LListItr<Object> LListItr<Object>::operator++( int ) {
	
	LListItr<Object> oldValue;
	oldValue = current;
	if(current != nullptr)
		current = current->next;
	return oldValue;
}


template<class Object>
Object& LListItr<Object>::operator*( ) const {
	if(current != nullptr)
		return current->element;
	cerr << "Cannot dereference a NULL pointer!\n";
}

template<class Object>
bool LListItr<Object>::operator==(LListItr<Object> rhs) const {
	return current == rhs.current;
}

template<class Object>
bool LListItr<Object>::operator!=(LListItr<Object> rhs) const {
	return !(*this==rhs);
}




int main(){}

