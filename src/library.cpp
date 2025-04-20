#include <iostream>
#include <iomanip>
#include "library.hpp"
#include "books.hpp"
#include "users.hpp"

using namespace std;

const char dashLine[] = "------------------------------------------------------------";

const char main1[] = "Quan ly doc gia";
const char main2[] = "Quan ly sach";
const char main3[] = "Lap phieu muon sach";
const char main4[] = "Lap phieu tra sach";
const char main5[] = "Cac thong ke co ban";
const char main6[] = "Thoat";
const array<const char*, 6> menuItems {main1, main2, main3, main4, main5, main6};

const char sub1_a[] = "Xem danh sach doc gia trong thu vien";
const char sub1_b[] = "Them doc gia";
const char sub1_c[] = "Chinh sua thong tin mot doc gia";
const char sub1_d[] = "Xoa thong tin mot doc gia";
const char sub1_e[] = "Tim kim doc gia theo CMND";
const char sub1_f[] = "Tim kiem doc gia theo ho ten";
const array<const char*, 6> subMenuItems1 {sub1_a, sub1_b, sub1_c, sub1_d, sub1_e, sub1_f};

const char sub2_a[] = "Xem danh sach cac sach trong thu vien";
const char sub2_b[] = "Them sach";
const char sub2_c[] = "Chinh sua thong tin sach";
const char sub2_d[] = "Xoa thong tin sach";
const char sub2_e[] = "Tim kiem sach theo ISBN";
const char sub2_f[] = "Tim kiem sach theo ten sach";
const array<const char*, 6> subMenuItems2 {sub2_a, sub2_b, sub2_c, sub2_d, sub2_e, sub2_f};

const char sub5_a[] = "Thong ke so luong sach trong thu vien";
const char sub5_b[] = "Thong ke so luong sach theo the loai";
const char sub5_c[] = "Thong ke so luong doc gia";
const char sub5_d[] = "Thong ke so luong doc gia theo gioi tinh";
const char sub5_e[] = "Thong ke so luong sach dang duoc muon";
const char sub5_f[] = "Thong ke danh sach doc gia tre han";
const array<const char*, 6> subMenuItems5 {sub5_a, sub5_b, sub5_c, sub5_d, sub5_e, sub5_f};

/***************************************************************************************************************************************
                                                      Menu
 ***************************************************************************************************************************************/

char printSubMenu(const array<const char*, 6> &subMenuItems) {
    const char notice_prompt[] {"Danh sach thao tac: "};
    const char select_prompt[] {"Vui long chon thao tac ban muon thuc hien: "};
    const char invalid_prompt[] {"Vui long chon mot tuy chon hop le (a-f): "};

    cout << notice_prompt << endl;
    for (size_t i = 0; i < subMenuItems.size(); ++i) {
        cout << (char)('a' + i) << ". " << subMenuItems[i] << endl; 
    }
    cout << select_prompt;

    char subOption;
    while (true) {
        cin >> subOption;
        subOption = tolower(subOption);
        // Clear the buffer after reading
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Validate input (a-f)
        if (subOption >= 'a' && subOption <= 'f') {
            break;
        }
        cout << invalid_prompt;
    }

    cout << dashLine << endl;
    return subOption;
}

void handleReaderSubMenu(char subOption, users &users) {
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

void handleBookSubMenu(char subOption, books &books) {
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

void handleStatsSubMenu(char subOption, const books &books, const users &users) {
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
      countBorrowedBooks(books, users);
      break;
    case 'f':
      cout << notice_prompt << subMenuItems5[5] << endl;
      listOverdueReaders(users);
      break;
    default:
      cout << "Lua chon khong hop le." << endl;
      break;
  }
}

void subMenu(int mainOption, const array<const char*, 6> &subMenuItems, books &books, users &users) {
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
          handleStatsSubMenu(subOption, books, users);
          break;
      }
      break;
    } else {
      cout << invalid_prompt << endl;
    }
  } while (true);
}

