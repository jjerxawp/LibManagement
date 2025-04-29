#include <iostream>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <limits>
#include "library.hpp"
#include "books.hpp"
#include "users.hpp"

using namespace std;

/***************************************************************************************************************************************
                                                      Menu value declaration
 ***************************************************************************************************************************************/

const char dashLine[] = "------------------------------------------------------------";

const char main1[] = "Quan ly doc gia";
const char main2[] = "Quan ly sach";
const char main3[] = "Lap phieu muon sach";
const char main4[] = "Lap phieu tra sach";
const char main5[] = "Cac thong ke co ban";
const char main6[] = "Thoat";
const char* menuItems[6] = {main1, main2, main3, main4, main5, main6};

const char sub1_a[] = "Xem danh sach doc gia trong thu vien";
const char sub1_b[] = "Them doc gia";
const char sub1_c[] = "Chinh sua thong tin mot doc gia";
const char sub1_d[] = "Xoa thong tin mot doc gia";
const char sub1_e[] = "Tim kim doc gia theo CMND";
const char sub1_f[] = "Tim kiem doc gia theo ho ten";
const char* subMenuItems1[6] = {sub1_a, sub1_b, sub1_c, sub1_d, sub1_e, sub1_f};

const char sub2_a[] = "Xem danh sach cac sach trong thu vien";
const char sub2_b[] = "Them sach";
const char sub2_c[] = "Chinh sua thong tin sach";
const char sub2_d[] = "Xoa thong tin sach";
const char sub2_e[] = "Tim kiem sach theo ISBN";
const char sub2_f[] = "Tim kiem sach theo ten sach";
const char* subMenuItems2[6] = {sub2_a, sub2_b, sub2_c, sub2_d, sub2_e, sub2_f};

const char sub5_a[] = "Thong ke so luong sach trong thu vien";
const char sub5_b[] = "Thong ke so luong sach theo the loai";
const char sub5_c[] = "Thong ke so luong doc gia";
const char sub5_d[] = "Thong ke so luong doc gia theo gioi tinh";
const char sub5_e[] = "Thong ke so luong sach dang duoc muon";
const char sub5_f[] = "Thong ke danh sach doc gia tre han";
const char* subMenuItems5[6] = {sub5_a, sub5_b, sub5_c, sub5_d, sub5_e, sub5_f};

/***************************************************************************************************************************************
                                                      Menu
 ***************************************************************************************************************************************/

// Vi cac chuc nang 1, 2, 5 deu co tong cong 5 chuc nang phu --> Co the dung 1 function duy nhat de print out options
// const char* subMenuItems[6] --> c array[6] chua cac gia tri cua subMenuItems
char printSubMenu(const char* subMenuItems[6]) {
    // Declare cac noi dung hien thi
    const char notice_prompt[] {"Danh sach thao tac: "};
    const char select_prompt[] {"Vui long chon thao tac ban muon thuc hien: "};
    const char invalid_prompt[] {"Vui long chon mot tuy chon hop le (a-f): "};

    cout << notice_prompt << endl;
    for (size_t i = 0; i < 6; ++i) {
        cout << (char)('a' + i) << ". " << subMenuItems[i] << endl; 
    }
    cout << select_prompt;

    char subOption;
    while (true) {
        cin >> subOption;
        subOption = tolower(subOption);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (subOption >= 'a' && subOption <= 'f') {
            break;
        }
        cout << invalid_prompt;
    }

    cout << dashLine << endl;
    return subOption;
}

// switch-case khi user chon chuc nang phu trong nhom 'Quan ly nguoi dung'
// char subOption --> subOption la input ma user da chon 
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]

void handleReaderSubMenu(char subOption, users users) {
    const char notice_prompt[] = "Ban da chon: ";
    switch (tolower(subOption)) {
        case 'a':
            cout << notice_prompt << subMenuItems1[0] << endl;
            displayAllUsers(users);
            break;
        case 'b':
            cout << notice_prompt << subMenuItems1[1] << endl;
            addUser(users);
            break;
        case 'c':
            cout << notice_prompt << subMenuItems1[2] << endl;
            editUser(users);
            break;
        case 'd':
            cout << notice_prompt << subMenuItems1[3] << endl;
            deleteUser(users);
            break;
        case 'e':
            cout << notice_prompt << subMenuItems1[4] << endl;
            searchUserByCMND(users);
            break;
        case 'f':
            cout << notice_prompt << subMenuItems1[5] << endl;
            searchUserByName(users);
            break;
        default:
            cout << "Lua chon khong hop le!" << endl;
            break;
    }
}

