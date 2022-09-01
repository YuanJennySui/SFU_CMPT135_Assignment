// a2.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Yuan Sui (Jenny)
// St.# : 301415307
// Email: jenny_sui@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#include "cmpt_error.h"    // These are the only permitted includes!
#include <iostream>        //
#include <string>          // Don't include anything else.
#include <algorithm>
#include <cassert>

using namespace std;

class str_vec{

    //private variables
private:
    int cap;
    int sz;
    string* arr;

    //public methods
public:

    //default capacity for a string array
    static const int DEFAULT_CAP = 10;

    //default constructor of size 0 and capacity 10
    str_vec()
    :cap(DEFAULT_CAP), sz(0), arr(new string[cap])
    {}

    //constructor of size n, capacity n + 10 and filled with string st
    str_vec(int n, string st)
    {
        //throw error if size is invalid
        if(n<0){
            cmpt::error("size can't be smaller than 0");
        }

        cap = n + DEFAULT_CAP;
        sz = n;
        arr = new string[cap];
        //input string st to each position of the array
        for(int i = 0; i < sz; i++){
            arr[i] = st;
        }
    }

    //copy constructor
    str_vec(const str_vec& other)
    {
        //copy private variables
        cap = other.cap;
        sz = other.sz;
        arr = new string[cap];

        //copy element of the array
        for(int i = 0; i < sz; i++){
            arr[i] = other.arr[i];
        }
    }

    //destructor
    ~str_vec(){
        //delete dynamic array
        delete[] arr;
        //output delete message
        cout << "string vector deleted" << endl;
    }

    //return size
    int size() const {
        return sz;
    }

    //return capacity
    int capacity() const {
        return cap;
    }

    //return the percentage of the array used
    int pct_used() const {
        double percentage = static_cast<double> (sz)/cap * 100;
        return static_cast<int> (percentage);
    }

    //return string of the array
    string to_str() const{
        //if size = 0
        if(sz == 0){
            return "[]";
        }else if(sz == 1) { //if size = 1
            return "[\"" + arr[0] + "\"]";
        }else { //iterate through the array
            string str = "[";
            for (int i = 0; i < sz - 1; i++) {
                str += "\"" + arr[i] + "\", ";
            }
            str += "\"" + arr[sz-1] + "\"]";
            return str;
        }
    }

    //output string to console
    void print() const{
        cout << to_str();
    }

    //output string and next line to console
    void println() const{
        cout << to_str() << endl;
    }

    //return the value of the element at index i
    string get(int i) const{
        //check bound
        if (i < 0 || i >= sz){
            cmpt::error("get: index out of bound");
        }
        return arr[i];
    }

    //change the value of the element at index i to str
    void set(int i, string str){
        //check bound
        if (i < 0 || i >= sz){
            cmpt::error("get: index out of bound");
        }
        arr[i] = str;
    }

    //add an element str to the end of the array
    void append(string str){
        //if size is smaller than capacity
        if(sz < cap){
            arr[sz] = str;
            sz ++;
        } else if(sz >= cap){ //if size is larger or equal to capacity;
            cap *= 2;
            string* copyArr = new string[cap];
            for( int i = 0; i < sz; i++ ){ //iterate through original array to copy original value
                copyArr[i] = arr[i];
            }
            //delete dynamic array
            delete[] arr;
            arr = copyArr;
            arr[sz] = str;
            sz ++;
        }
    }

    //add an element str to the beginning of the array
    void prepend (string str){
        //if the size is smaller than the capacity
        if(sz < cap) {
            string *copyArr = new string[cap];
            copyArr[0] = str;
            for (int i = 0; i < sz; i++) { //add new element and add previous element
                copyArr[i + 1] = arr[i];
            }
            //delete orignal array
            delete[] arr;
            arr = copyArr;
            sz++;
        } else if(sz >= cap){ //if the size is greater or equal to the capacity
            cap *= 2;
            string* copyArr = new string[cap];
            copyArr[0] = str;
            for( int i = 0; i < sz; i++ ){
                copyArr[i+1] = arr[i];
            }
            //delete original array
            delete[] arr;
            arr=copyArr;
            sz ++;
        }
    }

    //reverse the element in the array
    void reverse(){
        for(int i = 0; i <= sz/2 -1; i++){ //iterate up to the half way in the array
            string temp = arr[i];
            arr[i] = arr[sz-i-1];
            arr[sz-i-1] = temp;
        }
    }

    //sort the element in the array in alphabetical order
    void sort(){
        std::sort(arr, arr+sz);
    }

    //set the size of the array to 0
    void clear(){
        sz = 0;
    }

    //set the capacity of the array to equal size
    void shrink_to_fit(){
        //if size doesn't equal to capacity
        if(sz != cap){
            string* copyArr = new string[sz];
            for(int i = 0; i < sz; i++){ //copy all element from original array
                copyArr[i] = arr[i];
            }
            //delete original array
            delete []arr;
            arr = copyArr;
        }
    }
};

