#include <books.hpp>
#include <users.hpp>
#include <library.hpp>

int main() {
  books myBooks;
  users myUsers;
  transactions myTrans;
  bookshelvesConstructor(myBooks);
  userBaseConstructor(myUsers);
  transactionsConstructor(myTrans);
  mainMenu(myBooks, myUsers, myTrans);
  return 0;
}