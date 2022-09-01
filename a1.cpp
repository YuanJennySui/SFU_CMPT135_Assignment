// a1.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Yuan Sui
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

#include "a1.h"
#include "cmpt_error.h"
#include <iostream>      // no other #includes are allowed
#include <fstream>       // for this assignment
#include <string>
#include <cassert>

using namespace std;

//returns a new str_array with indicated cap, or a default cap of 10
str_array make_empty(int cap = 10)
{
    str_array emptyArr;
    emptyArr.arr = new string[cap];
    emptyArr.size = 0;
    emptyArr.capacity = cap;

    return emptyArr;
}

//delete the array and set pointer to nullptr
void deallocate(str_array& arr)
{
    delete[] arr.arr;
    arr.arr = nullptr;
}

// Returns the percentage of the array that is in use.
double pct_used(const str_array& arr) {
    double percentage = static_cast<double> (arr.size) / arr.capacity;
    return percentage;
}

// convert arr's underlying array to a string
string to_str(const str_array& arr)
{
    string str = "[";
    //if size of array is equal to 0
    if(arr.size == 0){
        return "[]";
    }
    //iterate through all the element in the array except the last element
    for(int i = 0; i < arr.size-1; i++){
        str += "\"" + arr.arr[i] + "\", ";
    }
    //add the last element of the array
    str += "\"" + arr.arr[arr.size-1] +"\"]";
    return str;
}

// prints to_str(arr) to cout
void print(const str_array& arr)
{
    string str = to_str(arr);
    cout << str;
}

// same as print, but also prints '\n' at the end
void println(const str_array& arr)
{
    string str = to_str(arr);
    cout << str << endl;
}

//return the string at indicated index
string get(const str_array& arr, int i)
{
    if(i < 0 || i >= arr.size){
        cmpt::error("index out of bound");
    }
    return arr.arr[i];
}

//change the string to another indicated string at the indicated index
void set(str_array& arr, int i, const string& s)
{
    if(i < 0 || i >= arr.size){
        cmpt::error("index out of bound");
    }
    arr.arr[i] = s;
}

//add a string to the right of the array
void add_right(str_array& arr, const string& s)
{
    //if size is smaller than the capacity
    if(arr.size < arr.capacity){
        arr.size ++;
        arr.arr[arr.size-1] = s;
    }
    //if size is bigger or equal to the capacity
    if(arr.size >= arr.capacity){
        arr.capacity *= 2;
        string* copyArr = new string[arr.capacity];
        for( int i = 0; i < arr.size; i++ ){
            copyArr[i] = arr.arr[i];
        }
        deallocate(arr);
        arr.arr=copyArr;
        arr.size ++;
        arr.arr[arr.size-1] = s;
    }
}

//returns a bool of whether 2 str_array have equal size and the same element in the same order
bool operator==(str_array a, str_array b)
{
    if(a.size != b.size){
        return false;
    }

    for(int i = 0; i < a.size; i++){
        if (a.arr[i] != b.arr[i]){
            return false;
        }
    }

    return true;
}

//set the size of the array to 0
void clear(str_array& arr)
{
    arr.size = 0;
}

//add a string to the left of the array
void add_left(str_array& arr, const string& s)
{
    //if the size is smaller than the capacity
    if(arr.size < arr.capacity){
        string* copyArr = new string[arr.capacity];
        copyArr[0] = s;
        for(int i = 0; i < arr.size; i++){
            copyArr[i+1] = arr.arr[i];
        }
        deallocate(arr);
        arr.arr = copyArr;
        arr.size ++;
    }
    //if the size is greater or equal to the capacity
    if(arr.size >= arr.capacity){
        arr.capacity *= 2;
        string* copyArr = new string[arr.capacity];
        copyArr[0] = s;
        for( int i = 0; i < arr.size; i++ ){
            copyArr[i+1] = arr.arr[i];
        }
        deallocate(arr);
        arr.arr=copyArr;
        arr.size ++;
    }
}

// make the size and capacity of arr the same; if arr.size is 0,
// new capacity is set to 1; does nothing if arr.size is already
// equal to  arr.capacity
void shrink_to_fit(str_array& arr)
{
    //if the size doesn't equal to capacity
    if(arr.size !=arr.capacity){
        //if the size is equal to 0
        if(arr.size == 0){
            string* copyArr = new string[1];
            deallocate(arr);
            arr.arr = copyArr;
            arr.capacity = 1;
        }else {
            string *copyArr = new string[arr.size];
            for (int i = 0; i < arr.size; i++) {
                copyArr[i] = arr.arr[i];
            }
            deallocate(arr);
            arr.capacity = arr.size;
            arr.arr = copyArr;
        }
    }
}

//test make_empty()
void test_make_empty()
{
    //test with default cap
    str_array test;
    test = make_empty();
    assert(test.size==0);
    assert(test.capacity==10);
    deallocate(test);

    //test with indicated cap of 50
    test = make_empty(50);
    assert(test.size==0);
    assert(test.capacity==50);
    deallocate(test);
}

void test_deallocate()
{
    str_array test;
    test = make_empty();
    deallocate(test);
    assert(test.arr==nullptr);
}

//test pct_used()
void test_pct_used()
{
    string* ptest = new string[4];
    ptest[0] = "hello";
    ptest[1] = "world";
    str_array test = {ptest, 2, 4};

    assert(pct_used(test)==0.5);
    deallocate(test);
}

