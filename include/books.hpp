#pragma once
#include <array>

using namespace std;

constexpr size_t BOOKCOUNT_MAX {100};
constexpr size_t BOOKNAME_MAXLENGTH {200};
constexpr size_t BOOKATT_COUNT {8}; 

extern const array<const char*, BOOKATT_COUNT> book_atts;

using book = array<array<char, BOOKNAME_MAXLENGTH>, BOOKATT_COUNT>;
using books = array<book, BOOKCOUNT_MAX>;

void bookshelvesConstructor(books &books);
void printTableHeader();
void printBookRow(int bookIndex, const books &books);
void displayBook(int bookIndex, const books &books);
void displayAllBooks(const books &books);
void addBook(books &books);
void editBook(books &books);
void deleteBook(books &books);
void searchBookByISBN(const books &books);
void searchBookByTitle(const books &books);
void countTotalBooks(const books &books);
void countBooksByGenre(const books &books);