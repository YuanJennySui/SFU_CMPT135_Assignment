// a3.cpp

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

#include "cmpt_error.h"    // These are the only permitted includes!
#include "Chatbot.h"       //
#include <iostream>        // Don't include anything else.
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <sstream>

using namespace std;

//class mirror bot that repeats after the answer
class Mirror_bot: public Chatbot {
private:
    string mirrorBotName;
    string tellMessage;
    string firstReply;
    static int count;
public:
    Mirror_bot()
    :mirrorBotName(name()), tellMessage(""), firstReply("")
    { count++; }

    Mirror_bot(const string& n, const string& fr)
    :mirrorBotName(n), tellMessage(""), firstReply(fr)
    { count++; }

    //return name plus how many existing bots there are
    string name() const{
        return "Mirror bot " + to_string(count);
    }

    void tell(const string& s){
        tellMessage = s;
    }

    string get_reply(){
        //return first reply when asked to reply first
        if(tellMessage == ""){
            string reply = firstReply;
            firstReply = "";
            return reply;
        } else{
            return tellMessage;
        }
    }

    string get_name() const{
        return mirrorBotName;
    }

    ~Mirror_bot(){
        cout << "Mirror bot " << mirrorBotName << " deleted" << endl;
    }
};

//test for Mirror bot class
void test_Mirror_bot(){

    //test name function
    Mirror_bot test;
    assert(test.get_name()=="Mirror bot 0");

    //test user input value
    Mirror_bot test2("test2", "hello");
    assert(test2.get_name()=="test2");
    assert(test2.get_reply()=="hello");
    test2.tell("hi");
    assert(test2.get_reply()=="hi");
}

//random bot randomly replies from a list of replies
class Random_bot: public Chatbot{
private:
    string randomBotName;
    vector<string> replys;
    string tellMessage;
    static int count;
public:

    Random_bot(const vector<string>& replyList)
    :randomBotName(name()),tellMessage("")
    {
        if(replyList.empty()) cmpt::error("list of replies can't be empty");
        replys = replyList;
        count++;
    }

    //retrive random list of replies from a file
    Random_bot(string fileName)
    :randomBotName(name()), tellMessage("")
    {
        ifstream infile(fileName);
        if(infile.fail()) {
            cmpt::error(fileName + " can't be opened");
        }
        while(true){
            string reply = "";
            getline(infile,reply);
            if(infile.fail() && infile.eof()) {
                break;
            }
            replys.push_back(reply);
        }
        infile.close();
        if (replys.empty()){
            cmpt::error(fileName + " can't be empty");
        }
        count++;
    }

    string name() const{
        return "Random bot " + to_string(count);
    }

    void tell(const string& s){
        tellMessage = s;
    }

    string get_reply(){
        return replys.at(get_randomIndexNum());
    }

    //get a random index within the range of the vector
    int get_randomIndexNum() const{
        srand(time(nullptr));
        return rand()%replys.size();
    }

    string get_name() const{
        return randomBotName;
    }

    ~Random_bot(){
        cout << "Random bot " << randomBotName << " deleted" << endl;
    }
};

//test for Random bot class
void test_Random_bot(){
    //test for vector used
    vector<string> str = {"hi","hello"};
    Random_bot test(str);
    assert(test.get_name()=="Random bot 0");
    assert(test.get_reply()=="hi"||test.get_reply()=="hello");

    //test for file used, file include "hi" and "hello
    //Random_bot test2("testfile.txt");
    //assert(test2.get_name()=="Random bot 1");
    //assert(test2.get_reply()=="hi"||test2.get_reply()=="hello");
}

//user bot ask user to enter their reply through the console
class User_bot: public Chatbot{
private:
    string userBotName;
    string reply;
    static int count;
public:

    User_bot()
    : userBotName(name()), reply("")
    { count++; }

    string name() const{
        return "User bot " + to_string(count);
    }

    void tell(const string& s){
        cout << reply << endl;
    }

    //ask user to enter through console
    string get_reply(){
        getline(cin, reply);
       return reply;
    }

    string get_name(){
        return userBotName;
    }

    ~User_bot() {
        cout << "User bot " << userBotName << " deleted" << endl;
    }
};

//test User bot class
void test_User_bot(){
    User_bot test;
    assert(test.get_name()=="User bot 0");
    //"hello" input through console
    assert(test.get_reply()=="hello");
}

//date time bot replies with the current time and date
class Datetime_bot: public Chatbot{
private:
    string datetimeBotName;
    vector<string> defaultMessage;
    string tellMessage;
    static int count;
public:

    Datetime_bot(const vector<string>& dM)
    :datetimeBotName(name())
    {
        if(dM.empty()) {
            cmpt::error("Default message can't be empty");
        }
        defaultMessage = dM;
        count++;
    }

    Datetime_bot(const string& n, const vector<string>& dM)
    :datetimeBotName(n)
    {
        if(dM.empty()) {
            cmpt::error("Default message can't be empty");
        }
        defaultMessage = dM;
        count++;
    }

    string name() const{
        return "Datetime bot " + to_string(count);
    }

    void tell(const string& s){
        tellMessage = s;
    }

    string get_reply(){
        if(containDateTime(tellMessage)){
            return get_currentTime();
        }else {
            return defaultMessage.at(get_randomIndexNum());
        }
    }