// switch-case khi user chon chuc nang phu trong nhom 'Quan ly sach'
// char subOption --> subOption la input ma user da chon 
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void handleBookSubMenu(char subOption, books books) {
    const char notice_prompt[] = "Ban da chon: ";
    switch (tolower(subOption)) {
        case 'a':
            cout << notice_prompt << subMenuItems2[0] << endl;
            displayAllBooks(books);
            break;
        case 'b':
            cout << notice_prompt << subMenuItems2[1] << endl;
            addBook(books);
            break;
        case 'c':
            cout << notice_prompt << subMenuItems2[2] << endl;
            editBook(books);
            break;
        case 'd':
            cout << notice_prompt << subMenuItems2[3] << endl;
            deleteBook(books);
            break;
        case 'e':
            cout << notice_prompt << subMenuItems2[4] << endl;
            searchBookByISBN(books);
            break;
        case 'f':
            cout << notice_prompt << subMenuItems2[5] << endl;
            searchBookByTitle(books);
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
    }
}

// switch-case khi user chon chuc nang phu trong nhom 'Cac thong ke co ban'
// char subOption --> subOption la input ma user da chon 
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
void handleStatsSubMenu(char subOption, const transactions trans, const books books, const users users) {
    const char notice_prompt[] = "Ban da chon: ";
    switch (tolower(subOption)) {
        case 'a':
            cout << notice_prompt << subMenuItems5[0] << endl;
            countTotalBooks(books);
            break;
        case 'b':
            cout << notice_prompt << subMenuItems5[1] << endl;
            countBooksByGenre(books);
            break;
        case 'c':
            cout << notice_prompt << subMenuItems5[2] << endl;
            countTotalUsers(users);
            break;
        case 'd':
            cout << notice_prompt << subMenuItems5[3] << endl;
            countUsersByGender(users);
            break;
        case 'e':
            cout << notice_prompt << subMenuItems5[4] << endl;
            listBorrowedBooks(trans, books, users);
            break;
        case 'f':
            cout << notice_prompt << subMenuItems5[5] << endl;
            listOverdueBorrows(trans, books, users);
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
    }
}

// switch-case khi user chon cac nhom chuc nang 1, 2, 5
// char mainOption --> mainOption la input ma user da chon
// const char* subMenuItems[6] --> array chua cac pointer den cac gia tri cua subMenu, tuy thuoc vao Menu-SubMenu ma user da chon
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
void subMenu(int mainOption, const char* subMenuItems[6], transactions trans, books books, users users) {
    const char invalid_prompt[] = "Lua chon khong hop le, vui long chon lai.";
    char subOption;
    do {
        subOption = printSubMenu(subMenuItems);
        subOption = tolower(subOption);

        if (subOption >= 'a' && subOption <= 'f') {
            switch (mainOption) {
                case 1:
                    handleReaderSubMenu(subOption, users);
                    break;
                case 2:
                    handleBookSubMenu(subOption, books);
                    break;
                case 5:
                    handleStatsSubMenu(subOption, trans, books, users);
                    break;
            }
            break;
        } else {
            cout << invalid_prompt << endl;
        }
    } while (true);
}

