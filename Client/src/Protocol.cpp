//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include "../include/Protocol.h"
#include "../include/connectionHandler.h"
#include "../include/sendFrame.h"

using namespace std;

bool Protocol::isUserTerminate()
{
    return loggedin.isTerminate();
}

void Protocol::setTerminate()
{
    this->terminate = true;
}


void Protocol::operator()() {
    //  std::cout<<ans<<std::endl;
    while (!this->terminate) {
        while (!connectionHand->isConnected())
        {}
        string ans;
        if (!connectionHand->getLine(ans)) {
            terminate = true;
            connectionHand->close();
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        vector<string> words = split(ans, '\n');
        if (words[0] == "CONNECTED") {
            cout << "Login successful" << endl;
        } else if (words[0] == "MESSAGE") {
            string genre = words[3].substr(words[3].find(':') + 1);
            if (words[5].find("has added", 0) != string::npos) {
            } else if (words[5].find("wish to borrow") != string::npos) {
                vector<string> splitted = split(words[5], ' ');
                string bookname;
                string tmp = "";
                size_t i;
                for (i = 4; i < splitted.size(); i++) {
                    bookname += splitted[i] + ' ';
                }
                bookname = bookname.substr(0, bookname.size() - 1);
                if (loggedin.canSendBook(bookname)) {
                    string tmp1 = "SEND\n";
                    tmp = tmp1 + words[3] + "\n\n" + loggedin.getUsername() + " has " + bookname +
                          "\n\n^@";
                    //      if (!connectionHand->sendLine(tmp)) {
                    //         cout << "Disconnected. Exiting...\n" << endl;
                    //     }
                if (!connectionHand->sendLine(tmp)) {
                    terminate = true;
                    connectionHand->close();
                    std::cout << "Disconnected. Exiting...\n" << std::endl;
                    break;
                }
            }
            } else if (words[5].find("has") != string::npos) {
                cout<<ans<<endl;
                vector<string> splitted = split(words[5], ' ');
                string bookName;
                string tmp;
                size_t i;
                for (i = 2; i < splitted.size(); i++) {
                    bookName += splitted[i] + ' ';
                }
                bookName = bookName.substr(0, bookName.size() - 1);
                vector<string> books = loggedin.getRequestsForBooks();
                if (find(books.begin(), books.end(), bookName) != books.end()) {
                    loggedin.removeRequestedBook(bookName);
                    loggedin.addBook(bookName, splitted[0]);
                    loggedin.addBookToGenre(bookName, genre);
                    string tmp1 = "SEND\n";
                    tmp = tmp1 + words[3] + "\n\n" + "Taking" + " " + splitted[2] + " from " + splitted[0] + "\n\n";
                    //  if (!connectionHand->sendLine(tmp)) {
                    //  cout << "Disconnected. Exiting...\n" << endl;
                    if (!connectionHand->sendLine(tmp)) {
                        terminate = true;
                        connectionHand->close();
                        std::cout << "Disconnected. Exiting...\n" << std::endl;
                        break;
                    }
                }
        }
             else if (words[5].find("Taking") != string::npos) {
                 cout<<ans<<endl;
                vector<string> splitted = split(words[5], ' ');
                string bookName;
                size_t i;
                for (i = 1; (i < splitted.size()) & (splitted[i] != "from"); i++) {
                    bookName += splitted[i] + ' ';
                }
                bookName = bookName.substr(0, bookName.size() - 1);
                if (loggedin.getUsername() == splitted[splitted.size() - 1]) {
                    loggedin.setBelong(false, bookName);
                    loggedin.eraseBookFromGenre(bookName, genre);
                }
            } else if (words[5].find("Returning") != string::npos) {
                 cout<<ans<<endl;
                vector<string> splitted = split(words[4], ' ');
                string bookName;
                size_t i;
                for (i = 1; (i < splitted.size()) & (splitted[i] != "to"); i++) {
                    bookName += splitted[i] + ' ';
                }
                bookName = bookName.substr(0, bookName.size() - 1);
                if (loggedin.getUsername() == splitted[splitted.size() - 1])
                    loggedin.setBelong(true, bookName);
            } else if (words[5].find("status") != string::npos) {//need to check what is the right instruction to do it
                vector<string> statusOfBooks = loggedin.getStatusBooks(genre);
                if (statusOfBooks.size() != 0) {
                    string statusFrameBody = loggedin.getUsername() + ':';
                    size_t i;
                    for (i = 0; i < statusOfBooks.size(); i++) {
                        statusFrameBody += statusOfBooks[i] + ',';
                    }
                    statusFrameBody = statusFrameBody.substr(0,statusFrameBody.size()-1);
                    string tmp1 = "SEND\n";
                    string str = tmp1 + words[3] + "\n\n" + statusFrameBody + "\n" + "^@";
                   // cout<<str<<endl;
                    if (!connectionHand->sendLine(str)) {
                        terminate = true;
                        connectionHand->close();
                        std::cout << "Disconnected. Exiting...\n" << std::endl;
                        break;
                    }
                }
            }
            else if (words[5].find(":") != string::npos) {//need to check what is the right instruction to do it
                   cout<<ans<<endl;
                    }
                }

         else if (words[0] == "RECEIPT") {
            int receiptId;
            string tmp = (words[1].substr(11));
            receiptId = stoi(tmp);
            string typeOfMessageGenre = loggedin.getTypeFrameGenreById(receiptId);
            if (typeOfMessageGenre == "SUBSCRIBE")
                cout << loggedin.getUsername() + " Joined club " + loggedin.getGenreForId(receiptId) << endl;
            else if (typeOfMessageGenre == "UNSUBSCRIBE")
                cout << loggedin.getUsername() + " Exited club" << endl;
            else if (typeOfMessageGenre == "DISCONNECT") {
                loggedin.setIsTerminated(true);
                // delete loggedin;
                // connectionHand->close();
//need to be removed from all genre
            }
        } else if (words[0] == "ERROR") {
            cout << words[1] + "\n" + words[2];
            /*
            if (words[1].find("receipt") != words[1].end()) {
                cout << words[1];
            }
            cout << ans.getValueByKey("message") << endl;
            cout << ans.getBody() << endl;*/
            loggedin.setIsTerminated(true);
            connectionHand->close();
            // break;
        }
    }
}
//}

vector<string> Protocol::split(string strToSplit, char delimiter) {
    vector<string> result;
    string currentStr = "";
    size_t i;
    for (i = 0; i < strToSplit.length(); ++i) {
        if ((strToSplit[i] == delimiter) | (i == strToSplit.length()-1)) {
            if(strToSplit.length()-1 == i)
            {
                result.push_back(currentStr + strToSplit[i]);
            } else {
                result.push_back(currentStr);
            }
            currentStr = "";
        }
        else {
            currentStr += strToSplit[i];
        }
    }
    return result;
}

Protocol::Protocol(ConnectionHandler *connectionHandler, User &loggedin):connectionHand(connectionHandler), loggedin(loggedin) {

}

