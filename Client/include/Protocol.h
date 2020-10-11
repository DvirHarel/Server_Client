//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//


#ifndef PROTOCOL_H
#define PROTOCOL_H
#include "connectionHandler.h"
#include "User.h"


class Protocol {
private:
    ConnectionHandler* connectionHand;
    User &loggedin;
    bool terminate = false;
public:

    Protocol(ConnectionHandler* connectionHandler,User &loggedin);
   // Protocol(const Protocol& aProtocol);
   // Protocol& operator=(const Protocol& aProtocol);
    void operator()();
    vector<string> split(string strToSplit, char delimiter);
    bool isUserTerminate();
    void setTerminate();
};


#endif //PROTOCOL_H