// Print out noi dung menu, dong thoi lay lua chon tu nguoi dung de truyen cho function mainMenuSwitch()
// return int option --> truyen cho ham mainMenuSwitch()
// const char* menuItems[6] --> C-array chua cac cac pointer tro den noi dung cua cac chuc nang cua Menu
int printMenu(const char* menuItems[6]) {
    int option {0};
    bool validInput = false;

    do {
        cout << dashLine << endl;
        cout << "Danh muc chuc nang chinh: " << endl;

        for (int i {0}; i < 6; ++i) {
            cout << i + 1 << ". " << menuItems[i] << endl;
        }
        cout << "Vui long chon chuc nang de tiep tuc: ";

        if (cin >> option) {
            if (option >= 1 && option <= 6) {
                validInput = true;
            } else {
                cout << "Lua chon khong hop le. Vui long chon mot so tu 1 den 6." << endl;
            }
        } else {
            cout << "Lua chon khong hop le, vui long chon mot so." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!validInput);

    cout << dashLine << endl;
    return option;
}

// switch-case cua main Menu, switch to sub-option
// int option --> tham so tu printMenu() dung lam switch
// const char* menuItems[6] --> array chua cac noi dung chuc nang cua Main Menu
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
void mainMenuSwitch(int option, const char* menuItems[6], books books, users users, transactions trans, bool &exitFlag) {
    const char notice_prompt[] = "Ban da chon: ";
    switch (option) {
        case 1:
            cout << notice_prompt << menuItems[0] << endl;
            subMenu(option, subMenuItems1, trans, books, users);
            break;
        case 2:
            cout << notice_prompt << menuItems[1] << endl;
            subMenu(option, subMenuItems2, trans, books, users);
            break;
        case 3:
            cout << notice_prompt << menuItems[2] << endl;
            createTransaction(trans, users, books);
            break;
        case 4:
            cout << notice_prompt << menuItems[3] << endl;
            returnBook(trans, books, users);
            break;
        case 5:
            cout << notice_prompt << menuItems[4] << endl;
            subMenu(option, subMenuItems5, trans, books, users);
            break;
        case 6:
            cout << notice_prompt << menuItems[5] << endl;
            cout << "Dang thoat chuong trinh..." << endl;
            exitFlag = true; 
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
    }
}

// Call ham printMenu() va truyen gia tri nhan duoc tu printMenu() den switch-case mainMenu de execute cac subOption neu input valid
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
void mainMenu(books books, users users, transactions trans) {
    int option;
    bool exitFlag = false;

    do {
        option = printMenu(menuItems);
        mainMenuSwitch(option, menuItems, books, users, trans, exitFlag);
        
        if (exitFlag) {
            break;
        }
        
        cout << "Nhan Enter de tiep tuc hoac 'q' de thoat: ";

        char input = cin.get();

        if (tolower(input) == 'q') {
            cout << "Dang thoat chuong trinh..." << endl;
            break;
        }
    } while (true);
}

/***************************************************************************************************************************************
                                                      Transactions
 ***************************************************************************************************************************************/

// Declare cac thuoc tinh cua moi transaction
const char trans_att_0[] {"Ma doc gia"};
const char trans_att_1[] {"Ngay muon"};
const char trans_att_2[] {"Ngay tra du kien"};
const char trans_att_3[] {"Ngay tra thuc te"};
const char trans_att_4[] {"ISBN"};
const char trans_att_5[] {"Phi phai tra"};

// Gom cac thuoc tinh thanh array 
const char* transaction_atts[6] = {
    trans_att_0, trans_att_1, trans_att_2, trans_att_3, trans_att_4, trans_att_5
};

// Tim ngay hien tai theo he thong
// char* date --> char array dung de chua gia tri ngay sau khi format
void getCurrentDate(char* date) {
    time_t now = time(nullptr); // Lay gia tri epoch hien tai
    tm* local_time = localtime(&now); // convert theo timezone
    strftime(date, DATE_LENGTH, "%d/%m/%Y", local_time); // ghi de ngay hien tai theo format dd-mm-yyyy vao tham so date
}

// Tim ngay het han (48 thang ke tu ngay hien tai)
// char* date --> char array dung de chua gia tri ngay sau khi format
void getDueDate(char* date) {
    time_t now = time(nullptr);
    now += MAX_BORROW_DAYS * 24 * 60 * 60;
    tm* due_time = localtime(&now);
    strftime(date, DATE_LENGTH, "%d/%m/%Y", due_time);
}

// Convert gia tri ngay sang integer
// Return gia tri ngay theo int de dung cho viec so sanh 2 dates de dang hon
// char* date --> char array dung de chua gia tri ngay sau khi format
int dateToInt(const char* date) {
    char day[3], month[3], year[5];
    strncpy(day, date, 2); day[2] = '\0';
    strncpy(month, date + 3, 2); month[2] = '\0';
    strncpy(year, date + 6, 4); year[4] = '\0';
    
    int d = atoi(day);
    int m = atoi(month);
    int y = atoi(year);
    
    return y * 10000 + m * 100 + d;
}

// So sanh giua ngay het han (expiryDate) va ngay hien tai cua he thong (currentDate)
// Return type: bool
// const char* expiryDate --> pointer tro den gia tri ngay het han
// const char* currentDate --> pointer tro den gia tri ngay hien tai
bool isMembershipExpired(const char* expiryDate, const char* currentDate) {
    int expiryInt = dateToInt(expiryDate);
    int currentInt = dateToInt(currentDate);
    return expiryInt < currentInt;
}

// Khoi tao mang chua cac transactions
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
void transactionsConstructor(transactions trans) {
    const char prompt[] {"Hoan tat khoi tao danh sach giao dich!"};
    
    for (size_t i = 0; i < TRANSACTION_COUNT_MAX; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            trans[i][j][0] = '\0';
        }
    }

    // Dummy data
    // strncpy(trans[0][0], "DG001", BOOKNAME_MAXLENGTH);
    // trans[0][0][BOOKNAME_MAXLENGTH - 1] = '\0';
    
    // strncpy(trans[0][1], "01/04/2025", BOOKNAME_MAXLENGTH);
    // trans[0][1][BOOKNAME_MAXLENGTH - 1] = '\0';
    
    // strncpy(trans[0][2], "08/04/2025", BOOKNAME_MAXLENGTH);
    // trans[0][2][BOOKNAME_MAXLENGTH - 1] = '\0';
    
    // trans[0][3][0] = '\0';
    
    // strncpy(trans[0][4], "0;1", BOOKNAME_MAXLENGTH);
    // trans[0][4][BOOKNAME_MAXLENGTH - 1] = '\0';
    
    // strncpy(trans[0][5], "0", BOOKNAME_MAXLENGTH);
    // trans[0][5][BOOKNAME_MAXLENGTH - 1] = '\0';

    cout << ".\n.\n" << prompt << "\n.\n.\n";
}

