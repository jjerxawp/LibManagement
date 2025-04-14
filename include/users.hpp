#pragma once
#include <array>

using namespace std;

constexpr size_t USERCOUNT_MAX {100};
constexpr size_t USERNAME_MAXLENGTH {100};
constexpr size_t USERATT_COUNT {9};

extern const array<const char*, USERATT_COUNT> user_atts;

using user = array<array<char, USERNAME_MAXLENGTH>, USERATT_COUNT>;
using users = array<user, USERCOUNT_MAX>;

void userBaseConstructor(users &users);
void displayAllUsers(const users &users);
void addUser(users &users);
void editUser(users &users);
void deleteUser(users &users);
void searchUserByCMND(const users &users);
void searchUserByName(const users &users);
void countTotalUsers(const users &users);
void countUsersByGender(const users &users);