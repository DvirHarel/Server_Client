//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#include "../include/User.h"
using namespace std;

#include <algorithm>
#include "../include/User.h"

User::User(): userName(), genreToID(), ownerOfBooks(), genreToCurrentBooks(),receiptIdToGenre(),  requestBooks(), isTerminated(false)  {
}

User::~User() {
    ownerOfBooks.clear();
    genreToID.clear();
    requestBooks.clear();
    receiptIdToGenre.clear();
    genreToCurrentBooks.clear();
}

const string User::getUsername() const {
    return userName;
}

void User::setUsername(const string username) {
    User::userName = username;
}

void User::addBook(string book, string owner) {
    pair<string,bool> ownerOfBook = make_pair(owner, true);
    
    ownerOfBooks[book] = ownerOfBook;
}

void User::eraseBook(string book) {
    
    ownerOfBooks.erase(book);
}

bool User::addSubscription(string genre, int id) {
    bool canAdd = false;
    
    if (genreToID.find(genre) == genreToID.end()) {
        genreToID[genre] = id;
        canAdd = true;
    }
    return canAdd;
}

bool User::eraseSubscription(string genre) {
    bool canErase = false;
    if (genreToID.find(genre) != genreToID.end()) {
        genreToID.erase(genre);
        canErase = true;
    }
    return canErase;
}

string User::getOwnerByBook(string book) {
    
    return ownerOfBooks[book].first;
}

void User::addToRequestedBooks(string book) {
    
    requestBooks.push_back(book);
}

void User::addBookToGenre(string bookName, string genre) {
    
    genreToCurrentBooks[genre].push_back(bookName);
}

void User::eraseBookFromGenre(string bookName, string genre) {
    
    genreToCurrentBooks[genre].erase(find(genreToCurrentBooks[genre].begin(),genreToCurrentBooks[genre].end(),bookName));
}

vector<string> User::getStatusBooks(string genre) {
    
    return genreToCurrentBooks[genre];
}

const vector<string> User::getRequestsForBooks() const {
    return requestBooks;
}

void User::removeRequestedBook(string book) {
    
    requestBooks.erase(find(requestBooks.begin(), requestBooks.end(), book));
}

void User::setBelong(bool ans, string bookName) {
    
    ownerOfBooks[bookName].second = ans;
}

bool User::canSendBook(string bookname) {
    for(pair<string, vector<string>> element: genreToCurrentBooks) {
       if (std::find(element.second.begin(), element.second.end(), bookname) != element.second.end())
                return true;
        }
    return false;
}

void User::addReceiptIdToGenre(int id, string message) {
    
    receiptIdToGenre[id] = message;
}

string User::getTypeFrameGenreById(int id) {
    
    return receiptIdToGenre[id];
}

bool User::isTerminate() const {
    return isTerminated;
}

void User::setIsTerminated(bool shouldTerminate) {
    User::isTerminated = shouldTerminate;
   // delete(this);
}

string User::getGenreForId(int IdNumber) {
    for(pair<string, int> element: genreToID) {
        if (element.second == IdNumber)
            return element.first;
    }
    return "";
}

int User::getIDforGenre(string genre)
{
    return genreToID[genre];
}

string User::getReceiptforGenre(int receipt){
    for(pair<int, string> element: receiptIdToGenre) {
        if (element.first == receipt)
            return element.second;
    }
    return "";
}
