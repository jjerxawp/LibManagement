#include "books.hpp"
#include "users.hpp"
#include "library.hpp"

int main() {
    book myBooks[BOOKCOUNT_MAX];
    user myUsers[USERCOUNT_MAX];
    transaction myTrans[TRANSACTION_COUNT_MAX];
    bookshelvesConstructor(myBooks);
    userBaseConstructor(myUsers);
    transactionsConstructor(myTrans);
    mainMenu(myBooks, myUsers, myTrans);
    return 0;
}