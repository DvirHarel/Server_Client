//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include <sstream>
#include "../include/subscribeFrame.h"

subscribeFrame::subscribeFrame(const string dest, int id, int receipt)  : destination(dest), id(id),receipt(receipt){

}
string subscribeFrame::getDest() const {
    return this->destination;
}

string subscribeFrame::toString() {
    string tmp1 = "SUBSCRIBE";
    stringstream ss;
    ss << id;
    string tmp2 = ss.str();

    stringstream rr;
    ss << receipt;
    string tmp3 = ss.str();

        string tmp = tmp1 + "\n" + "destination:" + this->destination + "\n" + "id:" + tmp2 + "\n" + "receipt:" +tmp3.substr(0,tmp3.size()-1) + "\n\n" + "^@";
        return tmp;
}


