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

// a4.cpp

#include "a4.h"  // no other includes are allowed!

using namespace std;

//function to calculate the sum of first n squares
int sum_of_squares(int n){
    //check pre-condition
    assert(0 <= n);
    //base case
    if(n==0){
        return 0;
    } else {
        //recursion
        return n*n + sum_of_squares(n-1);
    }
}

//test for sum_of_squares()
void sum_of_squares_test(){
    assert(sum_of_squares(0)==0);
    assert(sum_of_squares(1)==1);
    assert(sum_of_squares(2)==5);
    assert(sum_of_squares(3)==14);
    assert(sum_of_squares(4)==30);
    assert(sum_of_squares(5)==55);
}

//function that returns the count of the number of numbers from 1 to n (inclusive)
//that are multiple of 3 but not multiples of 5.
int sum_strange(int n){
    //check pre-condition
    assert( 0 < n);
    //base case
    if(n==1){
        return 0;
    } else if((n%3==0) && n%5!=0){ //if n is divisible by three but not divisible by 5
        return 1 + sum_strange(n-1);
    } else{
        return sum_strange(n-1);
    }
}

//test for sum_strange()
void sum_strange_test(){
    assert(sum_strange(21)==6);
    assert(sum_strange(20)==5);
    assert(sum_strange(18)==5);
    assert(sum_strange(15)==4);
    assert(sum_strange(2)==0);
    assert(sum_strange(1)==0);
}

//helper function for all_same()
bool all_same(const string& s, char firstChar, int begin){
    //base case
    if(begin == s.size()){
        return true;
    } else if(s[begin]==firstChar){ //if char is the same
        return all_same(s,firstChar,begin+1);
    } else { //if char is not the same
        return false;
    }
}

//function that returns true if all the characters in s are the same, and false otherwise.
bool all_same(const string& s){
    if(s.empty()) return true;
    if(s.size()==1) return true;
    //call helper function
    return all_same(s, s[0], 1);
}

//test for all_same()
void all_same_test(){
    assert(all_same(""));
    assert(all_same("s"));
    assert(all_same("ttt"));
    assert(!all_same("sss "));
    assert(!all_same("hello"));
}

//helper function for all_digits()
bool all_digits(const string& s, int begin){
    //base case
    if(begin==s.size()){
        return true;
    } else if((s[begin]>=48)&&(s[begin]<=57)){ //if char is a digit character '0' to '9'
        //recursion
        all_digits(s,begin+1);
    } else{ //if char is not a digit character '0' to '9'
        return false;
    }
}

//function that Returns true if s either empty, or contains only digit characters '0' to '9'.
bool all_digits(const string& s){
    if (s.size()==0) return true;
    //call helper function
    all_digits(s,0);
}

//test for all_digits()
void all_digits_test(){
    assert(all_digits(""));
    assert(all_digits("99973"));
    assert(!all_digits("df"));
    assert(!all_digits("9090 "));
    assert(!all_digits("dlfkj909"));
}

//helper function for trim()
string trim(const string& s, int begin, bool inWord){
    //if reach last char
    if(inWord && begin == s.size()-1){
        return std::string(1,s[begin]);
    } else if(!inWord && begin == s.size()-1){
        return "";
    } else if(!inWord && s[begin]==' '){ //if there are space in the beginning
        return trim(s, begin +1, false);
    } else if(!inWord && s[begin]!=' '){
        return std::string(1,s[begin]) + trim(s, begin +1, true);
    } else if(inWord && s[begin+1]==' ' && !all_same(s.substr(begin, s.size()-begin)) && all_same(s.substr(begin+1, s.size()-begin-1))) {
        return std::string(1, s[begin]);
    } else if(inWord && !all_same(s.substr(begin, s.size()-begin))){
        return std::string(1,s[begin]) + trim(s, begin+1, true);
    }
}

//function that returns a copy of s, but with all leading and trailing spaces removes. No other characters are changed.
string trim(const string& s){
    if(s.empty()) return "";
    //call helper function
    return trim(s, 0, false);
}

//test for trim()
void trim_test(){
    assert(trim("")=="");
    assert(trim("   ")=="");
    assert(trim(" a b ")=="a b");
    assert(trim("adf  ")=="adf");
    assert(trim("  adv")=="adv");
}

//helper function for sum_neg()
int sum_neg(const vector<int>& v, int begin){
    //base case
    if(begin == v.size()){
        return 0;
    } else if(v.at(begin) < 0){ //if the number is negative
        return v.at(begin) + sum_neg(v,begin+1);
    } else{ //if the number is not negative
        return sum_neg(v,begin+1);
    }
}