// Dung cac gia tri thuoc tinh cua transaction array de print out table header theo format
void printTransactionTableHeader() {
    const int colWidth = 20;
    cout << left;
    for (size_t i = 0; i < 6; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) {
            cout << "-";
        }
    }
    cout << "+" << endl;
    for (size_t i = 0; i < 6; ++i) {
        char buffer[colWidth + 1];
        strncpy(buffer, transaction_atts[i], colWidth);
        buffer[colWidth] = '\0';
        cout << "| " << setw(colWidth) << buffer << " ";
    }
    cout << "|" << endl;
    for (size_t i = 0; i < 6; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) {
            cout << "-";
        }
    }
    cout << "+" << endl;
}

// Print out tung record trong transaction array transaction[thuoc tinh][gia tri thuoc tinh]
// int transIndex --> index cua transaction can print out trong transactions array
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
void printTransactionRow(int transIndex, const transactions trans) {
    const int colWidth = 20;
    cout << left;
    for (size_t i = 0; i < 6; ++i) {
        cout << "| ";
        if (trans[transIndex][i][0] != '\0') {
            char buffer[colWidth + 1];
            strncpy(buffer, trans[transIndex][i], colWidth);
            buffer[colWidth] = '\0';
            cout << setw(colWidth) << buffer << " ";
        } else {
            cout << setw(colWidth) << "N/A" << " ";
        }
    }
    cout << "|" << endl;
}

