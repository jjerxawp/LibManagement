#include <iostream>
#include <iomanip>
#include "library.hpp"
#include "books.hpp"
#include "users.hpp"

using namespace std;

const char dashLine[] = "------------------------------------------------------------";

const char main1[] = "Quản lí độc giả";
const char main2[] = "Quản lí sách";
const char main3[] = "Lập phiếu mượn sách";
const char main4[] = "Lập phiếu trả sách";
const char main5[] = "Các thống kê cơ bản";
const char main6[] = "Thoát";
const array<const char*, 6> menuItems {main1, main2, main3, main4, main5, main6};

const char sub1_a[] = "Xem danh sách độc giả trong thư viện.";
const char sub1_b[] = "Thêm độc giả.";
const char sub1_c[] = "Chỉnh sửa thông tin một độc giả.";
const char sub1_d[] = "Xóa thông tin một độc giả.";
const char sub1_e[] = "Tìm kiếm độc giả theo CMND.";
const char sub1_f[] = "Tìm kiếm độc giả theo họ tên.";
const array<const char*, 6> subMenuItems1 {sub1_a, sub1_b, sub1_c, sub1_d, sub1_e, sub1_f};

const char sub2_a[] = "Xem danh sách các sách trong thư viện";
const char sub2_b[] = "Thêm sách";
const char sub2_c[] = "Chỉnh sửa thông tin một quyển sách";
const char sub2_d[] = "Xóa thông tin sách";
const char sub2_e[] = "Tìm kiếm sách theo ISBN";
const char sub2_f[] = "Tìm kiếm sách theo tên sách";
const array<const char*, 6> subMenuItems2 {sub2_a, sub2_b, sub2_c, sub2_d, sub2_e, sub2_f};

const char sub5_a[] = "Thống kê số lượng sách trong thư viện";
const char sub5_b[] = "Thống kê số lượng sách theo thể loại";
const char sub5_c[] = "Thống kê số lượng độc giả";
const char sub5_d[] = "Thống kê số lượng độc giả theo giới tính";
const char sub5_e[] = "Thống kê số sách đang được mượn";
const char sub5_f[] = "Thống kê danh sách độc giả bị trễ hạn";
const array<const char*, 6> subMenuItems5 {sub5_a, sub5_b, sub5_c, sub5_d, sub5_e, sub5_f};

char printSubMenu(const array<const char*, 6> &subMenuItems) {
    const char notice_prompt[] {"Danh sách thao tác: "};
    const char select_prompt[] {"Vui lòng chọn thao tác bạn muốn thực hiện: "};
    const char invalid_prompt[] {"Vui lòng chọn một tùy chọn hợp lệ (a-f): "};

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
  const char notice_prompt[] = "Bạn đã chọn: ";
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
      cout << "Lựa chọn không hợp lệ." << endl;
      break;
  }
}

void handleBookSubMenu(char subOption, books &books) {
  const char notice_prompt[] = "Bạn đã chọn: ";
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
      cout << "Lựa chọn không hợp lệ." << endl;
      break;
  }
}

void handleStatsSubMenu(char subOption, const books &books, const users &users) {
  const char notice_prompt[] = "Bạn đã chọn: ";
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
      cout << "Lựa chọn không hợp lệ." << endl;
      break;
  }
}

void subMenu(int mainOption, const array<const char*, 6> &subMenuItems, books &books, users &users) {
  const char invalid_prompt[] = "Lựa chọn không hợp lệ. Vui lòng chọn lại.";
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
        cout << "Danh mục chức năng chính:" << endl;

        for (int i {0}; i < menuItems.size(); ++i) {
            cout << i + 1 << ". " << menuItems[i] << endl;
        }
        cout << "Vui lòng chọn chức năng để tiếp tục: ";

        // Check if input is numeric
        if (cin >> option) {
            // Check if input is within valid range
            if (option >= 1 && option <= menuItems.size()) {
                validInput = true; // Input is valid
            } else {
                cout << "Lựa chọn không hợp lệ. Vui lòng nhập một số từ 1 đến " << menuItems.size() << "." << endl;
            }
        } else {
            cout << "Lựa chọn không hợp lệ. Vui lòng nhập một số." << endl;
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
        }
    } while (!validInput);

    cout << dashLine << endl;
    return option;
}

