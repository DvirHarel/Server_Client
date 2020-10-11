//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL3_SENDFRAME_H
#define SPL3_SENDFRAME_H

#include <string>

using namespace std;

class sendFrame {

private:
    const int command;
    const string dest;
    const string bookName;
    const string name;
    const string userNameToReturn;
public:
    sendFrame(const int command , const string name, const string dest, string bookName, const string userNameToReturn);
    int getCommand() const ;
    string getDest() const ;
    string getBookName() const ;
    string getName() const ;
    string toString();
};


#endif //SPL3_SENDFRAME_H