// Combined function giua printTransactionTableHeader() va printTransactionRow de print 1 transaction voi day du header va record
// int transIndex --> index cua transaction can print out trong transactions array
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
void displayTransaction(int transIndex, const transactions trans) {
    char invalid_index_prompt[] {"Invalid index.\n"};
    if (transIndex < 0 || transIndex >= TRANSACTION_COUNT_MAX) {
        cout << invalid_index_prompt;
        return;
    }
    
    printTransactionTableHeader();
    printTransactionRow(transIndex, trans);
    const int colWidth = 20;
    for (size_t i = 0; i < 6; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
}

void createTransaction(transactions trans, const users users, books books) {
    cout << "Tao phieu muon sach" << endl;
    int userIndex = findUser(users);
    if (userIndex == -1) {
        cout << "Khong the tao giao dich --> Nguoi dung khong ton tai" << endl;
        return;
    }

    // Trich xuat ngay hien tai (currentDate) va kiem tra xem membership co het han hay chua
    char currentDate[DATE_LENGTH];
    getCurrentDate(currentDate);
    size_t expiryDateIndex = 8; // Thuoc tinh 'Ngay het han' co index so 8
    if (isMembershipExpired(users[userIndex][expiryDateIndex], currentDate)) {
        cout << "Khong the tao giao dich --> The sach da het han" << endl;
        return;
    }

    size_t transIndex = 0;
    while (transIndex < TRANSACTION_COUNT_MAX && trans[transIndex][0][0] != '\0') {
        ++transIndex;
    }
    if (transIndex >= TRANSACTION_COUNT_MAX) {
        cout << "Khong the tao giao dich --> Danh sach giao dich da day" << endl;
        return;
    }

    strncpy(trans[transIndex][0], users[userIndex][0], USERNAME_MAXLENGTH);
    
    char dueDate[DATE_LENGTH];
    getCurrentDate(currentDate);
    getDueDate(dueDate);
    strncpy(trans[transIndex][1], currentDate, DATE_LENGTH);
    strncpy(trans[transIndex][2], dueDate, DATE_LENGTH);
    trans[transIndex][3][0] = '\0';
    strncpy(trans[transIndex][5], "0", FINE_LENGTH);

    cout << "Nhap so luong sach can muon (toi da " << ISBN_LIST_MAX << "): ";
    int bookCount;
    while (!(cin >> bookCount) || bookCount < 1 || bookCount > ISBN_LIST_MAX) {
        cout << "Vui long nhap so hop le (1-" << ISBN_LIST_MAX << "): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < bookCount; ++i) {
        cout << "Sach " << i + 1 << ":\n";
        int bookIndex = findBook(books);
        if (bookIndex == -1) {
            cout << "Bo qua sach nay" << endl;
            continue;
        }
        
        int copies = atoi(books[bookIndex][7]);
        if (copies <= 0) {
            cout << "Sach nay hien khong co san" << endl;
            continue;
        }
        
        char isbnList[BOOKNAME_MAXLENGTH];
        strncpy(isbnList, books[bookIndex][0], BOOKNAME_MAXLENGTH);
        if (i == 0) {
            strncpy(trans[transIndex][4], isbnList, BOOKNAME_MAXLENGTH);
        } else {
            strncat(trans[transIndex][4], ";", BOOKNAME_MAXLENGTH - strlen(trans[transIndex][4]) - 1);
            strncat(trans[transIndex][4], isbnList, BOOKNAME_MAXLENGTH - strlen(trans[transIndex][4]) - 1);
        }
        
        --copies;
        char newCount[BOOKNAME_MAXLENGTH];
        snprintf(newCount, BOOKNAME_MAXLENGTH, "%d", copies);
        strncpy(books[bookIndex][7], newCount, BOOKNAME_MAXLENGTH);
    }

    cout << "Hoan tat tao phieu muon!\n";
    
    displayTransaction(transIndex, trans);
}

// Kiem tra date input co dung dinh dang ngay hay khong
// const char* date --> pointer tro den gia tri date can kiem tra
bool validateDate(const char* date) {
    if (strlen(date) != 10) {
        return false;
    }

    if (date[2] != '/' || date[5] != '/') {
        return false;
    }

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(date[i])) {
            return false;
        }
    }

    return true;
}

