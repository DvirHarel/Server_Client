#include <stdlib.h>
#include "../include/connectionHandler.h"
#include "../include/User.h"
#include "../include/keyBoard.h"
#include "../include/connectFrame.h"
#include <iostream>
#include <thread>

using namespace std;

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
vector<string> split(string s, string delimiter) {
    vector<string> list;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}
int main (int argc, char *argv[]) {
 //   if (argc < 3) {
 //       cerr << "Usage: " << argv[0] << " host port" << endl << endl;
 //       return -1;
 //   }


    std::string host = "";
    short port = 0;//argv[2];

    ConnectionHandler connectionHandler(host, port);
    User bookClub = User();
    Protocol protocol = Protocol(&connectionHandler,bookClub);
    keyBoard key = keyBoard(bookClub,&connectionHandler,protocol);
    thread t1(key);
    thread t2(protocol);

    //From here we will see the rest of the ehco client implementation:

      /*  while (1) {
            const short bufsize = 1024;
            char buf[bufsize];
            cin.getline(buf, bufsize);
            string line(buf);
            string newline = key.operator()();
            int len = line.length();
                if (!connectionHandler.sendLine(newline)) {
                    connectionHandler.close();
                    cout << "Disconnected. Exiting...\n" << endl;
                    break;
                }
            // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
            cout << "\nSent " << len + 1 << " bytes to server\n" << endl;


            // We can use one of three options to read data from the server:
            // 1. Read a fixed number of characters
            // 2. Read a line (up to the newline character using the getline() buffered reader
            // 3. Read up to the null character
            string answer;
            // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
            // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
            if (!connectionHandler.getLine(answer)) {
                connectionHandler.close();
                cout << "Disconnected. Exiting...\n" << endl;
                break;
            }
            protocol.process(answer);
            len = answer.length();
            // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
            // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
            answer.resize(len - 1);
            cout << "\nReply: " << answer << " " << len << " bytes " << endl << endl;
            if (answer == "bye") {
                connectionHandler.close();
                cout << "Exiting...\n" << endl;
                break;
            }
            if(protocol.isUserTerminate())
            {
                connectionHandler.close();
                cout << "Exiting...\n" << endl;
                break;
            }
        }
   // } //else goto start;
        return 0;*/
    t1.join();
    t2.join();
    return 0;
    }





/*

#include <stdlib.h>
#include "Boost_Echo_Client/include/connectionHandler.h"
#include "Boost_Echo_Client/include/User.h"
#include "Boost_Echo_Client/include/keyBoard.h"
#include "Boost_Echo_Client/include/connectFrame.h"
#include <iostream>
#include <thread>

using namespace std;


vector<string> split(string s, string delimiter) {
    vector<string> list;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}
int main (int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " host port" << endl << endl;
        return -1;
    }
    // User loggedin = User();
    //keyBoard key = keyBoard(loggedin);
    std::string host = argv[1];
    short port = atoi(argv[2]);

    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    start:
    User bookClub = User();
    keyBoard key = keyBoard(bookClub);
    Protocol protocol = Protocol(&connectionHandler,bookClub);
    //From here we will see the rest of the ehco client implementation:

    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        string newline = key.operator()(line);
        int len = line.length();
        if (!connectionHandler.sendLine(newline)) {
            connectionHandler.close();
            cout << "Disconnected. Exiting...\n" << endl;
            break;
        }
        // connectionHandler.sendLine(line) appends '\n' to the message. Therefor we send len+1 bytes.
        cout << "\nSent " << len + 1 << " bytes to server\n" << endl;


        // We can use one of three options to read data from the server:
        // 1. Read a fixed number of characters
        // 2. Read a line (up to the newline character using the getline() buffered reader
        // 3. Read up to the null character
        string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!connectionHandler.getLine(answer)) {
            connectionHandler.close();
            cout << "Disconnected. Exiting...\n" << endl;
            break;
        }
        protocol.process(answer);
        len = answer.length();
        // A C string must end with a 0 char delimiter.  When we filled the answer buffer from the socket
        // we filled up to the \n char - we must make sure now that a 0 char is also present. So we truncate last character.
        answer.resize(len - 1);
        cout << "\nReply: " << answer << " " << len << " bytes " << endl << endl;
        if (answer == "bye") {
            connectionHandler.close();
            cout << "Exiting...\n" << endl;
            break;
        }
        if(protocol.isUserTerminate())
        {
            connectionHandler.close();
            cout << "Exiting...\n" << endl;
            break;
        }
    }
    // } //else goto start;
    return 0;
}*/
