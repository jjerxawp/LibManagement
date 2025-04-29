#pragma once
#include "books.hpp"
#include "users.hpp"
#include <ctime>
#include <cstddef>
using namespace std;

// Menu item arrays (replacing std::array with raw C arrays)
extern const char* menuItems[6];
extern const char* subMenuItems1[6];
extern const char* subMenuItems2[6];
extern const char* subMenuItems5[6];

/***/
constexpr size_t TRANSACTION_COUNT_MAX {1000};
constexpr size_t ISBN_LIST_MAX {5}; // Max books per transaction
constexpr size_t DATE_LENGTH {11}; // For dates in format DD/MM/YYYY
constexpr size_t FINE_LENGTH {20}; // For fine amount as string

constexpr int MAX_BORROW_DAYS {7};
constexpr double DAILY_FINE {5000.0}; // 5,000 VND per day
constexpr double LOST_BOOK_MULTIPLIER {2.0}; // 200% of book price

extern const char* transaction_atts[6];

// Define transaction as a 2D array (8 attributes, each of BOOKNAME_MAXLENGTH)
typedef char transaction[8][BOOKNAME_MAXLENGTH];
// Define transactions as a 1D array of transaction (TRANSACTION_COUNT_MAX entries)
typedef transaction transactions[TRANSACTION_COUNT_MAX];

// Menu prototypes
char printSubMenu(const char* subMenuItems[6]);
void handleReaderSubMenu(char subOption, users users);
void handleBookSubMenu(char subOption, books books);
void handleStatsSubMenu(char subOption, const transactions trans, const books books, const users users);
void subMenu(int mainOption, const char* subMenuItems[6], transactions trans, books books, users users);
int printMenu(const char* menuItems[6]);
void mainMenuSwitch(int option, const char* menuItems[6], books books, users users, transactions trans, bool &exitFlag);
void mainMenu(books books, users users, transactions trans);

// Transaction prototypes
void transactionsConstructor(transactions trans);
void createTransaction(transactions trans, const users users, books books);
void getCurrentDate(char* date);
void getDueDate(char* date);
void displayTransaction(int transIndex, const transactions trans);
void returnBook(transactions trans, books books, users users);
void listBorrowedBooks(const transactions trans, const books books, const users users);
void listOverdueBorrows(const transactions trans, const books books, const users users);
bool isMembershipExpired(const char* expiryDate, const char* currentDate);