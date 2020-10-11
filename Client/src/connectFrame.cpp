//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include <iostream>
#include "../include/connectFrame.h"
using namespace std;

connectFrame::connectFrame(const string host, const string name, const string password):host(host),userName(name),password(password) {
}

string connectFrame::getHost() const {
    return this->host;
}

string connectFrame::getUserName() const {
    return this->userName;
}

string connectFrame::getPassword() const {
    return this->password;
}

string connectFrame::toString() {
    string tmp1 = "CONNECT";
    string tmp = tmp1 + "\n" + "accept-version:1.2\n" + "host:" + this->host + "\n" + "login:" + this->userName + "\n" + "passcode:" + this->password + "\n\n^@";
    return tmp;
}
