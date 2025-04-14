#pragma once
#include <array>
#include "books.hpp"
#include "users.hpp"

using namespace std;

extern const array<const char*, 5> menuItems;
extern const array<const char*, 6> subMenuItems1;
extern const array<const char*, 6> subMenuItems2;
extern const array<const char*, 6> subMenuItems5;

// void userBaseConstructor(users &users);

char printSubMenu(const array<const char*, 6> &subMenuItems);
void handleReaderSubMenu(char subOption, users &users);
void handleBookSubMenu(char subOption, books &books);
void handleStatsSubMenu(char subOption, const books &books, const users &users);
void subMenu(int mainOption, const array<const char*, 6> &subMenuItems, books &books, users &users);
int printMenu(const array<const char*, 5> &menuItems);
void mainMenuSwitch(int option, const array<const char*, 5> &menuItems, books &books, users &users);
void mainMenu(books &books, users &users);

// Stats functions (temporary signatures)
void countBorrowedBooks(const books &books, const users &users);
void listOverdueReaders(const users &users);