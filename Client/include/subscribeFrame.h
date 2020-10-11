//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL3_SUBSCRIBEFRAME_H
#define SPL3_SUBSCRIBEFRAME_H

#include <string>

using namespace std;

class subscribeFrame {

private:
    const string destination;
    int id;
    int receipt;
public:
    subscribeFrame(const string dest,int id, int receipt);
    string getDest() const ;
    //string getID() const ;
    string toString();

};

#endif //SPL3_SUBSCRIBEFRAME_H
