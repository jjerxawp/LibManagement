#include <iostream>
#include <iomanip>
#include <limits>
#include <ctime>
#include <cstring>
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

// Ham de kiem tim bi tri trong o vi tri gan nhat tinh tu vi tri [0] trong users array
int findEmptyUserSlot(const users users) {
    for (int i = 0; i < USERCOUNT_MAX; ++i) {
        bool isEmpty = true;
        for (size_t j = 0; j < USERATT_COUNT; ++j) {
            if (users[i][j][0] != '\0') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            return i;
        }
    }
    return -1;
}

// Ham de lay ngay hien tai va format theo dinh dang DD/MM/YYYY
void getCurrentDate(char* date, size_t length) {
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    strftime(date, length, "%d/%m/%Y", local_time);
}

// Ham de lay ngay cach ngay hien tai 48 thang cho gia tri 'Ngay het han' cua the doc gia
void getExpiryDate(char* expiryDate, size_t length, const char* startDate) {
    tm time_struct = {};
    sscanf(startDate, "%d/%d/%d", &time_struct.tm_mday, &time_struct.tm_mon, &time_struct.tm_year);
    time_struct.tm_mon -= 1; 
    time_struct.tm_year -= 1900; 
    
    time_struct.tm_mon += 48;
    while (time_struct.tm_mon >= 12) {
        time_struct.tm_mon -= 12;
        time_struct.tm_year += 1;
    }
    
    time_t expiry_time = mktime(&time_struct);
    tm* expiry_tm = localtime(&expiry_time);
    strftime(expiryDate, length, "%d/%m/%Y", expiry_tm);
}

// Ham khoi tao users array
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
void userBaseConstructor(users users) {
    const char userbase_prompt[] {"Hoan tat khoi tao danh sach doc gia!"};
    
    for (size_t i = 0; i < USERCOUNT_MAX; ++i) {
        for (size_t j = 0; j < USERATT_COUNT; ++j) {
            users[i][j][0] = '\0';
        }
    }
    // Dummy data
    // strncpy(users[0][0], "DG001", USERNAME_MAXLENGTH);
    // strncpy(users[0][1], "Nguyen Van A", USERNAME_MAXLENGTH);
    // strncpy(users[0][2], "123456789", USERNAME_MAXLENGTH);
    // strncpy(users[0][3], "01/01/1990", USERNAME_MAXLENGTH);
    // strncpy(users[0][4], "Nam", USERNAME_MAXLENGTH);
    // strncpy(users[0][5], "nva@example.com", USERNAME_MAXLENGTH);
    // strncpy(users[0][6], "Hanoi", USERNAME_MAXLENGTH);
    // strncpy(users[0][7], "01/01/2019", USERNAME_MAXLENGTH);
    // strncpy(users[0][8], "01/01/2021", USERNAME_MAXLENGTH);
    
    cout << ".\n.\n" << userbase_prompt << "\n.\n.\n";
}

// Ham de print out header cua user table
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

// Ham dung de print tung row cua user[thuoc tinh][gia tri thuoc tinh]
// int userIndex --> index cua user trong users array
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
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

// Ham dung de print out header cua user table + row cua user theo index
// int userIndex --> index cua user trong users array
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
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

// Ham dung de print out header kem tat ca records trong users array
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
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

// Ham dung de add them user vao array
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]

void addUser(users users) {
    int index = findEmptyUserSlot(users);
    if (index == -1) {
        cout << "Thu vien da het cho, vui long dang ky lai vao luc khac" << endl;
        return;
    }

    // Yeu cau user nhap day du cac thong tin cua the sach
    for (size_t i = 0; i < USERATT_COUNT - 2; ++i) {
        cout << "Nhap " << user_atts[i] << ": ";
        cin.getline(users[index][i], USERNAME_MAXLENGTH);
    }

    // Gan ngay lap the doc gia voi ngay hien tai
    char currentDate[11];
    getCurrentDate(currentDate, sizeof(currentDate));
    strncpy(users[index][7], currentDate, USERNAME_MAXLENGTH);
    users[index][7][USERNAME_MAXLENGTH - 1] = '\0';

    // Tinh toan ngay het han cua the doc gia
    char expiryDate[11];
    getExpiryDate(expiryDate, sizeof(expiryDate), currentDate);
    strncpy(users[index][8], expiryDate, USERNAME_MAXLENGTH);
    users[index][8][USERNAME_MAXLENGTH - 1] = '\0';

    cout << "Da them nguoi dung." << endl;
    displayUser(index, users);
}

