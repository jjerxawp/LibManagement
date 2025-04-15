#include <iostream>
#include <users.hpp>
#include <iomanip>

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

const array<const char*, USERATT_COUNT> user_atts {
  user_att_0, user_att_1, user_att_2, user_att_3, user_att_4,
  user_att_5, user_att_6, user_att_7, user_att_8
};

void userBaseConstructor(users &users) {
  const char userbase_prompt[] {"Hoàn tất khởi tạo userbase!"};
  
  users = {};
  
  // Optional: Sample user
  strncpy(users[0][0].data(), "DG001", USERNAME_MAXLENGTH);
  strncpy(users[0][1].data(), "Nguyen Van A", USERNAME_MAXLENGTH);
  strncpy(users[0][2].data(), "123456789", USERNAME_MAXLENGTH);
  strncpy(users[0][3].data(), "01/01/1990", USERNAME_MAXLENGTH);
  strncpy(users[0][4].data(), "Nam", USERNAME_MAXLENGTH);
  strncpy(users[0][5].data(), "nva@example.com", USERNAME_MAXLENGTH);
  strncpy(users[0][6].data(), "Hanoi", USERNAME_MAXLENGTH);
  strncpy(users[0][7].data(), "01/01/2023", USERNAME_MAXLENGTH);
  strncpy(users[0][8].data(), "01/01/2024", USERNAME_MAXLENGTH);
  
  cout << ".\n.\n" << userbase_prompt << "\n.\n.\n";
}

void printUserTableHeader() {
  const int colWidth = 20;
  cout << left;
  for (size_t i = 0; i < user_atts.size(); ++i) {
    // cout << "+";
    for (int j = 0; j < colWidth + 3; ++j) cout << "-"; // 23 dashes
  }
  cout << "+" << endl;
  for (size_t i = 0; i < user_atts.size(); ++i) {
    char buffer[colWidth + 1];
    strncpy(buffer, user_atts[i], colWidth);
    buffer[colWidth] = '\0';
    cout << "| " << setw(colWidth) << buffer << " ";
  }
  cout << "|" << endl;
  for (size_t i = 0; i < user_atts.size(); ++i) {
    // cout << "+";
    for (int j = 0; j < colWidth + 3; ++j) cout << "-"; // 23 dashes
  }
  cout << "+" << endl;
}

void printUserRow(int userIndex, const users &users) {
  const int colWidth = 20;
  cout << left;
  for (size_t i = 0; i < user_atts.size(); ++i) {
    cout << "| ";
    if (users[userIndex][i][0] != '\0') {
      char buffer[colWidth + 1];
      strncpy(buffer, users[userIndex][i].data(), colWidth);
      buffer[colWidth] = '\0';
      cout << setw(colWidth) << buffer << " ";
    } else {
      cout << setw(colWidth) << "N/A" << " ";
    }
  }
  cout << "|" << endl;
}

void displayUser(int userIndex, const users &users) {
  char invalid_index_prompt[] {"Invalid index.\n"};
  if (userIndex < 0 || userIndex >= USERCOUNT_MAX) {
    cout << invalid_index_prompt;
    return;
  }
  
  printUserTableHeader();
  printUserRow(userIndex, users);
  const int colWidth = 20;
  for (size_t i = 0; i < user_atts.size(); ++i) {
    // cout << "+";
    for (int j = 0; j < colWidth + 3; ++j) cout << "-"; // 23 dashes
  }
  cout << "+" << endl;
}

void displayAllUsers(const users &users) {
  bool hasUser = false;
  
  printUserTableHeader();
  
  for (size_t j = 0; j < USERCOUNT_MAX; ++j) {
    bool isValidBook = false;
    for (size_t i = 0; i < user_atts.size(); ++i) {
      if (users[j][i][0] != '\0') {
        isValidBook = true;
        break;
      }
    }
    if (isValidBook) {
      hasUser = true;
      printUserRow(j, users);
    }
  }
  
  const int colWidth = 20;
  for (size_t i = 0; i < user_atts.size(); ++i) {
    // cout << "+";
    for (int j = 0; j < colWidth + 3; ++j) cout << "-"; // 23 dashes
  }
  cout << "+" << endl;
  
  if (!hasUser) {
    cout << "Không có người dùng.\n" << endl;
  }
}

void addUser(users &users) {
  // Find first empty slot
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
      cout << "Thư viện đã hết chỗ, vui lòng đăng kí lại lần sau" << endl;
      return;
  }

  for (size_t i = 0; i < user_atts.size(); ++i) {
      cout << "Nhập " << user_atts[i] << ": ";
      cin.getline(users[index][i].data(), USERNAME_MAXLENGTH);
  }

  cout << "Đã thêm sách." << endl;
  displayUser(index, users);

  // Clear buffer before returning
  // cin.clear();
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int findUserIndexByID(const users &users, const char* cmnd) {
    // Find index of CMND in user_atts
    size_t idIndex = 0;
    for (size_t i = 0; i < user_atts.size(); ++i) {
        if (strcmp(user_atts[i], "CMND") == 0) {
            idIndex = i;
            break;
        }
    }

    for (int i = 0; i < USERCOUNT_MAX; ++i) {
        if (strcmp(users[i][idIndex].data(), cmnd) == 0) {
            return i; // Found match, return index
        }
    }

    return -1; // User not found
}

int findUserIndexByName(const users &users, const char* name) {
    // Find index of Title in book_atts
    size_t nameIndex = 0;
    for (size_t i = 0; i < user_atts.size(); ++i) {
        if (strcmp(user_atts[i], "Ho ten") == 0) {
            nameIndex = i;
            break;
        }
    }

    // Search for book with matching Title
    for (int i = 0; i < USERCOUNT_MAX; ++i) {
        if (strcmp(users[i][nameIndex].data(), name) == 0) {
            return i; // Found match, return index
        }
    }

    return -1; // Book not found
}

