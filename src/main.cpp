#include <books.hpp>
#include <users.hpp>
#include <library.hpp>

int main() {
  books myBooks;
  users myUsers;
  bookshelvesConstructor(myBooks);
  userBaseConstructor(myUsers);
  mainMenu(myBooks, myUsers);
  return 0;
}