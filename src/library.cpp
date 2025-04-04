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


const char* sub1_a = "Xem danh sách độc giả trong thư viện.";
const char* sub1_b = "Thêm độc giả.";
const char* sub1_c = "Chỉnh sửa thông tin một độc giả.";
const char* sub1_d = "Xóa thông tin một độc giả.";
const char* sub1_e = "Tìm kiếm độc giả theo CMND.";
const char* sub1_f = "Tìm kiếm sách theo họ tên.";

int printMenu() {
  cout << dashLine << endl;
  cout << "Danh mục chức năng chính:" << endl;
  cout << "1. " << main1 << endl;
  cout << "2. " << main2 << endl;
  cout << "3. " << main3 << endl;
  cout << "4. " << main4 << endl;
  cout << "5. " << main5 << endl;
  cout << "Vui lòng chọn chức năng để tiếp tục: ";

  int option {};
  cin >> option;
  cout << dashLine << endl;

  return option;
}

char printSubMenu1() {
  const char* notice_prompt {"Danh sách thao tác: "};
  const char* select_prompt {"Vui lòng chọn thao tác bạn muốn thực hiện: "};

  cout << notice_prompt << endl;

  cout << "a. " << sub1_a << endl;
  cout << "b. " << sub1_b << endl;
  cout << "c. " << sub1_c << endl;
  cout << "d. " << sub1_d << endl;
  cout << "e. " << sub1_e << endl;
  cout << "f. " << sub1_f << endl;

  cout << select_prompt;

  char subOption {};
  cin >> subOption;
  cout << dashLine << endl;
  return subOption;
}

void subMenuHandler1 (char subOption) {
  const char* notice_prompt = "Bạn đã chọn: ";
  switch (subOption) {
    case 'a':
          cout << notice_prompt << sub1_a << endl;
          break;
      case 'b':
          cout << notice_prompt << sub1_b << endl;
          break;
      case 'c':
          cout << notice_prompt << sub1_c << endl;
          break;
      case 'd':
          cout << notice_prompt << sub1_d << endl;
          break;
      case 'e':
          cout << notice_prompt << sub1_e << endl;
          break;
      case 'f':
          cout << notice_prompt << sub1_f << endl;
          break;
      default:
          cout << "Invalid option. This should never happen." << endl;
          break;
  }
}

void subMenuSwitch1() {
  const char* invalid_prompt = "Lựa chọn không hợp lệ. Vui lòng chọn lại.";
  char subOption;
  do {
      subOption = printSubMenu1();
      subOption = tolower(subOption);

      if (subOption >= 'a' && subOption <= 'f') {
          subMenuHandler1(subOption);
          break;
      } else {
          cout << invalid_prompt << endl;
      }
  } while (true);
}

void mainMenuHandler (char option) {
  const char* notice_prompt = "Bạn đã chọn: ";
  switch (option) {
        case 1: {
            cout << notice_prompt << main1 << endl;
            subMenuSwitch1();
            break;
        }
        case 2:
            cout << notice_prompt << main2 << endl;
            break;
        case 3:
            cout << notice_prompt << main3 << endl;
            break;
        case 4:
            cout << notice_prompt << main4 << endl;
            break;
        case 5:
            cout << notice_prompt << main5 << endl;
            break;
    }
}

void menuSwitch() {

  const char* invalid_prompt = "Lựa chọn không hợp lệ. Vui lòng chọn lại.";
  int option;
  do {
      option = printMenu();

      if (option >= 1 && option <= 5) {
          mainMenuHandler(option);
          break;
      } else {
          cout << invalid_prompt << endl;
      }
  } while (true);
}