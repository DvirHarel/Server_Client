//
// Created by rapkeb@wincs.cs.bgu.ac.il on 14/01/2020.
//

#ifndef SPL3_USER_H
#define SPL3_USER_H

#include <string>
#include <map>
#include <vector>
#include <mutex>


using namespace std;

class User {

private:
    string userName;//yes
    map<string, int> genreToID;//yes
    map<string,pair<string,bool >> ownerOfBooks;//yes
    map<string,vector<string>> genreToCurrentBooks;//genre and the list of books
    map<int,string> receiptIdToGenre;//yes
    vector<string> requestBooks;
    bool isTerminated;
    //need to add mutex

public:
    User();
    ~User();
    const string getUsername() const;
    void setUsername(const string userName);
    void addBook(string book, string owner);
    void eraseBook(string book);
    bool addSubscription(string genre, int id);
    bool eraseSubscription(string genre);
    string getOwnerByBook(string book);
    void addToRequestedBooks(string book);
    void setBelong(bool,string);
    bool canSendBook(string);
    void addBookToGenre(string bookName,string genre);
    void eraseBookFromGenre(string bookName,string genre);
    const vector<string> getRequestsForBooks() const;
    vector<string> getStatusBooks(string genre);
    void addReceiptIdToGenre(int id,string);
    string getTypeFrameGenreById(int id);
    bool isTerminate() const;
    void setIsTerminated(bool isTerminated);
    void removeRequestedBook(string book);
    string getGenreForId(int IdNumber);
    int getIDforGenre(string genre);
    string getReceiptforGenre(int receipt);
};
#endif //SPL3_USER_H
