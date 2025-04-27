#include <iostream>
#include <iomanip>
#include <limits>
#include "users.hpp"

using namespace std;

const char user_att_0[] {"Ma doc gia"};
const char user_att_1[] {"Ho ten"};
const char user_att_2[] {"CMND"};
const char user_att_3[] {"Ngay sinh"};
const char user_att_4[] {"Gioi tinh"};
const char user_att_5[] {"Email"};
const char user_att_6[] {"Dia chi"};
const char user_att_7[] {"Ngay lap the"};
const char user_att_8[] {"Ngay het han"};

const char* user_atts[USERATT_COUNT] = {
    user_att_0, user_att_1, user_att_2, user_att_3, user_att_4,
    user_att_5, user_att_6, user_att_7, user_att_8
};

void userBaseConstructor(users users) {
    const char userbase_prompt[] {"Hoan tat khoi tao danh sach doc gia!"};
    
    for (size_t i = 0; i < USERCOUNT_MAX; ++i) {
        for (size_t j = 0; j < USERATT_COUNT; ++j) {
            users[i][j][0] = '\0';
        }
    }
    
    strncpy(users[0][0], "DG001", USERNAME_MAXLENGTH);
    strncpy(users[0][1], "Nguyen Van A", USERNAME_MAXLENGTH);
    strncpy(users[0][2], "123456789", USERNAME_MAXLENGTH);
    strncpy(users[0][3], "01/01/1990", USERNAME_MAXLENGTH);
    strncpy(users[0][4], "Nam", USERNAME_MAXLENGTH);
    strncpy(users[0][5], "nva@example.com", USERNAME_MAXLENGTH);
    strncpy(users[0][6], "Hanoi", USERNAME_MAXLENGTH);
    strncpy(users[0][7], "01/01/2023", USERNAME_MAXLENGTH);
    strncpy(users[0][8], "01/01/2024", USERNAME_MAXLENGTH);
    
    cout << ".\n.\n" << userbase_prompt << "\n.\n.\n";
}

void printUserTableHeader() {
    const int colWidth = 20;
    cout << left;
    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        char buffer[colWidth + 1];
        strncpy(buffer, user_atts[i], colWidth);
        buffer[colWidth] = '\0';
        cout << "| " << setw(colWidth) << buffer << " ";
    }
    cout << "|" << endl;
    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
}

void printUserRow(int userIndex, const users users) {
    const int colWidth = 20;
    cout << left;
    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        cout << "| ";
        if (users[userIndex][i][0] != '\0') {
            char buffer[colWidth + 1];
            strncpy(buffer, users[userIndex][i], colWidth);
            buffer[colWidth] = '\0';
            cout << setw(colWidth) << buffer << " ";
        } else {
            cout << setw(colWidth) << "N/A" << " ";
        }
    }
    cout << "|" << endl;
}

void displayUser(int userIndex, const users users) {
    char invalid_index_prompt[] {"Invalid index.\n"};
    if (userIndex < 0 || userIndex >= USERCOUNT_MAX) {
        cout << invalid_index_prompt;
        return;
    }
    
    printUserTableHeader();
    printUserRow(userIndex, users);
    const int colWidth = 20;
    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
}

void displayAllUsers(const users users) {
    bool hasUser = false;
    
    printUserTableHeader();
    
    for (size_t j = 0; j < USERCOUNT_MAX; ++j) {
        bool isValidUser = false;
        for (size_t i = 0; i < USERATT_COUNT; ++i) {
            if (users[j][i][0] != '\0') {
                isValidUser = true;
                break;
            }
        }
        if (isValidUser) {
            hasUser = true;
            printUserRow(j, users);
        }
    }
    
    const int colWidth = 20;
    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
    
    if (!hasUser) {
        cout << "Khong co nguoi dung trong he thong.\n" << endl;
    }
}

