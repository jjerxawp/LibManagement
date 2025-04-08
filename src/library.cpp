// library.cpp
#include <iostream>
#include "library.h"
// #include "books.h"

using namespace std;

const char* dashLine = "------------------------------------------------------------";

const char main1[] = "Quản lí độc giả";
const char main2[] = "Quản lí sách";
const char main3[] = "Lập phiếu mượn sách";
const char main4[] = "Lập phiếu trả sách";
const char main5[] = "Các thống kê cơ bản";
array<const char*, 5> menuItems {main1, main2, main3, main4, main5};

const char sub1_a[] = "Xem danh sách độc giả trong thư viện.";
const char sub1_b[] = "Thêm độc giả.";
const char sub1_c[] = "Chỉnh sửa thông tin một độc giả.";
const char sub1_d[] = "Xóa thông tin một độc giả.";
const char sub1_e[] = "Tìm kiếm độc giả theo CMND.";
const char sub1_f[] = "Tìm kiếm sách theo họ tên.";
array<const char*, 6> subMenuItems1 {sub1_a, sub1_b, sub1_c, sub1_d, sub1_e, sub1_f};

const char sub2_a[] = "Xem danh sách các sách trong thư viện";
const char sub2_b[] = "Thêm sách";
const char sub2_c[] = "Chỉnh sửa thông tin một quyển sách";
const char sub2_d[] = "Xóa thông tin sách";
const char sub2_e[] = "Tìm kiếm sách theo ISBN";
const char sub2_f[] = "Tìm kiếm sách theo tên sách";
array<const char*, 6> subMenuItems2 = {sub2_a, sub2_b, sub2_c, sub2_d, sub2_e, sub2_f};

const char sub5_a[] = "Thống kê số lượng sách trong thư viện";
const char sub5_b[] = "Thống kê số lượng sách theo thể loại";
const char sub5_c[] = "Thống kê số lượng độc giả";
const char sub5_d[] = "Thống kê số lượng độc giả theo giới tính";
const char sub5_e[] = "Thống kê số sách đang được mượn";
const char sub5_f[] = "Thống kê danh sách độc giả bị trễ hạn";
array<const char*, 6> subMenuItems5 = {sub5_a, sub5_b, sub5_c, sub5_d, sub5_e, sub5_f};

char printSubMenu(const array<const char*, 6> subMenuItems) {
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

void subMenuSwitch (char subOption, array<const char*, 6> subMenuItems) {
  
  const char notice_prompt[] = "Bạn đã chọn: ";
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
          cout << "Option never reached" << endl;
          break;
  }
}

void subMenu(array<const char*, 6> subMenuItems) {
  const char invalid_prompt[] = "Lựa chọn không hợp lệ. Vui lòng chọn lại.";
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

int printMenu(const array<const char*, 5> menuItems) {
  /*Hàm nhận một tham số là một mảng hằng, chứa các chức năng chính của ứng dụng quản lý thư viện.
    Hàm sẽ lần lượt in ra các giá trị có trong mảng và yêu cầu người dùng nhập chức năng cần thực hiện.
    Giá trị người dùng nhập sẽ được ghi nhận và lưu vào biến 'option' để thực hiện switch-case.*/
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

void mainMenuSwitch (int option, array<const char*, 5> menuItems) {
  /*Hàm sẽ nhận giá trị 'option' để thực hiện switch-case cho các lựa chọn chức năng của Main Menu*/
  const char notice_prompt[] = "Bạn đã chọn: ";
  switch (option) {
        case 1: {
            cout << notice_prompt << menuItems[0] << endl;
            subMenu(subMenuItems1);
            break;
        }
        case 2:
            cout << notice_prompt << menuItems[1] << endl;
            subMenu(subMenuItems2);
            break;
        case 3:
            cout << notice_prompt << menuItems[2] << endl;
            break;
        case 4:
            cout << notice_prompt << menuItems[3] << endl;
            break;
        case 5:
            cout << notice_prompt << menuItems[4] << endl;
            subMenu(subMenuItems5);
            break;
    }
}

void mainMenu() {

  const char invalid_prompt[] = "Lựa chọn không hợp lệ. Vui lòng chọn lại.";
  int option {};
  do {
      option = printMenu(menuItems);

      if (option >= 1 && option <= 5) {
          mainMenuSwitch(option, menuItems);
          break;
      } else {
          cout << invalid_prompt << endl;
      }
  } while (true);
}

// Khởi tạo thư viện

const size_t BOOKCOUNT_MAX {100};
const size_t BOOKNAME_MAXLENGTH {200};


const char book_att_0[] {"ISBN"};
const char book_att_1[] {"Tên sách"};
const char book_att_2[] {"Tác giả"};
const char book_att_3[] {"Nhà xuất bản"};
const char book_att_4[] {"Năm xuất bản"};
const char book_att_5[] {"Thể loại"};
const char book_att_6[] {"Giá sách"};
const char book_att_7[] {"Số quyển"};

const array<const char*, 8> book_atts {
  book_att_0, book_att_1, book_att_2, book_att_3,
  book_att_4, book_att_5, book_att_6, book_att_7};


void bookshelvesConstructor() {
  const char bookshelves_prompt[] {"Hoàn tất khởi tạo kệ sách!"};

  array<array<array<char, BOOKNAME_MAXLENGTH>, book_atts.size()>, BOOKCOUNT_MAX> books;

  for (size_t i {}; i < BOOKCOUNT_MAX; ++i) {
    for (size_t j {}; j < book_atts.size(); ++j) {
      strncpy(books[i][j].data(), book_atts[j], BOOKNAME_MAXLENGTH - 1);
      books[i][j][BOOKNAME_MAXLENGTH - 1] = '\0';
    }
  }

  cout << ".\n";
  cout << ".\n";  
  cout << bookshelves_prompt << endl;

}

const size_t USERCOUNT_MAX {100};
const size_t USERNAME_MAXLENGTH {100};

const char user_att_0[] {"Mã độc giả"};
const char user_att_1[] {"Họ tên"};
const char user_att_2[] {"CMND"};
const char user_att_3[] {"Ngày sinh"};
const char user_att_4[] {"Giới tính"};
const char user_att_5[] {"Email"};
const char user_att_6[] {"Địa chỉ"};
const char user_att_7[] {"Ngày lập thẻ"};
const char user_att_8[] {"Ngày hết hạn"};

const array<const char*, 9> user_atts {
  user_att_0, user_att_1, user_att_2, user_att_3, user_att_4,
  user_att_5, user_att_6, user_att_7, user_att_8};

void userBaseConstructor() {
  const char userbase_prompt[] {"Hoàn tất khởi tạo userbase!"};

  array<array<array<char, USERNAME_MAXLENGTH>, user_atts.size()>, USERCOUNT_MAX> users;

  for (size_t i {}; i < USERCOUNT_MAX; ++i) {
    for (size_t j {}; j < user_atts.size(); ++j) {
      strncpy(users[i][j].data(), user_atts[j], USERNAME_MAXLENGTH - 1);
      users[i][j][USERNAME_MAXLENGTH - 1] = '\0';
    }
  }
  cout << ".\n";
  cout << ".\n";  
  cout << userbase_prompt << endl;
  cout << ".\n";
  cout << ".\n";
}