int printMenu(const array<const char*, 6> &menuItems) {
    int option {0};
    bool validInput = false;

    do {
        cout << dashLine << endl;
        cout << "Danh muc chuc nang chinh: " << endl;

        for (int i {0}; i < menuItems.size(); ++i) {
            cout << i + 1 << ". " << menuItems[i] << endl;
        }
        cout << "Vui long chon chuc nang de tiep tuc: ";

        // Check if input is numeric
        if (cin >> option) {
            // Check if input is within valid range
            if (option >= 1 && option <= menuItems.size()) {
                validInput = true; // Input is valid
            } else {
                cout << "Lua chon khong hop le. Vui long chon mot so tu 1 den " << menuItems.size() << "." << endl;
            }
        } else {
            cout << "Lua chon khong hop le, vui long chon mot so." << endl;
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
        }
    } while (!validInput);

    cout << dashLine << endl;
    return option;
}

void mainMenuSwitch(int option, const array<const char*, 6> &menuItems, books &books, users &users, transactions &trans, bool &exitFlag) {
    const char notice_prompt[] = "Ban da chon: ";
    switch (option) {
        case 1:
            cout << notice_prompt << menuItems[0] << endl;
            subMenu(option, subMenuItems1, books, users);
            break;
        case 2:
            cout << notice_prompt << menuItems[1] << endl;
            subMenu(option, subMenuItems2, books, users);
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
            subMenu(option, subMenuItems5, books, users);
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


void mainMenu(books &books, users &users, transactions &trans) {
    int option;
    bool exitFlag = false;

    do {
        option = printMenu(menuItems);
        mainMenuSwitch(option, menuItems, books, users, trans, exitFlag);
        
        // Check if exit was signaled
        if (exitFlag) {
            break; // Exit the loop (program ends)
        }
        
        cout << "Nhan Enter de tiep tuc hoac 'q' de thoat: ";

        // Read a single character
        char input = cin.get(); // Read one character

        // Clear any remaining input
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check for 'q' or 'Q'
        if (tolower(input) == 'q') {
            cout << "Dang thoat chuong trinh..." << endl;
            break;
        }
        // Empty input (Enter) continues the loop
    } while (true);
}

void countBorrowedBooks(const books &books, const users &users) {
  cout << "Thống kê sách đang mượn (chưa triển khai)." << endl;
}

void listOverdueReaders(const users &users) {
  cout << "Danh sách độc giả trễ hạn (chưa triển khai)." << endl;
}

/***************************************************************************************************************************************
                                                      Transactions
 ***************************************************************************************************************************************/

// const char trans_att_0[] {"Ma doc gia"};
// const char trans_att_1[] {"Ngay muon"};
// const char trans_att_2[] {"Ngay tra du kien"};
// const char trans_att_3[] {"Ngay tra thuc te"};
// const char trans_att_4[] {"ISBN"};
// const char trans_att_5[] {"Phi muon sach"};
// const char trans_att_6[] {"Phi phat"};
// const char trans_att_7[] {"Phi phai tra"};

// const array<const char*, 8> transaction_atts {
//     trans_att_0, trans_att_1, trans_att_2, trans_att_3, trans_att_4, trans_att_5, trans_att_6, trans_att_7
// };

// void getCurrentDate(char* date) {
//     time_t now = time(nullptr);
//     tm* local_time = localtime(&now);
//     strftime(date, DATE_LENGTH, "%d/%m/%Y", local_time);
// }

// void getDueDate(char* date) {
//     time_t now = time(nullptr);
//     now += MAX_BORROW_DAYS * 24 * 60 * 60; // Add 7 days
//     tm* due_time = localtime(&now);
//     strftime(date, DATE_LENGTH, "%d/%m/%Y", due_time);
// }

// void transactionsConstructor(transactions &trans) {
//     const char prompt[] {"Hoan tat khoi tao danh sach giao dich!"};
//     trans = {};
//     cout << ".\n.\n" << prompt << "\n.\n.\n";
// }

// void printTransactionTableHeader() {
//     const int colWidth = 20;
//     cout << left;
//     for (size_t i = 0; i < transaction_atts.size(); ++i) {
//         for (int j = 0; j < colWidth + 3; ++j) cout << "-";
//     }
//     cout << "+" << endl;
//     for (size_t i = 0; i < transaction_atts.size(); ++i) {
//         char buffer[colWidth + 1];
//         strncpy(buffer, transaction_atts[i], colWidth);
//         buffer[colWidth] = '\0';
//         cout << "| " << setw(colWidth) << buffer << " ";
//     }
//     cout << "|" << endl;
//     for (size_t i = 0; i < transaction_atts.size(); ++i) {
//         for (int j = 0; j < colWidth + 3; ++j) cout << "-";
//     }
//     cout << "+" << endl;
// }

// void printTransactionRow(int transIndex, const transactions &trans) {
//     const int colWidth = 20;
//     cout << left;
//     for (size_t i = 0; i < transaction_atts.size(); ++i) {
//         cout << "| ";
//         if (trans[transIndex][i][0] != '\0') {
//             char buffer[colWidth + 1];
//             strncpy(buffer, trans[transIndex][i].data(), colWidth);
//             buffer[colWidth] = '\0';
//             cout << setw(colWidth) << buffer << " ";
//         } else {
//             cout << setw(colWidth) << "N/A" << " ";
//         }
//     }
//     cout << "|" << endl;
// }

// void displayTransaction(int transIndex, const transactions &trans) {
//     char invalid_index_prompt[] {"Invalid index.\n"};
//     if (transIndex < 0 || transIndex >= TRANSACTION_COUNT_MAX) {
//         cout << invalid_index_prompt;
//         return;
//     }
    
//     printTransactionTableHeader();
//     printTransactionRow(transIndex, trans);
//     const int colWidth = 20;
//     for (size_t i = 0; i < transaction_atts.size(); ++i) {
//         for (int j = 0; j < colWidth + 3; ++j) cout << "-";
//     }
//     cout << "+" << endl;
// }

// void createTransaction(transactions &trans, const users &users, books &books) {
//     // Find user
//     cout << "Tao phieu muon sach" << endl;
//     int userIndex = findUser(users);
//     if (userIndex == -1) {
//         cout << "Khong the tao giao dich --> Nguoi dung khong ton tai" << endl;
//         return;
//     }

//     // Find empty transaction slot
//     size_t transIndex = 0;
//     while (transIndex < TRANSACTION_COUNT_MAX && trans[transIndex][0][0] != '\0') {
//         ++transIndex;
//     }
//     if (transIndex >= TRANSACTION_COUNT_MAX) {
//         cout << "Khong the tao giao dich --> Danh sach giao dich da day" << endl;
//         return;
//     }

//     // Initialize transaction
//     transaction& newTrans = trans[transIndex];
    
//     // Set user ID
//     strncpy(newTrans[0].data(), users[userIndex][0].data(), USERNAME_MAXLENGTH);
    
//     // Set dates
//     char currentDate[DATE_LENGTH];
//     char dueDate[DATE_LENGTH];
//     getCurrentDate(currentDate);
//     getDueDate(dueDate);
//     strncpy(newTrans[1].data(), currentDate, DATE_LENGTH);
//     strncpy(newTrans[2].data(), dueDate, DATE_LENGTH);
//     newTrans[3] = {}; // Empty return date
//     strncpy(newTrans[6].data(), "0", FINE_LENGTH); // Initial penalty fine is 0

//     // Add books and calculate borrowing fee
//     cout << "Nhap so luong sach can muon (toi da " << ISBN_LIST_MAX << "): ";
//     int bookCount;
//     while (!(cin >> bookCount) || bookCount < 1 || bookCount > ISBN_LIST_MAX) {
//         cout << "Vui long nhap so hop le (1-" << ISBN_LIST_MAX << "): ";
//         cin.clear();
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');
//     }
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');

//     double totalBorrowFee = 0.0;
//     for (int i = 0; i < bookCount; ++i) {
//         cout << "Sach " << i + 1 << ":\n";
//         int bookIndex = findBook(books);
//         if (bookIndex == -1) {
//             cout << "Bo qua sach nay" << endl;
//             continue;
//         }
        
//         // Check if book is available
//         int copies = atoi(books[bookIndex][7].data());
//         if (copies <= 0) {
//             cout << "Sach nay hien khong co san" << endl;
//             continue;
//         }
        
//         // Add ISBN to transaction
//         array<char, BOOKNAME_MAXLENGTH> isbnList;
//         strncpy(isbnList.data(), books[bookIndex][0].data(), BOOKNAME_MAXLENGTH);
//         if (i == 0) {
//             strncpy(newTrans[4].data(), isbnList.data(), BOOKNAME_MAXLENGTH);
//         } else {
//             strncat(newTrans[4].data(), ";", BOOKNAME_MAXLENGTH - strlen(newTrans[4].data()) - 1);
//             strncat(newTrans[4].data(), isbnList.data(), BOOKNAME_MAXLENGTH - strlen(newTrans[4].data()) - 1);
//         }
        
//         // Add borrowing fee to total
//         double bookPrice = atof(books[bookIndex][6].data());
//         totalBorrowFee += bookPrice;
        
//         // Decrease book count
//         --copies;
//         array<char, BOOKNAME_MAXLENGTH> newCount;
//         snprintf(newCount.data(), BOOKNAME_MAXLENGTH, "%d", copies);
//         strncpy(books[bookIndex][7].data(), newCount.data(), BOOKNAME_MAXLENGTH);
//     }

//     // Set total borrowing fee
//     char borrowFeeStr[FINE_LENGTH];
//     snprintf(borrowFeeStr, FINE_LENGTH, "%.2f", totalBorrowFee);
//     strncpy(newTrans[5].data(), borrowFeeStr, FINE_LENGTH);

//     // Set total amount to pay (Phi muon sach + Phi phat, initially just Phi muon sach)
//     char totalAmountStr[FINE_LENGTH];
//     snprintf(totalAmountStr, FINE_LENGTH, "%.2f", totalBorrowFee);
//     strncpy(newTrans[7].data(), totalAmountStr, FINE_LENGTH);

//     cout << "Hoan tat tao phieu muon!\n";
    
//     // Display the created transaction
//     displayTransaction(transIndex, trans);
// }

// Updated transaction attributes
const char trans_att_0[] {"Ma doc gia"};
const char trans_att_1[] {"Ngay muon"};
const char trans_att_2[] {"Ngay tra du kien"};
const char trans_att_3[] {"Ngay tra thuc te"};
const char trans_att_4[] {"ISBN"};
const char trans_att_5[] {"Phi phai tra"};

const array<const char*, 6> transaction_atts {
    trans_att_0, trans_att_1, trans_att_2, trans_att_3, trans_att_4, trans_att_5
};

void getCurrentDate(char* date) {
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    strftime(date, DATE_LENGTH, "%d/%m/%Y", local_time);
}

void getDueDate(char* date) {
    time_t now = time(nullptr);
    now += MAX_BORROW_DAYS * 24 * 60 * 60; // Add 7 days
    tm* due_time = localtime(&now);
    strftime(date, DATE_LENGTH, "%d/%m/%Y", due_time);
}

void transactionsConstructor(transactions &trans) {
    const char prompt[] {"Hoan tat khoi tao danh sach giao dich!"};
    trans = {};
    cout << ".\n.\n" << prompt << "\n.\n.\n";
}

void printTransactionTableHeader() {
    const int colWidth = 20;
    cout << left;
    for (size_t i = 0; i < transaction_atts.size(); ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
    for (size_t i = 0; i < transaction_atts.size(); ++i) {
        char buffer[colWidth + 1];
        strncpy(buffer, transaction_atts[i], colWidth);
        buffer[colWidth] = '\0';
        cout << "| " << setw(colWidth) << buffer << " ";
    }
    cout << "|" << endl;
    for (size_t i = 0; i < transaction_atts.size(); ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
}

void printTransactionRow(int transIndex, const transactions &trans) {
    const int colWidth = 20;
    cout << left;
    for (size_t i = 0; i < transaction_atts.size(); ++i) {
        cout << "| ";
        if (trans[transIndex][i][0] != '\0') {
            char buffer[colWidth + 1];
            strncpy(buffer, trans[transIndex][i].data(), colWidth);
            buffer[colWidth] = '\0';
            cout << setw(colWidth) << buffer << " ";
        } else {
            cout << setw(colWidth) << "N/A" << " ";
        }
    }
    cout << "|" << endl;
}

void displayTransaction(int transIndex, const transactions &trans) {
    char invalid_index_prompt[] {"Invalid index.\n"};
    if (transIndex < 0 || transIndex >= TRANSACTION_COUNT_MAX) {
        cout << invalid_index_prompt;
        return;
    }
    
    printTransactionTableHeader();
    printTransactionRow(transIndex, trans);
    const int colWidth = 20;
    for (size_t i = 0; i < transaction_atts.size(); ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
}

void createTransaction(transactions &trans, const users &users, books &books) {
    // Find user
    cout << "Tao phieu muon sach" << endl;
    int userIndex = findUser(users);
    if (userIndex == -1) {
        cout << "Khong the tao giao dich --> Nguoi dung khong ton tai" << endl;
        return;
    }

    // Find empty transaction slot
    size_t transIndex = 0;
    while (transIndex < TRANSACTION_COUNT_MAX && trans[transIndex][0][0] != '\0') {
        ++transIndex;
    }
    if (transIndex >= TRANSACTION_COUNT_MAX) {
        cout << "Khong the tao giao dich --> Danh sach giao dich da day" << endl;
        return;
    }

    // Initialize transaction
    transaction& newTrans = trans[transIndex];
    
    // Set user ID
    strncpy(newTrans[0].data(), users[userIndex][0].data(), USERNAME_MAXLENGTH);
    
    // Set dates
    char currentDate[DATE_LENGTH];
    char dueDate[DATE_LENGTH];
    getCurrentDate(currentDate);
    getDueDate(dueDate);
    strncpy(newTrans[1].data(), currentDate, DATE_LENGTH);
    strncpy(newTrans[2].data(), dueDate, DATE_LENGTH);
    newTrans[3] = {}; // Empty return date
    strncpy(newTrans[5].data(), "0", FINE_LENGTH); // Initial fine is 0

    // Add books
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
        
        // Check if book is available
        int copies = atoi(books[bookIndex][7].data());
        if (copies <= 0) {
            cout << "Sach nay hien khong co san" << endl;
            continue;
        }
        
        // Add ISBN to transaction
        array<char, BOOKNAME_MAXLENGTH> isbnList;
        strncpy(isbnList.data(), books[bookIndex][0].data(), BOOKNAME_MAXLENGTH);
        if (i == 0) {
            strncpy(newTrans[4].data(), isbnList.data(), BOOKNAME_MAXLENGTH);
        } else {
            strncat(newTrans[4].data(), ";", BOOKNAME_MAXLENGTH - strlen(newTrans[4].data()) - 1);
            strncat(newTrans[4].data(), isbnList.data(), BOOKNAME_MAXLENGTH - strlen(newTrans[4].data()) - 1);
        }
        
        // Decrease book count
        --copies;
        array<char, BOOKNAME_MAXLENGTH> newCount;
        snprintf(newCount.data(), BOOKNAME_MAXLENGTH, "%d", copies);
        strncpy(books[bookIndex][7].data(), newCount.data(), BOOKNAME_MAXLENGTH);
    }

    cout << "Hoan tat tao phieu muon!\n";
    
    // Display the created transaction
    displayTransaction(transIndex, trans);
}

// bool validateDate(const char* date) {
//     // Check length (expecting 10 characters for DD/MM/YYYY)
//     if (strlen(date) != 10) {
//         return false;
//     }

//     // Check for slashes in correct positions
//     if (date[2] != '/' || date[5] != '/') {
//         return false;
//     }

//     // Basic check for digits in DD, MM, YYYY positions
//     for (int i = 0; i < 10; ++i) {
//         if (i == 2 || i == 5) continue; // Skip slashes
//         if (!isdigit(date[i])) {
//             return false;
//         }
//     }

//     return true;
// }

// // Function to calculate days between two dates (DD/MM/YYYY format)
// int calculateDaysDifference(const char* startDate, const char* endDate) {
//     tm start = {}, end = {};
//     sscanf(startDate, "%d/%d/%d", &start.tm_mday, &start.tm_mon, &start.tm_year);
//     sscanf(endDate, "%d/%d/%d", &end.tm_mday, &end.tm_mon, &end.tm_year);
    
//     start.tm_mon -= 1;
//     end.tm_mon -= 1;
//     start.tm_year -= 1900;
//     end.tm_year -= 1900;
    
//     time_t startTime = mktime(&start);
//     time_t endTime = mktime(&end);
    
//     return difftime(endTime, startTime) / (24 * 60 * 60);
// }

// // Function to calculate fine for a single book (overdue or lost)
// double calculateFine(const char* dueDate, const char* returnDate, const books& books, const char* isbn, bool isLost) {
//     double fine = 0.0;
    
//     // Find book
//     int bookIndex = -1;
//     for (size_t i = 0; i < books.size(); ++i) {
//         if (strcmp(books[i][0].data(), isbn) == 0) {
//             bookIndex = i;
//             break;
//         }
//     }
    
//     if (bookIndex == -1) {
//         return 0.0; // Book not found, no fine
//     }
    
//     // Calculate overdue fine if not lost
//     if (!isLost) {
//         int daysOverdue = calculateDaysDifference(dueDate, returnDate);
//         if (daysOverdue > 0) {
//             fine += daysOverdue * DAILY_FINE; // 5,000 VND per day
//         }
//     }
    
//     // Calculate fine for lost book
//     if (isLost) {
//         double bookPrice = atof(books[bookIndex][6].data());
//         fine += bookPrice * LOST_BOOK_MULTIPLIER; // 200% of book price
//     }
    
//     return fine;
// }

// // Function to find the index of a user's non-returned transaction
// int findTransactionIndex(const transactions& trans, const char* userID) {
//     for (size_t i = 0; i < TRANSACTION_COUNT_MAX; ++i) {
//         if (strcmp(trans[i][0].data(), userID) == 0 && 
//             trans[i][3][0] == '\0') { // Check for non-returned transaction
//             return i;
//         }
//     }
//     return -1;
// }

// void returnBook(transactions &trans, books &books, users &users) {
//     cout << "Tra sach" << endl;
    
//     // Find user
//     int userIndex = findUser(users);
//     if (userIndex == -1) {
//         cout << "Khong the tra sach --> Nguoi dung khong ton tai" << endl;
//         return;
//     }
    
//     // Find user's transaction
//     int transIndex = findTransactionIndex(trans, users[userIndex][0].data());
//     if (transIndex == -1) {
//         cout << "Khong tim thay phieu muon cho nguoi dung nay" << endl;
//         return;
//     }
    
//     // Input return date
//     char returnDate[DATE_LENGTH];
//     bool validDate = false;
//     do {
//         cout << "Nhap ngay tra sach (DD/MM/YYYY): ";
//         cin.getline(returnDate, DATE_LENGTH);
//         if (validateDate(returnDate)) {
//             validDate = true;
//         } else {
//             cout << "Ngay khong hop le. Vui long nhap lai theo dinh dang DD/MM/YYYY (vi du: 01/01/2025)." << endl;
//         }
//     } while (!validDate);
    
//     // Set return date
//     strncpy(trans[transIndex][3].data(), returnDate, DATE_LENGTH);
    
//     // Calculate fines
//     char fineStr[FINE_LENGTH] = "0";
//     double totalFine = 0.0;
    
//     // Ask about lost books
//     cout << "Co sach nao bi mat khong? (0: Khong, 1: Co): ";
//     int hasLostBook;
//     cin >> hasLostBook;
//     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
//     char lostISBN[BOOKNAME_MAXLENGTH] = "";
//     if (hasLostBook) {
//         cout << "Nhap ISBN cua sach bi mat: ";
//         cin.getline(lostISBN, BOOKNAME_MAXLENGTH);
//     }
    
//     // Get list of borrowed books
//     char isbnList[BOOKNAME_MAXLENGTH];
//     strncpy(isbnList, trans[transIndex][4].data(), BOOKNAME_MAXLENGTH);
//     char* isbn = strtok(isbnList, ";");
//     int bookCount = 0;
//     while (isbn != nullptr) {
//         ++bookCount;
//         bool isLost = (hasLostBook && strcmp(isbn, lostISBN) == 0);
//         totalFine += calculateFine(trans[transIndex][2].data(), returnDate, books, isbn, isLost);
//         isbn = strtok(nullptr, ";");
//     }
    
//     // Update fine string
//     snprintf(fineStr, FINE_LENGTH, "%.2f", totalFine);
    
//     // Update transaction fines
//     strncpy(trans[transIndex][6].data(), fineStr, FINE_LENGTH);
    
//     // Update total amount to pay
//     double borrowFee = atof(trans[transIndex][5].data());
//     char totalAmountStr[FINE_LENGTH];
//     snprintf(totalAmountStr, FINE_LENGTH, "%.2f", borrowFee + totalFine);
//     strncpy(trans[transIndex][7].data(), totalAmountStr, FINE_LENGTH);
    
//     // Update book copies (for non-lost books)
//     strncpy(isbnList, trans[transIndex][4].data(), BOOKNAME_MAXLENGTH);
//     isbn = strtok(isbnList, ";");
//     while (isbn != nullptr) {
//         // Skip lost book
//         if (hasLostBook && strcmp(isbn, lostISBN) == 0) {
//             isbn = strtok(nullptr, ";");
//             continue;
//         }
//         for (size_t i = 0; i < books.size(); ++i) {
//             if (strcmp(books[i][0].data(), isbn) == 0) {
//                 int copies = atoi(books[i][7].data());
//                 ++copies;
//                 array<char, BOOKNAME_MAXLENGTH> newCount;
//                 snprintf(newCount.data(), BOOKNAME_MAXLENGTH, "%d", copies);
//                 strncpy(books[i][7].data(), newCount.data(), BOOKNAME_MAXLENGTH);
//                 break;
//             }
//         }
//         isbn = strtok(nullptr, ";");
//     }
    
//     cout << "Hoan tat tra sach!\n";
//     displayTransaction(transIndex, trans);
// }

// Function to perform basic validation of date input (DD/MM/YYYY)
bool validateDate(const char* date) {
    // Check length (expecting 10 characters for DD/MM/YYYY)
    if (strlen(date) != 10) {
        return false;
    }

    // Check for slashes in correct positions
    if (date[2] != '/' || date[5] != '/') {
        return false;
    }

    // Basic check for digits in DD, MM, YYYY positions
    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) continue; // Skip slashes
        if (!isdigit(date[i])) {
            return false;
        }
    }

    return true;
}

// Function to calculate days between two dates (DD/MM/YYYY format)
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

// Function to calculate fine for a single book (overdue or lost)
double calculateFine(const char* dueDate, const char* returnDate, const books& books, const char* isbn, bool isLost) {
    double fine = 0.0;
    
    // Find book
    int bookIndex = -1;
    for (size_t i = 0; i < books.size(); ++i) {
        if (strcmp(books[i][0].data(), isbn) == 0) {
            bookIndex = i;
            break;
        }
    }
    
    if (bookIndex == -1) {
        return 0.0; // Book not found, no fine
    }
    
    // Calculate overdue fine if not lost
    if (!isLost) {
        int daysOverdue = calculateDaysDifference(dueDate, returnDate);
        if (daysOverdue > 0) {
            fine += daysOverdue * DAILY_FINE; // 5,000 VND per day
        }
    }
    
    // Calculate fine for lost book
    if (isLost) {
        double bookPrice = atof(books[bookIndex][6].data());
        fine += bookPrice * LOST_BOOK_MULTIPLIER; // 200% of book price
    }
    
    return fine;
}

// Function to find the index of a user's non-returned transaction
int findTransactionIndex(const transactions& trans, const char* userID) {
    for (size_t i = 0; i < TRANSACTION_COUNT_MAX; ++i) {
        if (strcmp(trans[i][0].data(), userID) == 0 && 
            trans[i][3][0] == '\0') { // Check for non-returned transaction
            return i;
        }
    }
    return -1;
}

void returnBook(transactions &trans, books &books, users &users) {
    cout << "Tra sach" << endl;
    
    // Find user
    int userIndex = findUser(users);
    if (userIndex == -1) {
        cout << "Khong the tra sach --> Nguoi dung khong ton tai" << endl;
        return;
    }
    
    // Find user's transaction
    int transIndex = findTransactionIndex(trans, users[userIndex][0].data());
    if (transIndex == -1) {
        cout << "Khong tim thay phieu muon cho nguoi dung nay" << endl;
        return;
    }
    
    // Input return date
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
    
    // Set return date
    strncpy(trans[transIndex][3].data(), returnDate, DATE_LENGTH);
    
    // Calculate fines
    char fineStr[FINE_LENGTH] = "0";
    double totalFine = 0.0;
    
    // Ask about lost books
    cout << "Co sach nao bi mat khong? (0: Khong, 1: Co): ";
    int hasLostBook;
    cin >> hasLostBook;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    char lostISBN[BOOKNAME_MAXLENGTH] = "";
    if (hasLostBook) {
        cout << "Nhap ISBN cua sach bi mat: ";
        cin.getline(lostISBN, BOOKNAME_MAXLENGTH);
    }
    
    // Get list of borrowed books
    char isbnList[BOOKNAME_MAXLENGTH];
    strncpy(isbnList, trans[transIndex][4].data(), BOOKNAME_MAXLENGTH);
    char* isbn = strtok(isbnList, ";");
    while (isbn != nullptr) {
        bool isLost = (hasLostBook && strcmp(isbn, lostISBN) == 0);
        totalFine += calculateFine(trans[transIndex][2].data(), returnDate, books, isbn, isLost);
        isbn = strtok(nullptr, ";");
    }
    
    // Update fine string
    snprintf(fineStr, FINE_LENGTH, "%.2f", totalFine);
    
    // Update transaction fines (now in Phi phai tra)
    strncpy(trans[transIndex][5].data(), fineStr, FINE_LENGTH);
    
    // Update book copies (for non-lost books)
    strncpy(isbnList, trans[transIndex][4].data(), BOOKNAME_MAXLENGTH);
    isbn = strtok(isbnList, ";");
    while (isbn != nullptr) {
        // Skip lost book
        if (hasLostBook && strcmp(isbn, lostISBN) == 0) {
            isbn = strtok(nullptr, ";");
            continue;
        }
        for (size_t i = 0; i < books.size(); ++i) {
            if (strcmp(books[i][0].data(), isbn) == 0) {
                int copies = atoi(books[i][7].data());
                ++copies;
                array<char, BOOKNAME_MAXLENGTH> newCount;
                snprintf(newCount.data(), BOOKNAME_MAXLENGTH, "%d", copies);
                strncpy(books[i][7].data(), newCount.data(), BOOKNAME_MAXLENGTH);
                break;
            }
        }
        isbn = strtok(nullptr, ";");
    }
    
    cout << "Hoan tat tra sach!\n";
    displayTransaction(transIndex, trans);
}