void addUser(users users) {
    int index = -1;
    for (int i = 0; i < USERCOUNT_MAX; ++i) {
        bool isEmpty = true;
        for (size_t j = 0; j < USERATT_COUNT; ++j) {
            if (users[i][j][0] != '\0') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Thu vien da het cho, vui long dang ky lai vao luc khac" << endl;
        return;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        cout << "Nhap " << user_atts[i] << ": ";
        cin.getline(users[index][i], USERNAME_MAXLENGTH);
    }

    cout << "Da them nguoi dung." << endl;
    displayUser(index, users);
}

int findUserIndexByID(const users users, const char* cmnd) {
    size_t idIndex = 0;
    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        if (strcmp(user_atts[i], "CMND") == 0) {
            idIndex = i;
            break;
        }
    }

    for (int i = 0; i < USERCOUNT_MAX; ++i) {
        if (strcmp(users[i][idIndex], cmnd) == 0) {
            return i;
        }
    }

    return -1;
}

int findUserIndexByName(const users users, const char* name) {
    size_t nameIndex = 0;
    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        if (strcmp(user_atts[i], "Ho ten") == 0) {
            nameIndex = i;
            break;
        }
    }

    for (int i = 0; i < USERCOUNT_MAX; ++i) {
        if (strcmp(users[i][nameIndex], name) == 0) {
            return i;
        }
    }

    return -1;
}

int selectUserAttribute(int n) {
    if (n < 1 || n > USERATT_COUNT) {
        cout << "Thuoc tinh khong hop le!" << endl;
        return -1;
    }

    return n - 1;
}

int findUser(const users users) {
    cout << "Tim nguoi dung theo:" << endl;
    cout << "1. CMND" << endl;
    cout << "2. Ho va ten" << endl;
    cout << "Nhap lua chon (1 hoac 2): ";
    
    int choice;
    while (!(cin >> choice)) {
        cout << "Vui long nhap so (1 hoac 2): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int userIndex = -1;
    char searchValue[USERNAME_MAXLENGTH];
    
    if (choice == 1) {
        cout << "Nhap CMND: ";
        cin.getline(searchValue, USERNAME_MAXLENGTH);
        userIndex = findUserIndexByID(users, searchValue);
    } else if (choice == 2) {
        cout << "Nhap 'Ten nguoi dung': ";
        cin.getline(searchValue, USERNAME_MAXLENGTH);
        userIndex = findUserIndexByName(users, searchValue);
    } else {
        cout << "Lua chon khong hop le." << endl;
        return -1;
    }

    if (userIndex == -1) {
        cout << "Khong tim thay nguoi dung." << endl;
        return -1;
    }

    return userIndex;
}

void editUser(users users) {
    int userIndex = findUser(users);

    if (userIndex == -1) {
        return;
    }

    cout << "Thong tin nguoi dung hien tai: " << endl;
    displayUser(userIndex, users);

    cout << "Chon thuoc tinh can cap nhat:" << endl;
    for (size_t i = 0; i < USERATT_COUNT; ++i) {
        cout << i + 1 << ". " << user_atts[i] << endl;
    }
    cout << "Nhap so thu tu thuoc tinh (1-" << USERATT_COUNT << "): ";
    
    int attrChoice;
    while (!(cin >> attrChoice)) {
        cout << "Vui long nhap so: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int attrIndex = selectUserAttribute(attrChoice);
    if (attrIndex == -1) {
        return;
    }

    cout << "Nhap gia tri moi cho " << user_atts[attrIndex] << ": ";
    cin.getline(users[userIndex][attrIndex], USERNAME_MAXLENGTH);

    cout << "Da cap nhat thong tin nguoi dung!" << endl;
    displayUser(userIndex, users);
}

void deleteUser(users users) {
    int userIndex = findUser(users);
    
    if (userIndex == -1) {
        return;
    }

    cout << "Nguoi dung ben duoi se bi xoa:" << endl;
    displayUser(userIndex, users);
    cout << "Xac nhan xoa nguoi dung (1: Co, 0: Khong): ";
    
    int confirm;
    while (!(cin >> confirm)) {
        cout << "Vui long nhap so (1 hoac 0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm != 1) {
        cout << "Huy xoa nguoi dung." << endl;
        return;
    }

    for (size_t j = 0; j < USERATT_COUNT; ++j) {
        users[userIndex][j][0] = '\0';
    }

    cout << "Da xoa nguoi dung thanh cong!" << endl;
}

void searchUserByCMND(const users users) {
    char invalid_prompt[] {"Khong tim thay nguoi dung \n"};
    char option_prompt[] {"Vui long nhap CMND nguoi dung: \n"};
    char searchValue[USERNAME_MAXLENGTH];
    
    cout << option_prompt;
    cin.getline(searchValue, USERNAME_MAXLENGTH);
    int userIndex = findUserIndexByID(users, searchValue);

    if (userIndex >= 0 && userIndex < USERCOUNT_MAX) {
        displayUser(userIndex, users);
        return;
    } else {
        cout << invalid_prompt;
    }
}

void searchUserByName(const users users) {
    char invalid_prompt[] {"Khong tim thay nguoi dung \n"};
    char option_prompt[] {"Vui long nhap ten nguoi dung: \n"};
    char searchValue[USERNAME_MAXLENGTH];
    
    cout << option_prompt;
    cin.getline(searchValue, USERNAME_MAXLENGTH);
    int userIndex = findUserIndexByName(users, searchValue);

    if (userIndex >= 0 && userIndex < USERCOUNT_MAX) {
        displayUser(userIndex, users);
        return;
    } else {
        cout << invalid_prompt;
    }
}

// Helper function to check if a value is in an array of strings
bool isValueInArray(const char* value, const char values[][USERNAME_MAXLENGTH], size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(values[i], value) == 0) {
            return true;
        }
    }
    return false;
}

