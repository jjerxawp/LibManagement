#include <iostream>
#include <users.hpp>

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

void displayAllUsers(const users &users) {
  cout << "Hiển thị danh sách độc giả (chưa triển khai)." << endl;
}

void addUser(users &users) {
  cout << "Thêm độc giả (chưa triển khai)." << endl;
}

void editUser(users &users) {
  cout << "Chỉnh sửa độc giả (chưa triển khai)." << endl;
}

void deleteUser(users &users) {
  cout << "Xóa độc giả (chưa triển khai)." << endl;
}

void searchUserByCMND(const users &users) {
  cout << "Tìm kiếm theo CMND (chưa triển khai)." << endl;
}

void searchUserByName(const users &users) {
  cout << "Tìm kiếm theo họ tên (chưa triển khai)." << endl;
}

void countTotalUsers(const users &users) {
  cout << "Thống kê số lượng độc giả (chưa triển khai)." << endl;
}

void countUsersByGender(const users &users) {
  cout << "Thống kê theo giới tính (chưa triển khai)." << endl;
}