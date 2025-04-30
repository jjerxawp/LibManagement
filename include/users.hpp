#pragma once
#include <cstddef>
using namespace std;

constexpr size_t USERCOUNT_MAX {100};
constexpr size_t USERNAME_MAXLENGTH {100};
constexpr size_t USERATT_COUNT {9};

extern const char* user_atts[USERATT_COUNT];

// Define user as a 2D array (USERATT_COUNT attributes, each of USERNAME_MAXLENGTH)
typedef char user[USERATT_COUNT][USERNAME_MAXLENGTH];
// Define users as a 1D array of user (USERCOUNT_MAX entries)
typedef user users[USERCOUNT_MAX];

void userBaseConstructor(users users);
void displayAllUsers(const users users);
void addUser(users users);
void editUser(users users);
void deleteUser(users users);
void searchUserByCMND(const users users);
void searchUserByName(const users users);
void countTotalUsers(const users users);
void countUsersByGender(const users users);
int findUserIndexByID(const users users, const char* cmnd);
int findUser(const users users);
int findEmptyUserSlot(const users users);
void getCurrentDate(char* date, size_t length);
void getExpiryDate(char* expiryDate, size_t length, const char* startDate);
bool validateDate(const char* dateStr);
// bool isValidNumeric(const char* str);