// Modified getTotalUser to count users for a specific attribute value
size_t getTotalUser(const users users, size_t attr_index, const char* value) {
    size_t total = 0;
    for (size_t i = 0; i < USERCOUNT_MAX; ++i) {
        if (users[i][0][0] != '\0' && strcmp(users[i][attr_index], value) == 0) {
            total += 1;
        }
    }
    return total;
}

// Overload for total user count (no attribute filtering)
size_t getTotalUser(const users users) {
    return getTotalUser(users, 0, users[0][0]); // Count all valid users
}

void countTotalUsers(const users users) {
    // Table formatting
    const int label_width = 30;
    const int count_width = 15;

    // Count total users
    size_t total = getTotalUser(users);

    // Print table
    cout << left;
    cout << "+" << string(label_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;
    cout << "| " << setw(label_width) << "Thong ke" << " | " << setw(count_width) << "So luong" << " |" << endl;
    cout << "+" << string(label_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;

    if (total == 0) {
        cout << "Khong co nguoi dung trong he thong." << endl;
    } else {
        cout << "| " << setw(label_width) << "Tong so nguoi dung" << " | " << setw(count_width) << total << " |" << endl;
    }

    cout << "+" << string(label_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;
}

void countUsersByGender(const users users) {
    // Array to store unique genders
    char unique_genders[USERCOUNT_MAX][USERNAME_MAXLENGTH];
    size_t gender_counts[USERCOUNT_MAX];
    size_t unique_count = 0;

    // Collect unique genders (Gioi tinh, index 4)
    for (size_t i = 0; i < USERCOUNT_MAX; ++i) {
        if (users[i][0][0] != '\0' && users[i][4][0] != '\0') {
            if (!isValueInArray(users[i][4], unique_genders, unique_count)) {
                strncpy(unique_genders[unique_count], users[i][4], USERNAME_MAXLENGTH);
                unique_genders[unique_count][USERNAME_MAXLENGTH - 1] = '\0';
                gender_counts[unique_count] = getTotalUser(users, 4, unique_genders[unique_count]);
                unique_count++;
            }
        }
    }

    // Table formatting
    const int gender_width = 30;
    const int count_width = 15;

    cout << left;
    cout << "+" << string(gender_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;
    cout << "| " << setw(gender_width) << "Gioi tinh" << " | " << setw(count_width) << "So luong" << " |" << endl;
    cout << "+" << string(gender_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;

    if (unique_count == 0) {
        cout << "Khong co nguoi dung trong he thong." << endl;
    } else {
        for (size_t i = 0; i < unique_count; ++i) {
            cout << "| " << setw(gender_width) << unique_genders[i] << " | ";
            cout << setw(count_width) << gender_counts[i] << " |" << endl;
        }
    }

    cout << "+" << string(gender_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;
}