void mainMenuSwitch(int option, const array<const char*, 6> &menuItems, books &books, users &users, transactions &trans, bool &exitFlag) {
    const char notice_prompt[] = "Bạn đã chọn: ";
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
            cout << "Chức năng lập phiếu trả sách chưa được triển khai." << endl;
            break;
        case 5:
            cout << notice_prompt << menuItems[4] << endl;
            subMenu(option, subMenuItems5, books, users);
            break;
        case 6:
            cout << notice_prompt << menuItems[5] << endl;
            cout << "Đang thoát chương trình..." << endl;
            exitFlag = true; 
            break;
        default:
            cout << "Lựa chọn không hợp lệ." << endl;
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
        
        cout << "Nhấn Enter để tiếp tục hoặc 'q' để thoát: ";

        // Read a single character
        char input = cin.get(); // Read one character

        // Clear any remaining input
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check for 'q' or 'Q'
        if (tolower(input) == 'q') {
            cout << "Đang thoát chương trình..." << endl;
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
                                                      Phiếu mượn/Phiếu trả
 ***************************************************************************************************************************************/

const char trans_att_0[] {"Ma doc gia"};
const char trans_att_1[] {"Ngay muon"};
const char trans_att_2[] {"Ngay tra du kien"};
const char trans_att_3[] {"Ngay tra thuc te"};
const char trans_att_4[] {"ISBN"};
const char trans_att_5[] {"Phi muon sach"};
const char trans_att_6[] {"Phi phat"};
const char trans_att_7[] {"Phi phai tra"};

const array<const char*, 8> transaction_atts {
    trans_att_0, trans_att_1, trans_att_2, trans_att_3, trans_att_4, trans_att_5, trans_att_6, trans_att_7
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
    const char prompt[] {"Hoàn tất khởi tạo danh sách giao dịch!"};
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
    cout << "Tạo phiếu mượn sách\n";
    int userIndex = findUser(users);
    if (userIndex == -1) {
        cout << "Không thể tạo giao dịch: Người dùng không tồn tại.\n";
        return;
    }

    // Find empty transaction slot
    size_t transIndex = 0;
    while (transIndex < TRANSACTION_COUNT_MAX && trans[transIndex][0][0] != '\0') {
        ++transIndex;
    }
    if (transIndex >= TRANSACTION_COUNT_MAX) {
        cout << "Danh sách giao dịch đã đầy!\n";
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
    strncpy(newTrans[6].data(), "0", FINE_LENGTH); // Initial penalty fine is 0

    // Add books and calculate borrowing fee
    cout << "Nhập số lượng sách muốn mượn (tối đa " << ISBN_LIST_MAX << "): ";
    int bookCount;
    while (!(cin >> bookCount) || bookCount < 1 || bookCount > ISBN_LIST_MAX) {
        cout << "Vui lòng nhập số hợp lệ (1-" << ISBN_LIST_MAX << "): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    double totalBorrowFee = 0.0;
    for (int i = 0; i < bookCount; ++i) {
        cout << "Sách " << i + 1 << ":\n";
        int bookIndex = findBook(books);
        if (bookIndex == -1) {
            cout << "Bỏ qua sách này.\n";
            continue;
        }
        
        // Check if book is available
        int copies = atoi(books[bookIndex][7].data());
        if (copies <= 0) {
            cout << "Sách này hiện không có sẵn.\n";
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
        
        // Add borrowing fee (from book's price)
        double bookPrice = atof(books[bookIndex][6].data());
        totalBorrowFee += bookPrice;
        char borrowFeeStr[FINE_LENGTH];
        snprintf(borrowFeeStr, FINE_LENGTH, "%.2f", bookPrice);
        if (i == 0) {
            strncpy(newTrans[5].data(), borrowFeeStr, FINE_LENGTH);
        } else {
            strncat(newTrans[5].data(), ";", FINE_LENGTH - strlen(newTrans[5].data()) - 1);
            strncat(newTrans[5].data(), borrowFeeStr, FINE_LENGTH - strlen(newTrans[5].data()) - 1);
        }
        
        // Decrease book count
        --copies;
        array<char, BOOKNAME_MAXLENGTH> newCount;
        snprintf(newCount.data(), BOOKNAME_MAXLENGTH, "%d", copies);
        strncpy(books[bookIndex][7].data(), newCount.data(), BOOKNAME_MAXLENGTH);
    }

    // Set total amount to pay (Phi muon sach + Phi phat, initially just Phi muon sach)
    char totalAmountStr[FINE_LENGTH];
    snprintf(totalAmountStr, FINE_LENGTH, "%.2f", totalBorrowFee);
    strncpy(newTrans[7].data(), totalAmountStr, FINE_LENGTH);

    cout << "Hoàn tất tạo phiếu mượn!\n";
    
    // Display the created transaction
    displayTransaction(transIndex, trans);
}