//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL3_DISCONNECTFRAME_H
#define SPL3_DISCONNECTFRAME_H

#include <string>

using namespace std;

class disconnectFrame {

private:
    disconnectFrame();
    int receipt;

public:
    disconnectFrame(int receipt);
    int getReceipt();
    string toString();
};

#endif //SPL3_DISCONNECTFRAME_H
