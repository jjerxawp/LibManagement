#pragma once
#include <array>
#include "books.hpp"
#include "users.hpp"
#include <ctime>

using namespace std;

extern const array<const char*, 6> menuItems;
extern const array<const char*, 6> subMenuItems1;
extern const array<const char*, 6> subMenuItems2;
extern const array<const char*, 6> subMenuItems5;

/***/
constexpr size_t TRANSACTION_COUNT_MAX {1000};
constexpr size_t ISBN_LIST_MAX {5}; // Max books per transaction
constexpr size_t DATE_LENGTH {11}; // For dates in format DD/MM/YYYY
constexpr size_t FINE_LENGTH {20}; // For fine amount as string

constexpr int MAX_BORROW_DAYS {7};
constexpr double DAILY_FINE {5000.0}; // 5,000 VND per day
constexpr double LOST_BOOK_MULTIPLIER {2.0}; // 200% of book price

extern const array<const char*, 6> transaction_atts;

using transaction = array<array<char, BOOKNAME_MAXLENGTH>, 8>;
using transactions = array<transaction, TRANSACTION_COUNT_MAX>;

// Menu prototypes
char printSubMenu(const array<const char*, 6> &subMenuItems);
void handleReaderSubMenu(char subOption, users &users);
void handleBookSubMenu(char subOption, books &books);
void handleStatsSubMenu(char subOption, const books &books, const users &users);
void subMenu(int mainOption, const array<const char*, 6> &subMenuItems, books &books, users &users);
int printMenu(const array<const char*, 6> &menuItems);
void mainMenuSwitch(int option, const array<const char*, 6> &menuItems, books &books, users &users, transactions &trans, bool &exitFlag);
void mainMenu(books &books, users &users, transactions &trans);

// Stats functions prototypes
void countBorrowedBooks(const books &books, const users &users);
void listOverdueReaders(const users &users);

// Transaction prototypes
void transactionsConstructor(transactions &trans);
void createTransaction(transactions &trans, const users &users, books &books);
void getCurrentDate(char* date);
void getDueDate(char* date);
void displayTransaction(int transIndex, const transactions &trans);
void returnBook(transactions &trans, books &books, users &users);