//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL3_UNSUBSCRIBEFRAME_H
#define SPL3_UNSUBSCRIBEFRAME_H

#include <string>

using namespace std;

class unsubscribeFrame {

private:
    const string destination;
    // static int ID;
    int id;
    int receipt;
public:
    unsubscribeFrame(const string dest, int id, int receipt);
    string getDest() const ;
    //string getID() const ;
    string toString();

};

#endif //SPL3_UNSUBSCRIBEFRAME_H
