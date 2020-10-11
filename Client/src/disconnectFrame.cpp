//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include "../include/disconnectFrame.h"

disconnectFrame::disconnectFrame() : receipt(){
}

int disconnectFrame::getReceipt() {
    return receipt;
}

disconnectFrame::disconnectFrame(int receipt): receipt(receipt) {

}

string disconnectFrame::toString() {
    string tmp = "DISCONNECT\nreceipt:" + to_string(this->receipt) + "\n\n^@";
    return tmp;
}