// Tinh toan so ngay chenh lenh giua 2 input date dau vao
// const char* startDate --> pointer tro den gia tri ngay bat dau
// const char* endDate --> pointer tro den gia tri ngay ket thuc
int calculateDaysDifference(const char* startDate, const char* endDate) {
    tm start = {}, end = {};
    sscanf(startDate, "%d/%d/%d", &start.tm_mday, &start.tm_mon, &start.tm_year);
    sscanf(endDate, "%d/%d/%d", &end.tm_mday, &end.tm_mon, &end.tm_year);
    
    start.tm_mon -= 1;
    end.tm_mon -= 1;
    start.tm_year -= 1900;
    end.tm_year -= 1900;
    
    time_t startTime = mktime(&start);
    time_t endTime = mktime(&end);
    
    return difftime(endTime, startTime) / (24 * 60 * 60);
}

// Tinh toan khoan tien phat (neu co) bao gom Overdue va bookLost
// const char* dueDate --> pointer tro den gia tri 'Ngay tra du kien' cua transaction
// const char* returnDate --> pointer tro den gia 'Ngay tra thuc te' ghi nhan duoc
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// const char* isbn --> pointer tro den gia tri isbn cua transaction
// bool isLost --> ghi nhan sach bi mat (neu co) ti tinh khoan phat cho bookLost
// Return type: Double --> Gia tri khoan phat
double calculateFine(const char* dueDate, const char* returnDate, const books books, const char* isbn, bool isLost) {
    double fine = 0.0;
    
    int bookIndex = -1;
    for (size_t i = 0; i < BOOKCOUNT_MAX; ++i) {
        if (strcmp(books[i][0], isbn) == 0) {
            bookIndex = i;
            break;
        }
    }
    
    if (bookIndex == -1) {
        return 0.0;
    }
    
    if (!isLost) {
        int daysOverdue = calculateDaysDifference(dueDate, returnDate);
        if (daysOverdue > 0) {
            fine += daysOverdue * DAILY_FINE;
        }
    }
    
    if (isLost) {
        double bookPrice = atof(books[bookIndex][6]);
        fine += bookPrice * LOST_BOOK_MULTIPLIER;
    }
    
    return fine;
}


int findTransactionIndex(const transactions trans, const char* userID) {
    for (size_t i = 0; i < TRANSACTION_COUNT_MAX; ++i) {
        if (strcmp(trans[i][0], userID) == 0 && trans[i][3][0] == '\0') {
            return i;
        }
    }
    return -1;
}

// Ham thuc thi cho viec hoan tra sach
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
void returnBook(transactions trans, books books, users users) {
    cout << "Tra sach" << endl;
    
    int userIndex = findUser(users);
    if (userIndex == -1) {
        cout << "Khong the tra sach --> Nguoi dung khong ton tai" << endl;
        return;
    }
    
    int transIndex = findTransactionIndex(trans, users[userIndex][0]);
    if (transIndex == -1) {
        cout << "Khong tim thay phieu muon cho nguoi dung nay" << endl;
        return;
    }
    
    char returnDate[DATE_LENGTH];
    bool validDate = false;
    do {
        cout << "Nhap ngay tra sach (DD/MM/YYYY): ";
        cin.getline(returnDate, DATE_LENGTH);
        if (validateDate(returnDate)) {
            validDate = true;
        } else {
            cout << "Ngay khong hop le. Vui long nhap lai theo dinh dang DD/MM/YYYY (vi du: 01/01/2025)." << endl;
        }
    } while (!validDate);
    
    strncpy(trans[transIndex][3], returnDate, DATE_LENGTH);
    
    char fineStr[FINE_LENGTH] = "0";
    double totalFine = 0.0;
    
    cout << "Co sach nao bi mat khong? (0: Khong, 1: Co): ";
    int hasLostBook;
    cin >> hasLostBook;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    char lostISBN[BOOKNAME_MAXLENGTH] = "";
    if (hasLostBook) {
        cout << "Nhap ISBN cua sach bi mat: ";
        cin.getline(lostISBN, BOOKNAME_MAXLENGTH);
    }
    
    char isbnList[BOOKNAME_MAXLENGTH];
    strncpy(isbnList, trans[transIndex][4], BOOKNAME_MAXLENGTH);
    char* isbn = strtok(isbnList, ";");
    while (isbn != nullptr) {
        bool isLost = (hasLostBook && strcmp(isbn, lostISBN) == 0);
        totalFine += calculateFine(trans[transIndex][2], returnDate, books, isbn, isLost);
        isbn = strtok(nullptr, ";");
    }
    
    snprintf(fineStr, FINE_LENGTH, "%.2f", totalFine);
    
    strncpy(trans[transIndex][5], fineStr, FINE_LENGTH);
    
    strncpy(isbnList, trans[transIndex][4], BOOKNAME_MAXLENGTH);
    isbn = strtok(isbnList, ";");
    while (isbn != nullptr) {
        if (hasLostBook && strcmp(isbn, lostISBN) == 0) {
            isbn = strtok(nullptr, ";");
            continue;
        }
        for (size_t i = 0; i < BOOKCOUNT_MAX; ++i) {
            if (strcmp(books[i][0], isbn) == 0) {
                int copies = atoi(books[i][7]);
                ++copies;
                char newCount[BOOKNAME_MAXLENGTH];
                snprintf(newCount, BOOKNAME_MAXLENGTH, "%d", copies);
                strncpy(books[i][7], newCount, BOOKNAME_MAXLENGTH);
                break;
            }
        }
        isbn = strtok(nullptr, ";");
    }
    
    cout << "Hoan tat tra sach!\n";
    displayTransaction(transIndex, trans);
}