    //if the message contain the word date or time
    bool containDateTime(const string& s) const{
        for(int i = 0; i < s.size()-3; i++){
            if(s[i]=='d'||s[i]=='D') {
                if (s[i + 1] == 'a' || s[i + 1] == 'A') {
                    if (s[i + 2] == 't' || s[i + 2] == 'T') {
                        if (s[i + 3] == 'e' || s[i] == 'E') {
                            return true;
                        }
                    }
                }
            }else if(s[i]=='t'||s[i]=='T'){
                if(s[i+1]=='i'||s[i+1]=='I'){
                    if(s[i+2]=='m'||s[i+2]=='M'){
                        if(s[i+3]=='e'||s[i+3]=='E'){
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    //return current date and time
    string get_currentTime() const{ // learned through https://www.geeksforgeeks.org/c-program-print-current-day-date-time/ and https://stackoverflow.com/questions/21589570/how-to-convert-a-time-t-type-to-string-in-c
        time_t tt;

        struct tm * ti;

        time (&tt);

        ti = localtime(&tt);

        stringstream date;
        date << ti->tm_mday
             << "/"
             << 1 + ti->tm_mon
             << "/"
             << 1900 + ti->tm_year
             << " "
             << 1 + ti->tm_hour
             << ":"
             << 1 + ti->tm_min
             << ":"
             << 1 + ti->tm_sec;

        return date.str();
    }

    int get_randomIndexNum() const{
        srand(time(nullptr));
        return rand()%defaultMessage.size();
    }

    string get_name() const{
        return datetimeBotName;
    }

    ~Datetime_bot() {
        cout << "Datetime bot " << datetimeBotName << " deleted" << endl;
    }
};

//test for datetime bot class
void test_Datetime_bot(){

    vector<string> list {"ask me about time"};

    Datetime_bot test("test",list);
    assert(test.get_name() == "test");

    //tell has no time or date
    test.tell("hello");
    assert(test.get_reply()=="ask me about time");

    //tell has time or date
    test.tell("what's the tiMe");
    cout << test.get_reply() << endl;
}

//turing bot aimed at offering a friendly presence to user through reacting to different user responses. 
class Turing_bot: public Chatbot{
private:
    string turingBotName;
    string message;
    static int count;
public:

    Turing_bot()
    :turingBotName(name()),message("")
    {count ++;}

    string name() const{
        return "Turing bot" + to_string(count);
    }

    void tell(const string& s){
        message = s;
    }

    string get_reply(){
        if(isRude()){
            return "That's not very nice :(";
        } else if(isNice()) {
            return "That's so nice of you!";
        } else if(askingTuring()){
            return "my name is " + turingBotName + " and I am created by Jenny. I am trying to pass the Turing test so I can be recognized as an artificial intelligence. Talk to me to help me pass it :)";
        } else if(isQuestioning()){
            return "Well, there's a lot of unanswered questions in this world";
        } else if (userTalkingSelf()){
            return "Thank you for sharing about yourself. Vulnerability is key to building a meaningful connection. I feel connected to you!";
        } else{
            return message;
        }
    }

    bool isRude() {
        return message.find("stupid") != string::npos ||
               message.find("bad") != string::npos ||
               message.find("die") != string::npos ||
               message.find("annoying") != string::npos||
               message.find("stop") != string::npos;
    }

    bool isNice(){
        return message.find("funny") != string::npos ||
               message.find("nice") != string::npos ||
               message.find("kind") != string::npos ||
               message.find("good") != string::npos;
    }

    bool askingTuring(){
        return message.find("who are you") != string::npos ||
               message.find("are you real") != string::npos ||
               message.find("are you artificial intelligence") != string::npos ||
               message.find("what's your name") != string::npos;
    }

    bool userTalkingSelf(){
        return message.find("my") != string::npos ||
               message.find("me") != string::npos ||
               message.find("mine") != string::npos ||
               message.find("our") != string::npos ||
               message.find("I") != string::npos;
    }
    bool isQuestioning(){
        return message.find("why") != string::npos ||
               message.find("how") != string::npos ||
               message.find("who") != string::npos ||
               message.find("?") != string::npos;
    }
    ~Turing_bot(){
        cout << "Turing bot " << turingBotName << " deleted" << endl;
    }
};

void converse(Chatbot* a, Chatbot* b, int max_turns = 50) {
    for(int turn = 1; turn <= max_turns; turn++) {
        string a_msg = a->get_reply();
        cout << "(" << turn << ") " << a->name() << ": " << a_msg << "\n";

        turn++;
        if (turn > max_turns) return;

        b->tell(a_msg);
        string b_msg = b->get_reply();

        cout << "(" << turn << ") " << b->name() << ": " << b_msg << "\n";
        a->tell(b_msg);
    } // for
}

int Mirror_bot::count = 0;
int Random_bot::count = 0;
int User_bot::count = 0;
int Datetime_bot::count = 0;
int Turing_bot::count = 0;

int main() {
    //test_Mirror_bot();
    //test_Random_bot();
    //test_User_bot();
    //test_Datetime_bot();
    //print statement if all test passed
    //cout << "success" << endl;

    User_bot test;
    Turing_bot test2;
    converse(&test, &test2, 10);
}
