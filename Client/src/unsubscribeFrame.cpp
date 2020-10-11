//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include "../include/unsubscribeFrame.h"

unsubscribeFrame::unsubscribeFrame(const string dest,int id, int receipt) : destination(dest),id(id),receipt(receipt) {
}

string unsubscribeFrame::getDest() const {
    return destination;
}

string unsubscribeFrame::toString() {
    string tmp1 = "UNSUBSCRIBE";
    string tmp = tmp1 + "\n" + "destination:" + this->destination + "\n" + "id:" +  to_string(this->id) + "\n" + "receipt:" + to_string(this->receipt) + "\n\n" + "^@";
    return tmp;
}
