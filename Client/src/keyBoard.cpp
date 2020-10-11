//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include "../include/keyBoard.h"
#include "../include/Protocol.h"
#include "../include/connectFrame.h"
#include "../include/disconnectFrame.h"
#include "../include/subscribeFrame.h"
#include "../include/unsubscribeFrame.h"

using namespace std;




/*unsigned long lenBytesStrNoZero(string str) {
    unsigned long strLen = str.length();
    setlocale(LC_ALL, "en_US.UTF-8");
    unsigned long u = 0;
    const char *c_str = str.c_str();
    while (u < strLen) {
        u += mblen(&c_str[u], strLen - u);
    }
    return u;
}*/


keyBoard::keyBoard(User &loggedin, ConnectionHandler *connectionHandler, Protocol &aProtocol): connectionHandler(connectionHandler), aProtocol(aProtocol), loggedin(loggedin),ID(0),receipt(0) {
   // ID=0;
   // receipt=0;
}


void keyBoard::operator()() {
    //  int receipt = 0;
    //   int ID = 0;

    while (!loggedin.isTerminate()) {// we wants to read as long as there is a connection to the server
        string tosend;
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        vector<string> words = split(line, " ");
        if (words[0] == "join") {
            subscribeFrame tmp = subscribeFrame(words[1], ID, receipt);
            if (loggedin.addSubscription(words[1], ID)) {
                ID++;
                loggedin.addReceiptIdToGenre(receipt, "SUBSCRIBE");//new receipt
                receipt++;
                std::cout << tmp.toString() << std::endl;//for checks
                tosend = tmp.toString();
            }
        }else if (words[0] == "login") {
            string host = words[1].substr(0,words[1].find(':'));
            short port = stoi(words[1].substr(words[1].find(":")+1));
            connectionHandler->setHostPort(host,port);
            connectionHandler->connect();
            connectionHandler->setConnect();
            if(!this->connectionHandler->isConnected())
            {
                cerr << "cannot connect to " << host << ":" << port << endl;
                break;
            }
                connectFrame tmp = connectFrame(words[1], words[2], words[3]);
                loggedin.setUsername(words[2]);
                std::cout << tmp.toString() << std::endl;      //for checks
                tosend = tmp.toString();
            } else if (words[0] == "logout") {
                disconnectFrame tmp = disconnectFrame(receipt);
                loggedin.addReceiptIdToGenre(receipt, "DISCONNECT");
                receipt++;
                std::cout << tmp.toString() << std::endl;      //for checks
                tosend = tmp.toString();
            } else if (words[0] == "add") {
                sendFrame tmp = sendFrame(1, loggedin.getUsername(), words[1], words[2], "neverMind");
                loggedin.addBook(words[2], loggedin.getUsername());
                loggedin.addBookToGenre(words[2], words[1]);
                std::cout << tmp.toString() << std::endl;      //for checks
                tosend = tmp.toString();
            } else if (words[0] == "borrow") {
                sendFrame tmp = sendFrame(2, loggedin.getUsername(), words[1], words[2], "neverMind");
                loggedin.addToRequestedBooks(words[2]);
                std::cout << tmp.toString() << std::endl;      //for checks
                tosend = tmp.toString();
            } else if (words[0] == "return") {
                sendFrame tmp = sendFrame(3, loggedin.getUsername(), words[1], words[2],
                                          loggedin.getOwnerByBook(words[3]));
                loggedin.eraseBook(words[2]);
                loggedin.eraseBookFromGenre(words[2], words[1]);
                std::cout << tmp.toString() << std::endl;      //for checks
                tosend = tmp.toString();

            } else if (words[0] == "status") {
                sendFrame tmp = sendFrame(4, loggedin.getUsername(), words[1], " ", "neverMind");
                std::cout << tmp.toString() << std::endl;      //for checks
                tosend = tmp.toString();

            } else if (words[0] == "exit") {
                unsubscribeFrame tmp = unsubscribeFrame(words[1], loggedin.getIDforGenre(words[1]), receipt);
                loggedin.eraseSubscription(words[1]);
                loggedin.addReceiptIdToGenre(receipt,
                                             "UNSUBSCRIBE");//check if receipt is true or to change it to subscription ID
                receipt++;
                std::cout << tmp.toString() << std::endl;      //for checks
                tosend = tmp.toString();
            }
            int len = tosend.size();
            string rrr = tosend;
            if (!connectionHandler->sendLine(rrr)) {
                aProtocol.setTerminate();
                connectionHandler->close();
                std::cout << "Disconnected. Exiting...\n" << std::endl;
                break;
            }
            std::cout << "Sent " << len + 1 << " bytes to server" << std::endl;
        }
    }
    vector<string> keyBoard::split(string s, string delimiter) {
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

ConnectionHandler *keyBoard::getCH() {
    return connectionHandler;
}

Protocol &keyBoard::getProtocol() {
    return aProtocol;
}

/*
bool keyBoard::getLoggedStatus() {
    return logged;
}


string keyBoard::getHost() {
    return host;
}

string keyBoard::getPort() {
    return port;
}

*/







