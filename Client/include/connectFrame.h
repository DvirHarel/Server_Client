//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL3_CONNECTFRAME_H
#define SPL3_CONNECTFRAME_H

#include <string>

using namespace std;

class connectFrame {

private:
    const string host;
    const string userName;
    const string password;
public:
    connectFrame(const string host, const string name, const string password);
    string getHost() const ;
    string getUserName() const ;
    string getPassword() const ;
    string toString();
};
#endif //SPL3_CONNECTFRAME_H