//return a bool to indicate whether two str_vec have the same element in the same order
bool operator==(str_vec a, str_vec b){
    //if two str_vec don't have the same size
    if(a.size() != b.size()){
        return false;
    }
    for(int i = 0; i < a.size(); i++){
        //if two element are not the same
        if(a.get(i) != b.get(i)){
            return false;
        }
    }
    return true;
}

//return a bool to indicate whether two str_vec are not equal to each other
bool operator!=(str_vec a, str_vec b){
    if( !(a == b)){
        return true;
    }
    return false;
}

//test make_empty()
void test_default_constructor()
{
    //test with default cap
    str_vec test;
    assert(test.size()==0);
    assert(test.capacity()==10);
}

// test constructor
void test_constructor()
{
    str_vec test(5, "cat");
    assert(test.size() == 5);
    assert(test.capacity() == 15);
    for(int i = 0; i < test.size(); i++){
        assert(test.get(i) == "cat");
    }
}

//test copy constructor
void test_copy_constructor(){
    str_vec test1 (5, "cat");
    str_vec test2 (test1);
    assert(test1 == test2);
}

//test size(), capacity() and pct_used()
void test_getters(){
    str_vec test (5, "cat");
    assert(test.size() == 5);
    assert(test.capacity() == 15);
    assert(test.pct_used() == static_cast<int>(5.0/15*100));
}

//test to_str()
void test_to_str()
{
    //test multiple string
    str_vec test (3, "cat");
    cout << "here";
    //assert(test.to_str()=="[\"cat\", \"cat\", \"cat\"]");

    //test one string
    str_vec test1 (1, "cat");
    assert(test1.to_str()=="[\"cat\"]");

    //test no string
    str_vec test2;
    assert(test2.to_str() == "[]");
}

//test print
void test_print()
{
    str_vec test (3, "cat");
    string s = test.to_str();
    assert(s =="[\"cat\", \"cat\", \"cat\"]");
}

//test println()
void test_println()
{
    str_vec test (3, "cat");
    string s = test.to_str() + "\n";
    assert(s =="[\"cat\", \"cat\", \"cat\"]\n");
}

//test get()
void test_get()
{
    str_vec test (3, "cat");

    assert(test.get(0)=="cat");
    assert(test.get(1)=="cat");
    assert(test.get(2)=="cat");
}

//test set()
void test_set()
{
    str_vec test (3, "cat");
    test.set(1, "dog");

    assert(test.get(0)== "cat");
    assert(test.get(1)=="dog");
    assert(test.get(2)=="cat");
}


//test append()
void test_append()
{
    //test if size = capacity
    str_vec test;
    for(int i = 0; i< 11; i++){
        test.append("cat");
    }
    assert(test.size()==11);
    assert(test.capacity()==20);

    //test if size < capacity
    str_vec test1;
    test1.append("cat");
    assert(test1.size()==1);
    assert(test1.capacity()==10);
}

//test prepend()
void test_prepend()
{
    //test if size = capacity
    str_vec test(3,"cat");
    for(int i = 0; i < 11; i++){
        test.prepend("one");
    }
    assert(test.size()==14);
    assert(test.capacity()==26);

    //test if size < capacity
    str_vec test1(3, "cat");
    test1.prepend("one");
    assert(test1.size()==4);
    assert(test1.capacity()==13);
}

//test reverse()
void test_reverse(){
    str_vec test;
    test.append("d");
    test.append("b");
    test.append("a");
    test.append("c");
    test.reverse();
    assert(test.to_str()=="[\"c\", \"a\", \"b\", \"d\"]");
}

//test sort()
void test_sort(){
    str_vec test;
    test.append("d");
    test.append("b");
    test.append("a");
    test.append("c");
    test.sort();
    assert(test.to_str()=="[\"a\", \"b\", \"c\", \"d\"]");
}

//test clear()
void test_clear()
{
    str_vec test(3, "cat");
    test.clear();
    assert(test.size()==0);
}

//test shrink to fit()
void test_shrink_to_fit()
{
    //test if size = capacity
    str_vec test;
    for(int i = 0; i < 10; i++){
        test.append("cat");
    }
    test.shrink_to_fit();
    assert(test.size()==test.capacity());

    //test if capacity > size
    str_vec test1(3, "cat");
    assert(test.size()==test.capacity());
}

//test operator== and !=
void test_operator()
{
    //test if two str_vec equals
    str_vec test (3, "cat");
    str_vec test1 (3, "cat");
    assert(test == test1);

    //test if two str_vec don't equates
   str_vec test2 (2, "cat");
   str_vec test3;
   assert(test2 != test3);
}

int main() {
    cout << "Assignment 1!\n";
    test_default_constructor();
    test_constructor();
    test_copy_constructor();
    test_getters();
    test_to_str();
    test_print();
    test_println();
    test_get();
    test_set();
    test_append();
    test_prepend();
    test_clear();
    test_shrink_to_fit();
    test_operator();
    test_reverse();
    test_sort();
    //print "success" if all test passed
    cout << "success \n";
}