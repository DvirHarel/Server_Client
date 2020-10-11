//
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARD_H
#define BOOST_ECHO_CLIENT_KEYBOARD_H


#include "Protocol.h"
#include "connectionHandler.h"
#include "User.h"
#include "sendFrame.h"
using namespace std;


class keyBoard {
private:
    ConnectionHandler* connectionHandler;
    Protocol &aProtocol;
    User &loggedin;
    int ID;
    int receipt;

    //bool logged;
  //  string host;
   // string port;


    // Protocol* Protocol;
public:
 //   string getHost();
  //  string getPort();
    keyBoard(User &loggedin,ConnectionHandler *connectionHandler,Protocol &aProtocol);
    void operator()();
    vector<string> split(string s, string delimiter);
    ConnectionHandler* getCH();
    Protocol& getProtocol();
};

#endif //BOOST_ECHO_CLIENT_KEYBOARD_H