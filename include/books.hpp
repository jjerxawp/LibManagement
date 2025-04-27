#pragma once
#include <cstddef>
using namespace std;

constexpr size_t BOOKCOUNT_MAX {100};
constexpr size_t BOOKNAME_MAXLENGTH {200};
constexpr size_t BOOKATT_COUNT {8}; 

extern const char* book_atts[BOOKATT_COUNT];

// Define book as a 2D array (BOOKATT_COUNT attributes, each of BOOKNAME_MAXLENGTH)
typedef char book[BOOKATT_COUNT][BOOKNAME_MAXLENGTH];
// Define books as a 1D array of book (BOOKCOUNT_MAX entries)
typedef book books[BOOKCOUNT_MAX];

void bookshelvesConstructor(books books);
void printTableHeader();
void printBookRow(int bookIndex, const books books);
void displayBook(int bookIndex, const books books);
void displayAllBooks(const books books);
void addBook(books books);
void editBook(books books);
void deleteBook(books books);
void searchBookByISBN(const books books);
void searchBookByTitle(const books books);
void countTotalBooks(const books books);
void countBooksByGenre(const books books);
int findEmptySlot(const books books);
int findBook(const books books);
int findBookIndexByISBN(const books books, const char* isbn);
int findEmptySlot(const books books);
bool isValidNumeric(const char* str);
bool isNonEmptyString(const char* str);
void countTotalBooks(const books books);
void countBooksByGenre(const books books);