//function that returns the sum of just the negative numbers in v.
int sum_neg(const vector<int>& v){
    if(v.empty()) return 0;
    //call helper function
    return sum_neg(v, 0);
}

//test for sum_neg()
void sum_neg_test(){
    assert(sum_neg({})==0);
    assert(sum_neg({1,2,3})==0);
    assert(sum_neg({1,-4,0})==-4);
    assert(sum_neg({-3,4,-9})==-12);
    assert(sum_neg({-3})==-3);
    assert(sum_neg({1})==0);
}

//helper function for min_vec()
vector<int> min_vec(const vector<int>& a, const vector<int>& b, vector<int> c, int begin){
    //base case
    if(begin == a.size()){
        return c;
    } else if(a.at(begin)<b.at(begin)){ //if a is smaller than b
        c[begin] = a[begin];
        return min_vec(a, b, c, begin + 1);
    } else{ //if b is smaller than a
        c[begin] = b[begin];
        return min_vec(a, b, c, begin + 1);
    }
}

//function that return  a vector equal to {min(a[0],b[0]), min(a[1],b[1]), min(a[2],b[2]), ..., min(a[n],b[n])}, where n == a.size()
vector<int> min_vec(const vector<int>& a, const vector<int>& b){
    //check pre-condition
    assert(a.size()==b.size());
    assert(a.size()>0);

    vector<int> minVec(a.size());
    return min_vec(a, b, minVec, 0);
}

void min_vec_test(){
    vector<int> test = min_vec({3, 4, 1}, {2, 5, 2});
    vector<int> c = {2, 4, 1};
    assert(test == c);

    vector<int> test2 = min_vec({1, 2, 4}, {2, 1, 1});
    vector<int> f = {1, 1, 1};
    assert(test2 == f);

    vector<int> test3 = min_vec({1}, {2});
    vector<int> g = {1};
    assert(test3 == g);
}

//helper function for count()
int count(const vector<string>& v, const string& s, int begin){
    //base case
    if(begin==v.size()){
        return 0;
    } else if(v.at(begin)==s){ //if string equal to s
        return 1 + count(v, s, begin +1);
    } else{ //if string don't equal to s
        return count(v, s, begin +1);
    }
}

//function returns the number of strings in v that are equal to s.
int count(const vector<string>& v, const string& s){
    return count(v, s, 0);
}

void count_test(){
    assert(count({"hello","hi"},"h")==0);
    assert(count({},"hello")==0);
    assert(count({"hi","hi","hello"},"hi")==2);
    assert(count({"hi"},"hi")==1);
    assert(count({"my","my","my"},"my")==3);
}

//helper function for zip()
void zip(const string&s, const string& t, vector<string>& list, int begin){
    //if begin still within list size
    if(begin<list.size()){
        //add string together
        list.at(begin) = std::string(1,s[begin]) + std::string(1,t[begin]);
        zip(s, t, list, begin +1);
    }
}

//function that returns a vector<string> where the first string is the first character
//of s followed by the first character of t, the second string is the
//second character of s followed by the second character of t, and so on.
vector<string> zip(const string& s, const string& t){
    //check pre-condition
    assert(s.size()==t.size());
    //call helper function
    vector<string> zipWord(s.size());
    zip(s,t,zipWord,0);
    return zipWord;
}

//test for zip_test
void zip_test(){
    vector<string> test = {"ax", "by", "cz"};
    assert(zip("abc", "xyz")==test);

    vector<string> test2 = {"hw","eo","lr","ll","od"};
    assert(zip("hello","world")==test2);

    vector<string> test3 = {};
    assert(zip("","")==test3);
}

//helper function for join()
string join(const vector<string>& v, const string& sep, int begin){
    //if at the last word
    if(begin == v.size()-1) {
        return v.at(begin);
    } else {
        return v.at(begin) + sep + join(v, sep, begin +1);
    }
}

//function that returns a string consisting of all the strings in v concatenated
//together with sep after each string (except for the last).
string join(const vector<string>& v, const string& sep){
    if(v.empty()) return "";
    //calls helper function
    return join(v, sep, 0);
}

//test for join()
void join_test(){
    assert(join({},"")=="");
    assert(join({"cat", "dog", "house"}, ", ") == "cat, dog, house");
    assert(join({"he", "we", "see"}, "")=="hewesee");
    assert(join({"hello","world"}," ")=="hello world");
}

int main () {
    sum_of_squares_test();
    sum_strange_test();
    all_same_test();
    all_digits_test();
    trim_test();
    sum_neg_test();
    min_vec_test();
    count_test();
    zip_test();
    join_test();
    //print if all test passed
    cout << "all tests passed" << endl;
}