// Ham thuc thi hien thi danh sach cac transactions hien co
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
void listBorrowedBooks(const transactions trans, const books books, const users users) {
    bool hasBorrowedBooks = false;
    
    cout << "\n------ Danh Sach Sach Dang Duoc Muon ------\n";
    cout << setw(15) << left << "Ma Doc Gia"
         << setw(20) << "Ten Doc Gia"
         << setw(15) << "ISBN"
         << setw(50) << "Ten Sach"
         << setw(15) << "Ngay Muon"
         << setw(15) << "Ngay Tra Du Kien" << endl;
    for (int i = 0; i < 125; ++i) cout << '-';
    cout << endl;

    for (size_t i = 0; i < TRANSACTION_COUNT_MAX; ++i) {
        if (trans[i][0][0] != '\0' && trans[i][3][0] == '\0') {
            hasBorrowedBooks = true;
            
            char readerID[USERNAME_MAXLENGTH];
            strncpy(readerID, trans[i][0], USERNAME_MAXLENGTH);
            readerID[USERNAME_MAXLENGTH - 1] = '\0';
            int userIndex = -1;
            for (size_t u = 0; u < USERCOUNT_MAX; ++u) {
                if (users[u][0][0] != '\0' && strcmp(users[u][0], readerID) == 0) {
                    userIndex = u;
                    break;
                }
            }
            
            char userName[USERNAME_MAXLENGTH] = "N/A";
            if (userIndex != -1) {
                strncpy(userName, users[userIndex][1], USERNAME_MAXLENGTH);
                userName[USERNAME_MAXLENGTH - 1] = '\0';
            }

            char isbnList[BOOKNAME_MAXLENGTH];
            strncpy(isbnList, trans[i][4], BOOKNAME_MAXLENGTH);
            isbnList[BOOKNAME_MAXLENGTH - 1] = '\0';

            char* token = strtok(isbnList, ";");
            while (token != nullptr) {
                int bookIndex = -1;
                for (size_t b = 0; b < BOOKCOUNT_MAX; ++b) {
                    if (books[b][0][0] != '\0' && strcmp(books[b][0], token) == 0) {
                        bookIndex = b;
                        break;
                    }
                }

                char bookTitle[BOOKNAME_MAXLENGTH] = "N/A";
                if (bookIndex != -1) {
                    strncpy(bookTitle, books[bookIndex][1], BOOKNAME_MAXLENGTH);
                    bookTitle[BOOKNAME_MAXLENGTH - 1] = '\0';
                }

                cout << setw(15) << left << trans[i][0]
                     << setw(20) << userName
                     << setw(15) << token
                     << setw(50) << bookTitle
                     << setw(15) << trans[i][1]
                     << setw(15) << trans[i][2]
                     << endl;

                token = strtok(nullptr, ";");
            }
        }
    }

    if (!hasBorrowedBooks) {
        cout << "Hien tai khong co sach nao dang duoc muon.\n";
    }
    
    for (int i = 0; i < 125; ++i) cout << '-';
    cout << endl << endl;
}

