//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include "../include/sendFrame.h"

int sendFrame::getCommand() const {
    return this->command;
}

string sendFrame::getDest() const {
    return this->dest;
}

string sendFrame::getBookName() const {
    return this->bookName;
}


string sendFrame::toString() {
    string tmp1 = "SEND";
    string tmp;
    if(command==1)
            tmp = tmp1 + "\n" + "destination:" + this->dest + "\n\n" + name +" "+  "has added the book " + this->bookName + "\n\n^@";
    else if(command==2)
            tmp = tmp1 + "\n" + "destination:" + this->dest + "\n\n" + name +" "+ "wish to borrow"+ " "  + this->bookName + "\n\n^@";
        else if(command==3)
            tmp = tmp1 + "\n" + "destination:" + this->dest + "\n\n" + "Returning"+" " + this->bookName + " to " + userNameToReturn + "\n\n^@";
            else if(command==4)
                  tmp = tmp1 + "\n" + "destination:" + this->dest + "\n\n" + "book status" + "\n\n^@";
    /*
    switch (this->command)
    {
        case 1: //add
            tmp = tmp1 + "\n" + "destination:" + this->dest + "\n\n" + getName() +  "has added the book " + this->bookName + "\n" + "^@";
        case 2: // borrow
            tmp = tmp1 + "\n" + "destination:" + this->dest + "\n\n" + getName() + "wish to borrow"  + this->bookName + "\n" + "^@";
        case 3://return
            tmp = tmp1 + "\n" + "destination:" + this->dest + "\n\n" + "Returning" + this->bookName + " to " + this->name + "\n" + "^@";
        case 4://status
            tmp = tmp1 + "\n" + "destination:" + this->dest + "\n\n" + "book status" + "\n" + "^@";
      //  default: // error

    }
     */
    return tmp;
}

string sendFrame::getName() const {
    return name;
}

sendFrame::sendFrame(const int command, const string name, const string dest, string bookName,
                     const string userNameToReturn): command(command),dest(dest), bookName(bookName), name(name),userNameToReturn(userNameToReturn) {

}


