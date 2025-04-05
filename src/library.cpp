// library.cpp
#include <iostream>
#include <cctype> 
#include "library.h"    // Include the library header file
// #include "books.h"      // Include the header file for book-related functions

using namespace std;

const char* dashLine = "------------------------------------------------------------";

const char* main1 = "Quản lí độc giả";
const char* main2 = "Quản lí sách";
const char* main3 = "Lập phiếu mượn sách";
const char* main4 = "Lập phiếu trả sách";
const char* main5 = "Các thống kê cơ bản";
array<const char*, 5> menuItems = {main1, main2, main3, main4, main5};

const char* sub1_a = "Xem danh sách độc giả trong thư viện.";
const char* sub1_b = "Thêm độc giả.";
const char* sub1_c = "Chỉnh sửa thông tin một độc giả.";
const char* sub1_d = "Xóa thông tin một độc giả.";
const char* sub1_e = "Tìm kiếm độc giả theo CMND.";
const char* sub1_f = "Tìm kiếm sách theo họ tên.";
array<const char*, 6> subMenuItems1 = {sub1_a, sub1_b, sub1_c, sub1_d, sub1_e, sub1_f};

const char* sub2_a = "Xem danh sách các sách trong thư viện";
const char* sub2_b = "Thêm sách";
const char* sub2_c = "Chỉnh sửa thông tin một quyển sách";
const char* sub2_d = "Xóa thông tin sách";
const char* sub2_e = "Tìm kiếm sách theo ISBN";
const char* sub2_f = "Tìm kiếm sách theo tên sách";
array<const char*, 6> subMenuItems2 = {sub2_a, sub2_b, sub2_c, sub2_d, sub2_e, sub2_f};

const char* sub5_a = "Thống kê số lượng sách trong thư viện";
const char* sub5_b = "Thống kê số lượng sách theo thể loại";
const char* sub5_c = "Thống kê số lượng độc giả";
const char* sub5_d = "Thống kê số lượng độc giả theo giới tính";
const char* sub5_e = "Thống kê số sách đang được mượn";
const char* sub5_f = "Thống kê danh sách độc giả bị trễ hạn";
array<const char*, 6> subMenuItems5 = {sub5_a, sub5_b, sub5_c, sub5_d, sub5_e, sub5_f};

int printMenu(const array<const char*, 5>& menuItems) {
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

char printSubMenu(const array<const char*, 6> subMenuItems) {
  const char* notice_prompt {"Danh sách thao tác: "};
  const char* select_prompt {"Vui lòng chọn thao tác bạn muốn thực hiện: "};

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

void subMenuSwitch (char subOption, const array<const char*, 6> subMenuItems) {
  const char* notice_prompt = "Bạn đã chọn: ";
  switch (subOption) {
    case 'a':
          cout << notice_prompt << subMenuItems[0] << endl;
          break;
      case 'b':
          cout << notice_prompt << subMenuItems[1] << endl;
          break;
      case 'c':
          cout << notice_prompt << subMenuItems[2] << endl;
          break;
      case 'd':
          cout << notice_prompt << subMenuItems[3] << endl;
          break;
      case 'e':
          cout << notice_prompt << subMenuItems[4] << endl;
          break;
      case 'f':
          cout << notice_prompt << subMenuItems[5] << endl;
          break;
      default:
          cout << "Invalid option. This should never happen." << endl;
          break;
  }
}

void subMenu(const array<const char*, 6> subMenuItems) {
  const char* invalid_prompt = "Lựa chọn không hợp lệ. Vui lòng chọn lại.";
  char subOption;
  do {
      subOption = printSubMenu(subMenuItems);
      subOption = tolower(subOption);

      if (subOption >= 'a' && subOption <= 'f') {
          subMenuSwitch(subOption, subMenuItems);
          break;
      } else {
          cout << invalid_prompt << endl;
      }
  } while (true);
}

void mainMenuSwitch (char option) {
  const char* notice_prompt = "Bạn đã chọn: ";
  switch (option) {
        case 1: {
            cout << notice_prompt << main1 << endl;
            subMenu(subMenuItems1);
            break;
        }
        case 2:
            cout << notice_prompt << main2 << endl;
            subMenu(subMenuItems2);
            break;
        case 3:
            cout << notice_prompt << main3 << endl;
            break;
        case 4:
            cout << notice_prompt << main4 << endl;
            break;
        case 5:
            cout << notice_prompt << main5 << endl;
            subMenu(subMenuItems5);
            break;
    }
}

void mainMenu() {

  const char* invalid_prompt = "Lựa chọn không hợp lệ. Vui lòng chọn lại.";
  int option;
  do {
      option = printMenu(menuItems);

      if (option >= 1 && option <= 5) {
          mainMenuSwitch(option);
          break;
      } else {
          cout << invalid_prompt << endl;
      }
  } while (true);
}