// DUng ham dateToInt de chuyen 2 ngay can so sanh o dang char[] ve Int cho de so sanh
// const char* expectedDate --> pointer tro den gia tri cua 'Ngay tra du kien'
// const char* currentDate --> pointer tro den gia tri cua 'Ngay hien tai'
bool isOverdue(const char* expectedDate, const char* currentDate) {
    int expectedInt = dateToInt(expectedDate);
    int currentInt = dateToInt(currentDate);
    return expectedInt < currentInt;
}

// Hien thi cac transaction da qua han
// transactions trans --> 3D C-array [Giao dich][Thuoc tinh cua giao dich][Gia tri thuoc tinh]
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// users users --> 3D C-array chua [Nguoi dung][Thuoc tinh nguoi dung][Gia tri cua thuoc tinh]
void listOverdueBorrows(const transactions trans, const books books, const users users) {
    bool hasOverdueBorrows = false;
    
    char currentDate[DATE_LENGTH];
    getCurrentDate(currentDate);
    
    cout << "\n------ Danh Sach Muon Qua Han ------\n";
    cout << setw(10) << left << "Ma Doc Gia"
         << setw(20) << "Ten Doc Gia"
         << setw(15) << "ISBN"
         << setw(50) << "Ten Sach"
         << setw(15) << "Ngay Muon"
         << setw(15) << "Ngay Tra Du Kien" << endl;
    for (int i = 0; i < 125; ++i) cout << '-';
    cout << endl;

    for (size_t i = 0; i < TRANSACTION_COUNT_MAX; ++i) {
        if (trans[i][0][0] != '\0' && trans[i][3][0] == '\0') {
            if (isOverdue(trans[i][2], currentDate)) {
                hasOverdueBorrows = true;
                
                char readerID[USERNAME_MAXLENGTH];
                strncpy(readerID, trans[i][0], USERNAME_MAXLENGTH);
                readerID[USERNAME_MAXLENGTH - 1] = '\0';
                int userIndex = -1;
                for (size_t u = 0; u < USERCOUNT_MAX; ++u) {
                    if (users[u][0][0] != '\0' && strcmp(users[u][0], readerID) == 0) {
                        userIndex = u;
                        break;
                    }
                }
                
                char userName[USERNAME_MAXLENGTH] = "N/A";
                if (userIndex != -1) {
                    strncpy(userName, users[userIndex][1], USERNAME_MAXLENGTH);
                    userName[USERNAME_MAXLENGTH - 1] = '\0';
                }

                char isbnList[BOOKNAME_MAXLENGTH];
                strncpy(isbnList, trans[i][4], BOOKNAME_MAXLENGTH);
                isbnList[BOOKNAME_MAXLENGTH - 1] = '\0';

                char* token = strtok(isbnList, ";");
                while (token != nullptr) {
                    int bookIndex = -1;
                    for (size_t b = 0; b < BOOKCOUNT_MAX; ++b) {
                        if (books[b][0][0] != '\0' && strcmp(books[b][0], token) == 0) {
                            bookIndex = b;
                            break;
                        }
                    }

                    char bookTitle[BOOKNAME_MAXLENGTH] = "N/A";
                    if (bookIndex != -1) {
                        strncpy(bookTitle, books[bookIndex][1], BOOKNAME_MAXLENGTH);
                        bookTitle[BOOKNAME_MAXLENGTH - 1] = '\0';
                    }

                    cout << setw(10) << left << trans[i][0]
                         << setw(20) << userName
                         << setw(15) << token
                         << setw(50) << bookTitle
                         << setw(15) << trans[i][1]
                         << setw(15) << trans[i][2]
                         << endl;

                    token = strtok(nullptr, ";");
                }
            }
        }
    }

    if (!hasOverdueBorrows) {
        cout << "Hien tai khong co muon qua han nao.\n";
    }
    
    for (int i = 0; i < 125; ++i) cout << '-';
    cout << endl << endl;
}