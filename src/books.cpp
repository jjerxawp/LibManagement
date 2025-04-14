#include <iostream>
#include <iomanip>
#include <books.hpp>

using namespace std;

const char book_att_0[] {"ISBN"};
const char book_att_1[] {"Ten sach"};
const char book_att_2[] {"Tac gia"};
const char book_att_3[] {"Nha xuat ban"};
const char book_att_4[] {"Nam xuat ban"};
const char book_att_5[] {"The loai"};
const char book_att_6[] {"Gia sach"};
const char book_att_7[] {"So quyen"};

const array<const char*, BOOKATT_COUNT> book_atts {
  book_att_0, book_att_1, book_att_2, book_att_3,
  book_att_4, book_att_5, book_att_6, book_att_7
};

void bookshelvesConstructor(books &books) {
  const char bookshelves_prompt[] {"Hoàn tất khởi tạo kệ sách!"};
  
  books = {};
  
  // Sample books
  strncpy(books[0][0].data(), "978-3-16-148410-0", BOOKNAME_MAXLENGTH);
  strncpy(books[0][1].data(), "The Great Gatsby", BOOKNAME_MAXLENGTH);
  strncpy(books[0][2].data(), "F. Scott Fitzgerald", BOOKNAME_MAXLENGTH);
  strncpy(books[0][3].data(), "Scribner", BOOKNAME_MAXLENGTH);
  strncpy(books[0][4].data(), "1925", BOOKNAME_MAXLENGTH);
  strncpy(books[0][5].data(), "Fiction", BOOKNAME_MAXLENGTH);
  strncpy(books[0][6].data(), "10.99", BOOKNAME_MAXLENGTH);
  strncpy(books[0][7].data(), "5", BOOKNAME_MAXLENGTH);

  strncpy(books[1][0].data(), "978-0-14-243733-9", BOOKNAME_MAXLENGTH);
  strncpy(books[1][1].data(), "1984", BOOKNAME_MAXLENGTH);
  strncpy(books[1][2].data(), "George Orwell", BOOKNAME_MAXLENGTH);
  strncpy(books[1][3].data(), "Penguin", BOOKNAME_MAXLENGTH);
  strncpy(books[1][4].data(), "1949", BOOKNAME_MAXLENGTH);
  strncpy(books[1][5].data(), "Dystopian", BOOKNAME_MAXLENGTH);
  strncpy(books[1][6].data(), "8.99", BOOKNAME_MAXLENGTH);
  strncpy(books[1][7].data(), "3", BOOKNAME_MAXLENGTH);

  cout << ".\n.\n" << bookshelves_prompt << endl;
}

void printTableHeader() {
  const int colWidth = 20;
  cout << left;
  for (size_t i = 0; i < book_atts.size(); ++i) {
    // cout << "+";
    for (int j = 0; j < colWidth + 3; ++j) cout << "-"; // 23 dashes
  }
  cout << "+" << endl;
  for (size_t i = 0; i < book_atts.size(); ++i) {
    char buffer[colWidth + 1];
    strncpy(buffer, book_atts[i], colWidth);
    buffer[colWidth] = '\0';
    cout << "| " << setw(colWidth) << buffer << " ";
  }
  cout << "|" << endl;
  for (size_t i = 0; i < book_atts.size(); ++i) {
    // cout << "+";
    for (int j = 0; j < colWidth + 3; ++j) cout << "-"; // 23 dashes
  }
  cout << "+" << endl;
}

void printBookRow(int bookIndex, const books &books) {
  const int colWidth = 20;
  cout << left;
  for (size_t i = 0; i < book_atts.size(); ++i) {
    cout << "| ";
    if (books[bookIndex][i][0] != '\0') {
      char buffer[colWidth + 1];
      strncpy(buffer, books[bookIndex][i].data(), colWidth);
      buffer[colWidth] = '\0';
      cout << setw(colWidth) << buffer << " ";
    } else {
      cout << setw(colWidth) << "N/A" << " ";
    }
  }
  cout << "|" << endl;
}

void displayBook(int bookIndex, const books &books) {
  char invalid_index_prompt[] {"Invalid index.\n"};
  if (bookIndex < 0 || bookIndex >= BOOKCOUNT_MAX) {
    cout << invalid_index_prompt;
    return;
  }
  
  printTableHeader();
  printBookRow(bookIndex, books);
  const int colWidth = 20;
  for (size_t i = 0; i < book_atts.size(); ++i) {
    // cout << "+";
    for (int j = 0; j < colWidth + 3; ++j) cout << "-"; // 23 dashes
  }
  cout << "+" << endl;
}

void displayAllBooks(const books &books) {
  bool hasBooks = false;
  
  printTableHeader();
  
  for (size_t j = 0; j < BOOKCOUNT_MAX; ++j) {
    bool isValidBook = false;
    for (size_t i = 0; i < book_atts.size(); ++i) {
      if (books[j][i][0] != '\0') {
        isValidBook = true;
        break;
      }
    }
    if (isValidBook) {
      hasBooks = true;
      printBookRow(j, books);
    }
  }
  
  const int colWidth = 20;
  for (size_t i = 0; i < book_atts.size(); ++i) {
    // cout << "+";
    for (int j = 0; j < colWidth + 3; ++j) cout << "-"; // 23 dashes
  }
  cout << "+" << endl;
  
  if (!hasBooks) {
    cout << "No books available." << endl;
  }
}

void addBook(books &books) {
  int index;
  cout << "Nhập chỉ số sách (0-" << BOOKCOUNT_MAX - 1 << "): ";
  cin >> index;
  if (index < 0 || index >= BOOKCOUNT_MAX) {
    cout << "Chỉ số không hợp lệ." << endl;
    return;
  }
  bool isOccupied = false;
  for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
    if (books[index][i][0] != '\0') {
      isOccupied = true;
      break;
    }
  }
  if (isOccupied) {
    cout << "Vị trí đã có sách. Vui lòng chọn chỉ số khác." << endl;
    return;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  for (size_t i = 0; i < book_atts.size(); ++i) {
    cout << "Nhập " << book_atts[i] << ": ";
    cin.getline(books[index][i].data(), BOOKNAME_MAXLENGTH);
  }
  cout << "Đã thêm sách." << endl;
}

void editBook(books &books) {
  cout << "Chỉnh sửa sách (chưa triển khai)." << endl;
}

void deleteBook(books &books) {
  cout << "Xóa sách (chưa triển khai)." << endl;
}

void searchBookByISBN(const books &books) {
  cout << "Tìm kiếm theo ISBN (chưa triển khai)." << endl;
}

void searchBookByTitle(const books &books) {
  cout << "Tìm kiếm theo tên sách (chưa triển khai)." << endl;
}

void countTotalBooks(const books &books) {
  cout << "Thống kê số lượng sách (chưa triển khai)." << endl;
}

void countBooksByGenre(const books &books) {
  cout << "Thống kê theo thể loại (chưa triển khai)." << endl;
}