//test to_str()
void test_to_str()
{
    //test multiple string
    string* ptest = new string[3];
    ptest[0] = "owl";
    ptest[1] = "bug";
    ptest[2] = "cow";
    str_array test = {ptest, 3, 3};

    assert(to_str(test)=="[\"owl\", \"bug\", \"cow\"]");
    deallocate(test);

    //test one string
    string* ptest2 = new string[1];
    ptest2[0] = "hello";
    str_array test2 = {ptest2,1,1};

    assert(to_str(test2)=="[\"hello\"]");
    deallocate(test2);

    //test no string
    string* ptest3 = new string[1];
    str_array test3 = {ptest3,0,1};

    assert(to_str(test3)=="[]");
    deallocate(test3);
}

//test print
void test_print()
{
    string* ptest = new string[3];
    ptest[0] = "owl";
    ptest[1] = "bug";
    ptest[2] = "cow";
    str_array test = {ptest, 3, 3};
    string str = to_str(test);

    assert(str =="[\"owl\", \"bug\", \"cow\"]");
    deallocate(test);
}

//test println()
void test_println()
{
    string* ptest = new string[3];
    ptest[0] = "owl";
    ptest[1] = "bug";
    ptest[2] = "cow";
    str_array test = {ptest, 3, 3};
    string str = to_str(test);
    str += "\n";

    assert(str =="[\"owl\", \"bug\", \"cow\"]\n");
    deallocate(test);
}

//test get()
void test_get()
{
    string* ptest = new string[3];
    ptest[0] = "owl";
    ptest[1] = "bug";
    ptest[2] = "cow";
    str_array test = {ptest, 3, 3};

    assert(get(test,0)=="owl");
    assert(get(test,1)=="bug");
    assert(get(test,2)=="cow");
    deallocate(test);
}

//test set()
void test_set()
{
    string* ptest = new string[3];
    ptest[0] = "owl";
    ptest[1] = "bug";
    ptest[2] = "cow";
    str_array test = {ptest, 3, 3};

    set(test,0,"hello");
    set(test,1,"world");
    assert(test.arr[0]=="hello");
    assert(test.arr[1]=="world");
    assert(test.arr[2]=="cow");
    deallocate(test);
}

//test add_right()
void test_add_right()
{
    //test if size = capacity
    string* ptest = new string[3];
    ptest[0] = "owl";
    ptest[1] = "bug";
    ptest[2] = "cow";
    str_array test = {ptest, 3, 3};

    add_right(test,"chocolate");
    assert(test.capacity==6);
    assert(test.size==4);
    assert(test.arr[3]=="chocolate");
    deallocate(test);

    //test if size < capacity
    string* ptest2 = new string[3];
    ptest2[0] = "hello";
    str_array test2 = {ptest2,1,3};

    add_right(test2,"world");
    assert(test2.capacity==3);
    assert(test2.size==2);
    assert(test2.arr[1]=="world");
    deallocate(test2);
}

void test_operator()
{
    //test if two str_array equals
    string* ptest = new string[3];
    ptest[0] = "hello";
    ptest[1] = "world";
    str_array test = {ptest,2,3};

    string* ptest2 = new string[3];
    ptest2[0] = "hello";
    ptest2[1] = "world";
    str_array test2 = {ptest2,2,3};

    assert(test==test2);
    deallocate(test);
    deallocate(test2);

    //test if two str_array don't equates
    string* ptest3 = new string[3];
    ptest3[0] = "hello";
    ptest3[1] = "world";
    str_array test3 = {ptest3,2,3};

    string* ptest4 = new string[3];
    ptest4[0] = "hello";
    ptest4[1] = "chocolate";
    str_array test4 = {ptest4,2,3};

    assert(!(test3==test4));
    deallocate(test3);
    deallocate(test4);
}

//test clear()
void test_clear()
{
    string* ptest = new string[3];
    ptest[0] = "hello";
    ptest[1] = "world";
    str_array test = {ptest,2,3};

    clear(test);

    assert(test.size==0);
    deallocate(test);
}

//test add_left()
void test_add_left()
{
    //test if size = capacity
    string* ptest = new string[3];
    ptest[0] = "owl";
    ptest[1] = "bug";
    ptest[2] = "cow";
    str_array test = {ptest, 3, 3};

    add_left(test,"chocolate");
    assert(test.capacity==6);
    assert(test.size==4);
    assert(test.arr[3]=="cow");
    assert(test.arr[0]=="chocolate");
    deallocate(test);

    //test if size < capacity
    string* ptest2 = new string[3];
    ptest2[0] = "hello";
    str_array test2 = {ptest2,1,3};

    add_left(test2,"world");
    assert(test2.capacity==3);
    assert(test2.size==2);
    assert(test2.arr[0]=="world");
    assert(test2.arr[1]=="hello");
    deallocate(test2);
}

//test shrink to fit()
void test_shrink_to_fit()
{
    //test if size = capacity
    string* ptest = new string[3];
    ptest[0] = "owl";
    ptest[1] = "bug";
    ptest[2] = "cow";
    str_array test = {ptest, 3, 3};

    shrink_to_fit(test);
    assert(test.size==test.capacity);
    deallocate(test);

    //test if capacity > size
    string* ptest2 = new string[3];
    ptest2[0] = "hello";
    str_array test2 = {ptest2,1,3};

    shrink_to_fit(test2);
    assert(test2.size==test2.capacity);
    deallocate(test2);

    //test if size = 0
    string* ptest3 = new string[3];
    str_array test3 = {ptest3,0,3};

    shrink_to_fit(test3);
    assert(test3.size==0);
    assert(test3.capacity==1);
    deallocate(test3);
}

int main() {
    cout << "Assignment 1!\n";
    test_make_empty();
    test_deallocate();
    test_pct_used();
    test_to_str();
    test_print();
    test_println();
    test_get();
    test_set();
    test_add_right();
    test_operator();
    test_clear();
    test_add_left();
    test_shrink_to_fit();
    //print "success" if all test passed
    cout << "success \n";
}

