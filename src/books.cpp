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
  // Find first empty slot
  int index = -1;
  for (int i = 0; i < BOOKCOUNT_MAX; ++i) {
      bool isEmpty = true;
      for (size_t j = 0; j < BOOKATT_COUNT; ++j) {
          if (books[i][j][0] != '\0') {
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
      cout << "Thư viện đã đầy. Không thể thêm sách." << endl;
      return;
  }

  for (size_t i = 0; i < book_atts.size(); ++i) {
      cout << "Nhập " << book_atts[i] << ": ";
      cin.getline(books[index][i].data(), BOOKNAME_MAXLENGTH);
  }

  cout << "Đã thêm sách." << endl;
  displayBook(index, books);

  // Clear buffer before returning
  // cin.clear();
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int findBookIndexByISBN(const books &books, const char* isbn) {
    // Find index of ISBN in book_atts
    size_t isbnAttrIndex = 0;
    for (size_t i = 0; i < book_atts.size(); ++i) {
        if (strcmp(book_atts[i], "ISBN") == 0) {
            isbnAttrIndex = i;
            break;
        }
    }

    // Search for book with matching ISBN
    for (int i = 0; i < BOOKCOUNT_MAX; ++i) {
        if (strcmp(books[i][isbnAttrIndex].data(), isbn) == 0) {
            return i; // Found match, return index
        }
    }

    return -1; // Book not found
}

int findBookIndexByTittle(const books &books, const char* tittle) {
    // Find index of Title in book_atts
    size_t titleAttrIndex = 0;
    for (size_t i = 0; i < book_atts.size(); ++i) {
        if (strcmp(book_atts[i], "Ten sach") == 0) {
            titleAttrIndex = i;
            break;
        }
    }

    // Search for book with matching Title
    for (int i = 0; i < BOOKCOUNT_MAX; ++i) {
        if (strcmp(books[i][titleAttrIndex].data(), tittle) == 0) {
            return i; // Found match, return index
        }
    }

    return -1; // Book not found
}

int selectBookAttribute(int n) {
    // Validate attribute choice
    if (n < 1 || n > static_cast<int>(book_atts.size())) {
        cout << "Thuộc tính không hợp lệ." << endl;
        return -1;
    }

    // Return zero-based index
    return n - 1;
}

int findBook(const books &books) {
    // Prompt user to choose search method
    cout << "Tìm sách bằng:" << endl;
    cout << "1. ISBN" << endl;
    cout << "2. Tên sách" << endl;
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
    int bookIndex = -1;
    char searchValue[BOOKNAME_MAXLENGTH];
    
    if (choice == 1) {
        cout << "Nhập ISBN: ";
        cin.getline(searchValue, BOOKNAME_MAXLENGTH);
        bookIndex = findBookIndexByISBN(books, searchValue);
    } else if (choice == 2) {
        cout << "Nhập Tên sách: ";
        cin.getline(searchValue, BOOKNAME_MAXLENGTH);
        bookIndex = findBookIndexByTittle(books, searchValue);
    } else {
        cout << "Lựa chọn không hợp lệ." << endl;
        return -1;
    }

    // Check if book was found
    if (bookIndex == -1) {
        cout << "Không tìm thấy sách." << endl;
        return -1;
    }

    return bookIndex;
}

void editBook(books &books) {
    // Find book index using the reusable function
    int bookIndex = findBook(books);
    
    // If no book was found or invalid choice, return
    if (bookIndex == -1) {
        return;
    }

    // Display current book details
    cout << "Thông tin sách hiện tại:" << endl;
    displayBook(bookIndex, books);

    // Prompt user to select attribute to edit
    cout << "Chọn thuộc tính để chỉnh sửa:" << endl;
    for (size_t i = 0; i < book_atts.size(); ++i) {
        cout << i + 1 << ". " << book_atts[i] << endl;
    }
    cout << "Nhập số thứ tự thuộc tính (1-" << book_atts.size() << "): ";
    
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
    int attrIndex = selectBookAttribute(attrChoice);
    if (attrIndex == -1) {
        return;
    }

    // Edit the selected attribute
    cout << "Nhập giá trị mới cho " << book_atts[attrIndex] << ": ";
    cin.getline(books[bookIndex][attrIndex].data(), BOOKNAME_MAXLENGTH);

    cout << "Đã cập nhật sách." << endl;
    displayBook(bookIndex, books);

    // Clear buffer before returning
    // cin.clear();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void deleteBook(books &books) {
    // Find book index using the reusable function
    int bookIndex = findBook(books);
    
    // If no book was found or invalid choice, return
    if (bookIndex == -1) {
        return;
    }

    // Confirm deletion
    cout << "Thông tin sách sẽ bị xóa:" << endl;
    displayBook(bookIndex, books);
    cout << "Bạn có chắc chắn muốn xóa sách này? (1: Có, 0: Không): ";
    
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
        cout << "Hủy xóa sách." << endl;
        return;
    }

    // Clear the book entry by setting all attributes to empty
    for (size_t j = 0; j < book_atts.size(); ++j) {
        books[bookIndex][j].data()[0] = '\0';
    }

    cout << "Đã xóa sách thành công." << endl;

    // Clear buffer before returning
    // cin.clear();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void searchBookByTitle(const books &books) {
  char invalid_prompt[] {"Khong tim thay sach \n"};
  char option_prompt[] {"Vui long nhap ten sach: \n"};
  char searchValue[BOOKNAME_MAXLENGTH];
  
  cout << option_prompt;
  cin.getline(searchValue, BOOKNAME_MAXLENGTH);
  int bookIndex {findBookIndexByTittle(books, searchValue)};

  if (bookIndex >= 0 && bookIndex < BOOKCOUNT_MAX) {
    displayBook(bookIndex, books);
    return;
  } else {
    cout << invalid_prompt;
  }

}

void searchBookByISBN(const books &books) {
  char invalid_prompt[] {"Khong tim thay sach \n"};
  char option_prompt[] {"Vui long nhap ISBN: \n"};
  char searchValue[BOOKNAME_MAXLENGTH];
  
  cout << option_prompt;
  cin.getline(searchValue, BOOKNAME_MAXLENGTH);
  int bookIndex {findBookIndexByISBN(books, searchValue)};

  if (bookIndex >= 0 && bookIndex < BOOKCOUNT_MAX) {
    displayBook(bookIndex, books);
    return;
  } else {
    cout << invalid_prompt;
  }
}

size_t getTotalBooks (const books &books) {
  size_t total {};

  for (size_t i {0}; i < BOOKCOUNT_MAX; ++i) {
    if (books[i][0][0] != '\0') {
      total += atoi(books[i][7].data());
    } 
  }
  return total;
}

void countTotalBooks(const books &books) {
  size_t total = getTotalBooks(books);
  cout << "Tổng số lượng sách hiện có của thư viện: " << total << " quyển" << endl;
}

void countBooksByGenre(const books &books) {
  cout << "Thống kê theo thể loại (chưa triển khai)." << endl;
}