int selectUserAttribute(int n) {
    // Validate attribute choice
    if (n < 1 || n > static_cast<int>(user_atts.size())) {
        cout << "Thuộc tính không hợp lệ." << endl;
        return -1;
    }

    // Return zero-based index
    return n - 1;
}

int findUser(const users &users) {
    // Prompt user to choose search method
    cout << "Tìm người dùng theo:" << endl;
    cout << "1. CMND" << endl;
    cout << "2. Họ và tên" << endl;
    cout << "Nhập lựa chọn (1 hoặc 2): ";
    
    int choice;
    while (!(cin >> choice)) {
        cout << "Vui lòng nhập số (1 hoặc 2): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Get search value and find book index
    int userIndex {-1};
    char searchValue[USERNAME_MAXLENGTH];
    
    if (choice == 1) {
        cout << "Nhập CMND: ";
        cin.getline(searchValue, USERNAME_MAXLENGTH);
        userIndex = findUserIndexByID(users, searchValue);
    } else if (choice == 2) {
        cout << "Nhập Tên người dùng: ";
        cin.getline(searchValue, USERNAME_MAXLENGTH);
        userIndex = findUserIndexByName(users, searchValue);
    } else {
        cout << "Lựa chọn không hợp lệ." << endl;
        return -1;
    }

    // Check if book was found
    if (userIndex == -1) {
        cout << "Không tìm thấy người dùng." << endl;
        return -1;
    }

    return userIndex;
}

void editUser(users &users) {
  int userIndex {findUser(users)};

  if (userIndex == -1) {
    return;
  }

  cout << "Thông tin người dùng hiện tại: " << endl;
  displayUser(userIndex, users);

  // Prompt user to select attribute to edit
  cout << "Chọn thuộc tính để chỉnh sửa:" << endl;
  for (size_t i = 0; i < user_atts.size(); ++i) {
      cout << i + 1 << ". " << user_atts[i] << endl;
  }
  cout << "Nhập số thứ tự thuộc tính (1-" << user_atts.size() << "): ";
  
  int attrChoice;
  while (!(cin >> attrChoice)) {
      cout << "Vui lòng nhập số: ";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  
  // Clear newline left by cin >>
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  // Validate attribute choice using selectBookAttribute
  int attrIndex = selectUserAttribute(attrChoice);
  if (attrIndex == -1) {
      return;
  }

  // Edit the selected attribute
  cout << "Nhập giá trị mới cho " << user_atts[attrIndex] << ": ";
  cin.getline(users[userIndex][attrIndex].data(), USERNAME_MAXLENGTH);

  cout << "Đã cập nhật thông tin người dùng." << endl;
  displayUser(userIndex, users);

  // Clear buffer before returning
  // cin.clear();
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

void deleteUser(users &users) {
    // Find book index using the reusable function
    int userIndex = findUser(users);
    
    // If no book was found or invalid choice, return
    if (userIndex == -1) {
        return;
    }

    // Confirm deletion
    cout << "Người dùng bên dưới sẽ bị xoá:" << endl;
    displayUser(userIndex, users);
    cout << "Bạn có chắc chắn muốn xóa người dùng này này? (1: Có, 0: Không): ";
    
    int confirm;
    while (!(cin >> confirm)) {
        cout << "Vui lòng nhập số (1 hoặc 0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // Clear the buffer after successful input
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm != 1) {
        cout << "Hủy xóa người dùng." << endl;
        return;
    }

    // Clear the book entry by setting all attributes to empty
    for (size_t j = 0; j < user_atts.size(); ++j) {
        users[userIndex][j].data()[0] = '\0';
    }

    cout << "Đã xóa người dùng thành công." << endl;

    // Clear buffer before returning
    // cin.clear();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void searchUserByCMND(const users &users) {
  char invalid_prompt[] {"Khong tim thay nguoi dung \n"};
  char option_prompt[] {"Vui long nhap CMND nguoi dung: \n"};
  char searchValue[USERNAME_MAXLENGTH];
  
  cout << option_prompt;
  cin.getline(searchValue, USERNAME_MAXLENGTH);
  int userIndex {findUserIndexByID(users, searchValue)};

  if (userIndex >= 0 && userIndex < USERCOUNT_MAX) {
    displayUser(userIndex, users);
    return;
  } else {
    cout << invalid_prompt;
  }
}

void searchUserByName(const users &users) {
  char invalid_prompt[] {"Khong tim thay nguoi dung \n"};
  char option_prompt[] {"Vui long nhap ten nguoi dung: \n"};
  char searchValue[USERNAME_MAXLENGTH];
  
  cout << option_prompt;
  cin.getline(searchValue, USERNAME_MAXLENGTH);
  int userIndex{findUserIndexByName(users, searchValue)};

  if (userIndex >= 0 && userIndex < USERCOUNT_MAX) {
    displayUser(userIndex, users);
    return;
  } else {
    cout << invalid_prompt;
  }
}

size_t getTotalUser(const users& users) {
  size_t total {0};

  for (size_t i {0}; i < USERCOUNT_MAX; ++i){
    if (users[i][0][0] != '\0') {
      total += 1;
    }
  }
  return total;
}

void countTotalUsers(const users &users) {
  size_t total = getTotalUser(users);
  cout << "Tổng số lượng người dùng hiện có của thư viện: " << total << " thành viên." << endl;
}

void countUsersByGender(const users &users) {
  cout << "Thống kê theo giới tính (chưa triển khai)." << endl;
}