// Ham dung de tim userIndex theo CMND
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
// const char* cmnd --> pointer tro den gia tri CMND de lookup
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

// Ham dung de tim userIndex theo Ho va Ten
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
// const char* name --> pointer tro den gia tri 'Ho va Ten' de lookup
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

// Ham dung de prompt user chon thuoc tinh de edit
// int n --> gia tri dung de kiem tra tinh hon le
// return type: int --> tra ve index thuoc tinh cua user[thuoc tinh]
int selectUserAttribute(int n) {
    if (n < 1 || n > USERATT_COUNT) {
        cout << "Thuoc tinh khong hop le!" << endl;
        return -1;
    }

    return n - 1;
}

// Ham dung de tim kiem user, dong thoi cho option tim kim theo CMND hoac Ho va Ten
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
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

// Ham dung de chinh sua thong tin doc gia
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
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

// Ham dung de xoa doc gia
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
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

// Ham dung de tim thong tin doc gia theo CMND
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
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

// Ham dung de tim thong tin doc gia theo Ho va Ten
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
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

// Ham dung de check xem gia tri tham so co xuat hien trong mot field cua mang nguoi dung (user) hay khong
// Tham so dau vao la pointer point den char[] cua gia tri can kiem tra: const char* value
// C array cua mang can kiem tra gia tri cua thuoc tinh: const char values[][USERNAME_MAXLENGTH]
bool isValueInArray(const char* value, const char values[][USERNAME_MAXLENGTH], size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(values[i], value) == 0) {
            return true;
        }
    }
    return false;
}

// Ham dung de count nguoi dung theo tham so thuoc tinh
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
// size_t attr_index --> index cua thuoc tinh trong mang
// const char* value --> pointer tro den gia tri can group de tinh tong so luong sach
size_t getTotalUser(const users users, size_t attr_index, const char* value) {
    size_t total = 0;
    for (size_t i = 0; i < USERCOUNT_MAX; ++i) {
        if (users[i][0][0] != '\0' && strcmp(users[i][attr_index], value) == 0) {
            total += 1;
        }
    }
    return total;
}

// Overload function cua ham count nguoi dung, nhung khong cam tham so thuoc tinh
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
size_t getTotalUser(const users users) {
    return getTotalUser(users, 0, users[0][0]);
}

// Ham thuc thi, print table theo format --> Tong so doc gia hien co trong thu vien
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
void countTotalUsers(const users users) {
    // Khai bao format cua table
    const int label_width = 30;
    const int count_width = 15;

    // Goi ham count nguoi dung getTotalUser(), khong can tham so thuoc tinh
    size_t total = getTotalUser(users);

    // Print out head cua bang thong ke
    cout << left;
    cout << "+" << string(label_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;
    cout << "| " << setw(label_width) << "Thong ke" << " | " << setw(count_width) << "So luong" << " |" << endl;
    cout << "+" << string(label_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;

    // Print out noi dung cua thong ke
    if (total == 0) {
        cout << "Khong co nguoi dung trong he thong." << endl;
    } else {
        cout << "| " << setw(label_width) << "Tong so nguoi dung" << " | " << setw(count_width) << total << " |" << endl;
    }

    cout << "+" << string(label_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;
}

// Ham thuc thi dem so luong doc gia theo gioi tinh, print out thong ke theo dang table
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
void countUsersByGender(const users users) {
    // Khai bao mang chua cac gia tri unique cua mien (field) gioi tinh
    char unique_genders[USERCOUNT_MAX][USERNAME_MAXLENGTH];
    size_t gender_counts[USERCOUNT_MAX];
    size_t unique_count = 0;

    // Trich xuat cac gia tri unique cua mien (field) gioi tinh
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

    // Khai bai format cua table 
    const int gender_width = 30;
    const int count_width = 15;

    // Print out table header
    cout << left;
    cout << "+" << string(gender_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;
    cout << "| " << setw(gender_width) << "Gioi tinh" << " | " << setw(count_width) << "So luong" << " |" << endl;
    cout << "+" << string(gender_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;

    // Print out noi duung thong ke 
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