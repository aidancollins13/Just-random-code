// CS2134 Spring 2015
// Homework 4 Programming Solution
// Please do not reproduce this material.

// You MUST pick "Q1" Q2" "Q3" "Q4" Q6" OR "Q7"
// Q5 was extra credit and its solution is not included
#define Q2

/**************************************************
** QUESTION 1 - DONE                             **
***************************************************/

//Note: code from previous HW needed to compile Q1 code! 

#ifdef Q1
#include <iostream>
#include <limits>
using namespace std;

template <class ForwardItr, class Functor>
ForwardItr select_item(ForwardItr start, ForwardItr end, Functor pred){
    ForwardItr tmp_itr = end;
    for ( ; start != end; start++) {
        if (pred(*start)) tmp_itr = start;
    }
    return tmp_itr;
}

class closest_stop {
public:
    closest_stop (double lon, double lat) :
        longitude(lon), latitude(lat), 
        shortest_dist(numeric_limits<double>::max()) {}

    /* You need train_stop_data and haverdist included for this to compile
    bool operator() (train_stop_data stop){
        double dist = haverdist(latitude, longitude, stop.get_latitude(), stop.get_longitude());
        if (dist < shortest_dist){
            shortest_dist = newDist;
            return true;
        }
        return false;
    }
    */

private:
    double longitude;
    double latitude;
    double shortest_dist;
};

int main() {
}
#endif

/**************************************************
** QUESTION 2 - DONE                             **
***************************************************/

#ifdef Q2
#include <iostream>
using namespace std;

template <class Object>
Object sumOriginal(Object x, int n) {
    Object tmp = Object();
    for ( ; n > 0; --n, ++x ) {
        tmp = tmp + x;
        cout << tmp << ", ";
    }
    return tmp;
}

// One potential approach, using a driver function
// to get around using 2 parameters for the recursive function

template<class Object>
Object summation (Object x, Object y, int n) {
    cout << x << ", ";
    if (n < 2) return x;
    return summation(x+y,y+1,n-1);
}

template<class Object>
Object summation (Object x, int n) {
    if (n < 1) return x;
    Object y = x;
    return summation(x,y+1,n);
}

int main() {
    int y = 4;
    int z = 8;

    cout << "Original Function:\n";
    int x = sumOriginal(y, z);
    cout << endl;
    cout << "Returns: " << x << endl;

    cout << "\nRecursive Function:\n";
    x = summation(y, z);
    cout << endl;
    cout << "Returns: " << x << endl;
}
#endif

/**************************************************
** QUESTION 3 - DONE                             **
***************************************************/

#ifdef Q3
#include <iostream>
using namespace std;

void recPattern (int n) {
    if (n < 1) return;
    recPattern(n-1);
    cout << " " << n;
    recPattern(n-1);
}

int main(){
    for (int i = 0; i < 6; i++) {
        cout << "The output if n=" << i << " is:";
        recPattern(i);
        cout << endl;
    }
}
#endif

/**************************************************
** QUESTION 4 - DONE                             **
***************************************************/

#ifdef Q4
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;


template<class Object>
Object sumVector (typename vector<Object>::const_iterator begin, typename vector<Object>::const_iterator end) {
    if (begin == end-1) return *begin;
    int middle = (end-begin)/2;
    typename vector<Object>::const_iterator mid = begin + middle;
    return sumVector<Object>(begin, mid) + sumVector<Object>(mid, end);
}

template<class Object>
Object sumVector (const vector<Object>& a) {
    if (!a.size()) return 0;
    typename vector<Object>::const_iterator begin = a.begin();
    typename vector<Object>::const_iterator end = a.end();
    return sumVector<Object>(begin, end);
}

int main() {
    vector<int> vec;
    vec.push_back(-21);
    vec.push_back(31);
    vec.push_back(14);
    vec.push_back(1);
    vec.push_back(-20);
    int sum = sumVector(vec);
    cout << "The sum is: " << sum << endl;
}
#endif

/**************************************************
** QUESTION 6 - DONE                             **
***************************************************/

#ifdef Q6

// You need to enable C++11 to run this question
// (It's just for initializing the vector and printing it)

#include <iostream>
#include <vector>
using namespace std;

template<class RandItr>
void mergeSort(RandItr tmp, RandItr start, RandItr end) {
    if(end-start == 1) return;
    RandItr mid = start + (end-start)/2;
    int sz = end-start;

    // Sort the two sides first
    mergeSort(tmp, start, mid);
    mergeSort(tmp+sz/2, mid, end);
    
    // Then merge the sorted sides
    merge(start, mid, mid, end, tmp);

    // Important: You must copy the sorted result (tmp) into the original vector
    copy(tmp, tmp+sz, start);
    /* Or, a loop could've been used to copy the vectors:
    RandItr cur = start;
    while(cur != end)
    {
        *cur = *tmp;
        tmp++;
        cur++;
    }
    */
}

template <class RandItr>
void mergeSort( RandItr start, RandItr end ) {
    int sz = end-start; // or use auto sz = end-start;
    typedef typename iterator_traits<RandItr>::value_type Object;
    vector<Object> tmp(sz);
    mergeSort(tmp.begin(), start, end);
}

int main() {
    vector<int> test {3,6,5,89,-10};
    cout << "Unsorted: ";
    for (int a : test) cout << a << " ";
    cout << endl << "Sorted:   ";
    mergeSort(test.begin(), test.end());
    for (int a : test) cout << a << " ";
    cout << endl;
}

#endif

/**************************************************
** QUESTION 7 - DONE                             **
***************************************************/

#ifdef Q7

#include <iostream>
#include <vector>
#include <algorithm>
// If you're using C++11, you need the below include
#include <utility>
using namespace std;

class Student {
public:
    Student (const string& who) : name(who) {}
    string getName () const { return name; }
private:
    string name;
};

ostream& operator<<(ostream& os, const Student& person) {
    os << "Name: " << person.getName() << endl;
    return os;
}

class meFirst {
public:
    meFirst(const string& me) : me(me) {}
    bool operator() (Student left, Student right) {
        if(left.getName() == me) return true;
        if(right.getName() == me) return false;
        else return (left.getName() <= right.getName());
    }
private:
    string me;
};

int main() {
    vector<Student> classList;
    classList.push_back(Student("Squire"));
    classList.push_back(Student("Page"));
    classList.push_back(Student("Lee"));
    classList.push_back(Student("Malone"));
    classList.push_back(Student("Wooten"));
    classList.push_back(Student("Wells"));
    classList.push_back(Student("Burton"));
    classList.push_back(Student("Pastorius"));
    classList.push_back(Student("Jones"));
    classList.push_back(Student("Claypool"));
    classList.push_back(Student("McCartney"));


    cout << "----- Unsorted: -----\n";
    for (int i = 0; i < classList.size(); i++)
        cout << "Name: " << classList[i].getName() << endl;

    meFirst m = meFirst("Wells");
    sort(classList.begin(), classList.end(), m);
    
    cout << "\n----- 'Sorted': -----\n";
    for (int i = 0; i < classList.size(); i++)
        cout << "Name: " << classList[i].getName() << endl;

    cout << "\nDo you see how the list has changed?\n\n";
}

#endif