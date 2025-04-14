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
const array<const char*, 5> menuItems {main1, main2, main3, main4, main5};

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

  cout << notice_prompt << endl;
  for (size_t i = 0; i < subMenuItems.size(); ++i) {
    cout << (char)('a' + i) << ". " << subMenuItems[i] << endl; 
  }
  cout << select_prompt;

  char subOption {};
  cin >> subOption;
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

int printMenu(const array<const char*, 5> &menuItems) {
  cout << dashLine << endl;
  cout << "Danh mục chức năng chính:" << endl;

  for (int i = 0; i < menuItems.size(); ++i) {
    cout << i + 1 << ". " << menuItems[i] << endl;
  }
  cout << "Vui lòng chọn chức năng để tiếp tục: ";

  int option {};
  cin >> option;
  cout << dashLine << endl;

  return option;
}

void mainMenuSwitch(int option, const array<const char*, 5> &menuItems, books &books, users &users) {
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
      cout << "Chức năng lập phiếu mượn sách chưa được triển khai." << endl;
      break;
    case 4:
      cout << notice_prompt << menuItems[3] << endl;
      cout << "Chức năng lập phiếu trả sách chưa được triển khai." << endl;
      break;
    case 5:
      cout << notice_prompt << menuItems[4] << endl;
      subMenu(option, subMenuItems5, books, users);
      break;
    default:
      cout << "Lựa chọn không hợp lệ." << endl;
      break;
  }
}

void mainMenu(books &books, users &users) {
  const char invalid_prompt[] = "Lựa chọn không hợp lệ. Vui lòng chọn lại.";
  int option;
  do {
    option = printMenu(menuItems);
    if (option >= 1 && option <= 5) {
      mainMenuSwitch(option, menuItems, books, users);
      cout << "Nhấn Enter để tiếp tục hoặc 'q' để thoát: ";
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      char cont;
      cin.get(cont);
      if (tolower(cont) == 'q') break;
    } else {
      cout << invalid_prompt << endl;
    }
  } while (true);
}

// void userBaseConstructor(users &users) {
//   const char userbase_prompt[] {"Hoàn tất khởi tạo userbase!"};
  
//   users = {};
  
//   // Sample user
//   strncpy(users[0][0].data(), "DG001", USERNAME_MAXLENGTH);
//   strncpy(users[0][1].data(), "Nguyen Van A", USERNAME_MAXLENGTH);
//   strncpy(users[0][2].data(), "123456789", USERNAME_MAXLENGTH);
//   strncpy(users[0][3].data(), "01/01/1990", USERNAME_MAXLENGTH);
//   strncpy(users[0][4].data(), "Nam", USERNAME_MAXLENGTH);
//   strncpy(users[0][5].data(), "nva@example.com", USERNAME_MAXLENGTH);
//   strncpy(users[0][6].data(), "Hanoi", USERNAME_MAXLENGTH);
//   strncpy(users[0][7].data(), "01/01/2023", USERNAME_MAXLENGTH);
//   strncpy(users[0][8].data(), "01/01/2024", USERNAME_MAXLENGTH);
  
//   cout << ".\n.\n" << userbase_prompt << "\n.\n.\n";
// }

void countBorrowedBooks(const books &books, const users &users) {
  cout << "Thống kê sách đang mượn (chưa triển khai)." << endl;
}

void listOverdueReaders(const users &users) {
  cout << "Danh sách độc giả trễ hạn (chưa triển khai)." << endl;
}