#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <limits>
#include "books.hpp"

using namespace std;

const char book_att_0[] {"ISBN"};
const char book_att_1[] {"Ten sach"};
const char book_att_2[] {"Tac gia"};
const char book_att_3[] {"Nha xuat ban"};
const char book_att_4[] {"Nam xuat ban"};
const char book_att_5[] {"The loai"};
const char book_att_6[] {"Gia sach"};
const char book_att_7[] {"So quyen"};

const char* book_atts[BOOKATT_COUNT] = {
    book_att_0, book_att_1, book_att_2, book_att_3,
    book_att_4, book_att_5, book_att_6, book_att_7
};

// Ham dung de lowercase va xoa whitespace cua ISBN input, tien cho viec kiem tra va tim kiem
// char* isbn --> pointer tro den gia tri cua ISBN can kiem tra
// size_t maxLength --> so ky tu toi da cho gia tri cua thuoc tinh
void normalizeISBN(char* isbn, size_t maxLength) {
    char temp[BOOKNAME_MAXLENGTH];
    size_t j = 0;

    for (size_t i = 0; isbn[i] != '\0' && i < maxLength && j < maxLength - 1; ++i) {
        if (!isspace(isbn[i])) {
            temp[j++] = tolower(isbn[i]);
        }
    }
    temp[j] = '\0';
    strncpy(isbn, temp, maxLength);
    isbn[maxLength - 1] = '\0';
}

// Ham dung de kiem tra tham so co o dang so nguyen hay khong
// const char* str --> pointer tro den gia tri can kiem tra
// return type: bool --> true neu gia tri kiem tra co the convert sang so nguyen
bool isValidNumeric(const char* str) {
    if (str[0] == '\0') return false;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

// Ham kiem tra gia tri tham so co la chuoi empty string hay khong
// const char* str --> pointer tro den gia tri can kiem tra
// return type: bool --> true neu gia tri kiem tra co chua du lieu
bool isNonEmptyString(const char* str) {
    if (str[0] == '\0') return false;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (!isspace(str[i])) return true;
    }
    return false;
}

// Ham tim vi tri trong gan nhat trong books array
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
int findEmptySlot(const books books) {
    for (int i = 0; i < BOOKCOUNT_MAX; ++i) {
        bool isEmpty = true;
        for (size_t j = 0; j < BOOKATT_COUNT; ++j) {
            if (books[i][j][0] != '\0') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) {
            return i;
        }
    }
    return -1;
}

// Ham thuc thi, dung de khoi tao 3D C-array de chua thong tin cac cuon sach
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void bookshelvesConstructor(books books) {
    const char bookshelves_prompt[] {"Hoan tat khoi tao ke sach!"};
    
    for (size_t i = 0; i < BOOKCOUNT_MAX; ++i) {
        for (size_t j = 0; j < BOOKATT_COUNT; ++j) {
            books[i][j][0] = '\0';
        }
    }
    
    // Dummy data
    // strncpy(books[0][0], "0", BOOKNAME_MAXLENGTH);
    // normalizeISBN(books[0][0], BOOKNAME_MAXLENGTH);
    // strncpy(books[0][1], "The Great Gatsby", BOOKNAME_MAXLENGTH);
    // strncpy(books[0][2], "F. Scott Fitzgerald", BOOKNAME_MAXLENGTH);
    // strncpy(books[0][3], "Scribner", BOOKNAME_MAXLENGTH);
    // strncpy(books[0][4], "1925", BOOKNAME_MAXLENGTH);
    // strncpy(books[0][5], "Fiction", BOOKNAME_MAXLENGTH);
    // strncpy(books[0][6], "100000", BOOKNAME_MAXLENGTH);
    // strncpy(books[0][7], "5", BOOKNAME_MAXLENGTH);

    // strncpy(books[1][0], "1", BOOKNAME_MAXLENGTH);
    // normalizeISBN(books[1][0], BOOKNAME_MAXLENGTH);
    // strncpy(books[1][1], "1984", BOOKNAME_MAXLENGTH);
    // strncpy(books[1][2], "George Orwell", BOOKNAME_MAXLENGTH);
    // strncpy(books[1][3], "Penguin", BOOKNAME_MAXLENGTH);
    // strncpy(books[1][4], "1949", BOOKNAME_MAXLENGTH);
    // strncpy(books[1][5], "Dystopian", BOOKNAME_MAXLENGTH);
    // strncpy(books[1][6], "200000", BOOKNAME_MAXLENGTH);
    // strncpy(books[1][7], "3", BOOKNAME_MAXLENGTH);

    cout << ".\n.\n" << bookshelves_prompt << endl;
}

// Ham dung de print table header, voi gia tri header la cac thuoc tinh cua book array
void printTableHeader() {
    const int colWidth = 20;
    cout << left;
    for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
    for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
        char buffer[colWidth + 1];
        strncpy(buffer, book_atts[i], colWidth);
        buffer[colWidth] = '\0';
        cout << "| " << setw(colWidth) << buffer << " ";
    }
    cout << "|" << endl;
    for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
}

// Ham dung de print tung record book trong books 3D-array
// int bookIndex --> index cua book trong books
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void printBookRow(int bookIndex, const books books) {
    const int colWidth = 20;
    cout << left;
    for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
        cout << "| ";
        if (books[bookIndex][i][0] != '\0') {
            char buffer[colWidth + 1];
            strncpy(buffer, books[bookIndex][i], colWidth);
            buffer[colWidth] = '\0';
            cout << setw(colWidth) << buffer << " ";
        } else {
            cout << setw(colWidth) << "N/A" << " ";
        }
    }
    cout << "|" << endl;
}

// Ham ket hop giua 'printTableHeader' va 'printBookRow' --> Print book record o table format voi header + record
// int bookIndex --> index cua book trong books
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void displayBook(int bookIndex, const books books) {
    char invalid_index_prompt[] {"Invalid index.\n"};
    if (bookIndex < 0 || bookIndex >= BOOKCOUNT_MAX) {
        cout << invalid_index_prompt;
        return;
    }
    
    printTableHeader();
    printBookRow(bookIndex, books);
    const int colWidth = 20;
    for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
}

// Print out header + tat ca cac record co trong 3D-array books
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void displayAllBooks(const books books) {
    bool hasBooks = false;
    
    printTableHeader();
    
    for (size_t j = 0; j < BOOKCOUNT_MAX; ++j) {
        bool isValidBook = false;
        for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
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
    for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
        for (int j = 0; j < colWidth + 3; ++j) cout << "-";
    }
    cout << "+" << endl;
    
    if (!hasBooks) {
        cout << "Hien khong co sach." << endl;
    }
}

// Ham dung de them book vao books 3D-array
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void addBook(books books) {
    int index = findEmptySlot(books);
    if (index == -1) {
        cout << "Thu vien da day, khong the them sach!" << endl;
        return;
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char isbnInput[BOOKNAME_MAXLENGTH] = {0};
    bool validISBN = false;
    while (!validISBN) {
        cout << "Nhap " << book_atts[0] << ": ";
        cin.getline(isbnInput, BOOKNAME_MAXLENGTH);
        normalizeISBN(isbnInput, BOOKNAME_MAXLENGTH);

        if (isbnInput[0] == '\0') {
            cout << "ISBN khong hop le, vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        int existingIndex = findBookIndexByISBN(books, isbnInput);
        if (existingIndex != -1) {
            cout << "Sach voi ISBN '" << isbnInput << "' da ton tai trong thu vien!" << endl;
            cout << "Thong tin sach hien co:" << endl;
            displayBook(existingIndex, books);
            cout << "Vui long nhap ISBN khac." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        validISBN = true;
        strncpy(books[index][0], isbnInput, BOOKNAME_MAXLENGTH);
        books[index][0][BOOKNAME_MAXLENGTH - 1] = '\0';
    }

    char inputBuffer[BOOKNAME_MAXLENGTH] = {0};
    bool validInput = false;
    while (!validInput) {
        cout << "Nhap " << book_atts[1] << ": ";
        cin.getline(inputBuffer, BOOKNAME_MAXLENGTH);
        if (isNonEmptyString(inputBuffer)) {
            validInput = true;
            strncpy(books[index][1], inputBuffer, BOOKNAME_MAXLENGTH);
            books[index][1][BOOKNAME_MAXLENGTH - 1] = '\0';
        } else {
            cout << "Ten sach khong hop le, vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        cout << "Nhap " << book_atts[2] << ": ";
        cin.getline(inputBuffer, BOOKNAME_MAXLENGTH);
        if (isNonEmptyString(inputBuffer)) {
            validInput = true;
            strncpy(books[index][2], inputBuffer, BOOKNAME_MAXLENGTH);
            books[index][2][BOOKNAME_MAXLENGTH - 1] = '\0';
        } else {
            cout << "Tac gia khong hop le, vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        cout << "Nhap " << book_atts[3] << ": ";
        cin.getline(inputBuffer, BOOKNAME_MAXLENGTH);
        if (isNonEmptyString(inputBuffer)) {
            validInput = true;
            strncpy(books[index][3], inputBuffer, BOOKNAME_MAXLENGTH);
            books[index][3][BOOKNAME_MAXLENGTH - 1] = '\0';
        } else {
            cout << "Nha xuat ban khong hop le, vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        cout << "Nhap " << book_atts[4] << ": ";
        cin.getline(inputBuffer, BOOKNAME_MAXLENGTH);
        if (isValidNumeric(inputBuffer)) {
            validInput = true;
            strncpy(books[index][4], inputBuffer, BOOKNAME_MAXLENGTH);
            books[index][4][BOOKNAME_MAXLENGTH - 1] = '\0';
        } else {
            cout << "Nam xuat ban phai la so nguyen hop le, vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        cout << "Nhap " << book_atts[5] << ": ";
        cin.getline(inputBuffer, BOOKNAME_MAXLENGTH);
        if (isNonEmptyString(inputBuffer)) {
            validInput = true;
            strncpy(books[index][5], inputBuffer, BOOKNAME_MAXLENGTH);
            books[index][5][BOOKNAME_MAXLENGTH - 1] = '\0';
        } else {
            cout << "The loai khong hop le, vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        cout << "Nhap " << book_atts[6] << ": ";
        cin.getline(inputBuffer, BOOKNAME_MAXLENGTH);
        if (isValidNumeric(inputBuffer)) {
            validInput = true;
            strncpy(books[index][6], inputBuffer, BOOKNAME_MAXLENGTH);
            books[index][6][BOOKNAME_MAXLENGTH - 1] = '\0';
        } else {
            cout << "Gia sach phai la so nguyen hop le, vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    validInput = false;
    while (!validInput) {
        cout << "Nhap " << book_atts[7] << ": ";
        cin.getline(inputBuffer, BOOKNAME_MAXLENGTH);
        if (isValidNumeric(inputBuffer)) {
            validInput = true;
            strncpy(books[index][7], inputBuffer, BOOKNAME_MAXLENGTH);
            books[index][7][BOOKNAME_MAXLENGTH - 1] = '\0';
        } else {
            cout << "So quyen phai la so nguyen hop le, vui long nhap lai." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "Da them sach!" << endl;
    displayBook(index, books);
}

// Ham dung de tim index cua book theo ISBN
// Return type: index cua book trong books 3D-array
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// const char* isbn --> pointer tro den gia tri cua ISBN can tim
int findBookIndexByISBN(const books books, const char* isbn) {
    size_t isbnAttrIndex = 0;
    for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
        if (strcmp(book_atts[i], "ISBN") == 0) {
            isbnAttrIndex = i;
            break;
        }
    }

    char normalizedBookISBN[BOOKNAME_MAXLENGTH];
    for (int i = 0; i < BOOKCOUNT_MAX; ++i) {
        if (books[i][isbnAttrIndex][0] != '\0') {
            strncpy(normalizedBookISBN, books[i][isbnAttrIndex], BOOKNAME_MAXLENGTH);
            normalizedBookISBN[BOOKNAME_MAXLENGTH - 1] = '\0';
            normalizeISBN(normalizedBookISBN, BOOKNAME_MAXLENGTH);
            if (strcmp(normalizedBookISBN, isbn) == 0) {
                return i;
            }
        }
    }

    return -1;
}

// Ham dung de tim index cua book theo ISBN
// Return type: index cua book trong books 3D-array
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// const char* tittle --> pointer tro den gia tri cua 'Ten sach' can tim
int findBookIndexByTittle(const books books, const char* tittle) {
    size_t titleAttrIndex = 0;
    for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
        if (strcmp(book_atts[i], "Ten sach") == 0) {
            titleAttrIndex = i;
            break;
        }
    }

    for (int i = 0; i < BOOKCOUNT_MAX; ++i) {
        if (strcmp(books[i][titleAttrIndex], tittle) == 0) {
            return i;
        }
    }

    return -1;
}

// Ham dung de tim index cua thuoc tinh book[thuoc tinh], phuc vu cho chon thuoc tinh de edit
// int n --> input cua user
// return type: int --> index cua thuoc tinh trong book[thuoc tinh]
int selectBookAttribute(int n) {
    if (n < 1 || n > BOOKATT_COUNT) {
        cout << "Thuoc tinh khong hop le" << endl;
        return -1;
    }

    return n - 1;
}

// Ham dung de tim book trong books 3D-array
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// Return type: int --> index cua book can tim trong books 3D-array
int findBook(const books books) {
    cout << "Tim sach theo:" << endl;
    cout << "1. ISBN" << endl;
    cout << "2. Ten sach" << endl;
    cout << "Nhap lua chon (1 hoac 2): ";
    
    int choice;
    while (!(cin >> choice)) {
        cout << "Vui long nhap so (1 hoac 2): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int bookIndex = -1;
    char searchValue[BOOKNAME_MAXLENGTH];
    
    if (choice == 1) {
        cout << "Nhap ISBN: ";
        cin.getline(searchValue, BOOKNAME_MAXLENGTH);
        normalizeISBN(searchValue, BOOKNAME_MAXLENGTH);
        bookIndex = findBookIndexByISBN(books, searchValue);
    } else if (choice == 2) {
        cout << "Nhap 'Ten sach': ";
        cin.getline(searchValue, BOOKNAME_MAXLENGTH);
        bookIndex = findBookIndexByTittle(books, searchValue);
    } else {
        cout << "Lua chon khong hop le." << endl;
        return -1;
    }

    if (bookIndex == -1) {
        cout << "Khong tim thay sach." << endl;
        return -1;
    }

    return bookIndex;
}

// Ham dung de thay doi thuoc tinh cua mot sach
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void editBook(books books) {
    int bookIndex = findBook(books);
    
    if (bookIndex == -1) {
        return;
    }

    cout << "Thong tin sach hien tai:" << endl;
    displayBook(bookIndex, books);

    cout << "Chon thuoc tinh can cap nhat:" << endl;
    for (size_t i = 0; i < BOOKATT_COUNT; ++i) {
        cout << i + 1 << ". " << book_atts[i] << endl;
    }
    cout << "Nhap so thu tu cua thuoc tinh (1-" << BOOKATT_COUNT << "): ";
    
    int attrChoice;
    while (!(cin >> attrChoice)) {
        cout << "Vui long nhap so hop le: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int attrIndex = selectBookAttribute(attrChoice);
    if (attrIndex == -1) {
        return;
    }

    char inputBuffer[BOOKNAME_MAXLENGTH] = {0};
    bool validInput = false;
    while (!validInput) {
        cout << "Nhap gia tri moi cho " << book_atts[attrIndex] << ": ";
        cin.getline(inputBuffer, BOOKNAME_MAXLENGTH);

        if (attrIndex == 0) {
            normalizeISBN(inputBuffer, BOOKNAME_MAXLENGTH);
            if (inputBuffer[0] == '\0') {
                cout << "ISBN khong hop le, vui long nhap lai." << endl;
            } else {
                int existingIndex = findBookIndexByISBN(books, inputBuffer);
                if (existingIndex != -1 && existingIndex != bookIndex) {
                    cout << "Sach voi ISBN '" << inputBuffer << "' da ton tai trong thu vien!" << endl;
                    cout << "Thong tin sach hien co:" << endl;
                    displayBook(existingIndex, books);
                    cout << "Vui long nhap ISBN khac." << endl;
                } else {
                    validInput = true;
                    strncpy(books[bookIndex][attrIndex], inputBuffer, BOOKNAME_MAXLENGTH);
                    books[bookIndex][attrIndex][BOOKNAME_MAXLENGTH - 1] = '\0';
                }
            }
        } else if (attrIndex == 1 || attrIndex == 2 || attrIndex == 3 || attrIndex == 5) {
            if (isNonEmptyString(inputBuffer)) {
                validInput = true;
                strncpy(books[bookIndex][attrIndex], inputBuffer, BOOKNAME_MAXLENGTH);
                books[bookIndex][attrIndex][BOOKNAME_MAXLENGTH - 1] = '\0';
            } else {
                cout << book_atts[attrIndex] << " khong hop le, vui long nhap lai." << endl;
            }
        } else if (attrIndex == 4 || attrIndex == 6 || attrIndex == 7) {
            if (isValidNumeric(inputBuffer)) {
                validInput = true;
                strncpy(books[bookIndex][attrIndex], inputBuffer, BOOKNAME_MAXLENGTH);
                books[bookIndex][attrIndex][BOOKNAME_MAXLENGTH - 1] = '\0';
            } else {
                cout << book_atts[attrIndex] << " phai la so nguyen hop le, vui long nhap lai." << endl;
            }
        }
        if (!validInput) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "Da cap nhat sach!" << endl;
    displayBook(bookIndex, books);
}

// Ham dung de xoa book trong books 3D-array
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void deleteBook(books books) {
    int bookIndex = findBook(books);
    
    if (bookIndex == -1) {
        return;
    }

    cout << "Thong tin sach se bi xoa:" << endl;
    displayBook(bookIndex, books);
    cout << "Xac nhan xoa sach (1: Có, 0: Không): ";
    
    int confirm;
    while (!(cin >> confirm)) {
        cout << "Vui long nhap so hop le (1 hoac 0): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (confirm != 1) {
        cout << "Huy xoa sach." << endl;
        return;
    }

    for (size_t j = 0; j < BOOKATT_COUNT; ++j) {
        books[bookIndex][j][0] = '\0';
    }

    cout << "Da xoa sach thanh cong!" << endl;
}

// Ham dung de tim sach va hien thi ra console theo 'Ten sach'
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void searchBookByTitle(const books books) {
    char invalid_prompt[] {"Khong tim thay sach \n"};
    char option_prompt[] {"Vui long nhap ten sach: \n"};
    char searchValue[BOOKNAME_MAXLENGTH];
    
    cout << option_prompt;
    cin.getline(searchValue, BOOKNAME_MAXLENGTH);
    int bookIndex = findBookIndexByTittle(books, searchValue);

    if (bookIndex >= 0 && bookIndex < BOOKCOUNT_MAX) {
        displayBook(bookIndex, books);
        return;
    } else {
        cout << invalid_prompt;
    }
}

// Ham dung de tim sach va hien thi ra console theo 'ISBN'
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void searchBookByISBN(const books books) {
    char invalid_prompt[] {"Khong tim thay sach \n"};
    char option_prompt[] {"Vui long nhap ISBN: \n"};
    char searchValue[BOOKNAME_MAXLENGTH];
    
    cout << option_prompt;
    cin.getline(searchValue, BOOKNAME_MAXLENGTH);
    normalizeISBN(searchValue, BOOKNAME_MAXLENGTH);
    int bookIndex = findBookIndexByISBN(books, searchValue);

    if (bookIndex >= 0 && bookIndex < BOOKCOUNT_MAX) {
        displayBook(bookIndex, books);
        return;
    } else {
        cout << invalid_prompt;
    }
}

// Ham phu tro dung de kiem tra xem mot char[] co xuat hien trong book[thuoc tinh][gia tri thuoc tinh]
// return type: bool --> true neu tim thay
// const char* value --> pointer tro den gia tri tim kiem
// const char values[][BOOKNAME_MAXLENGTH] --> vi tri cua gia tri thuoc tinh can kiem tra
bool isValueInArray(const char* value, const char values[][BOOKNAME_MAXLENGTH], size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(values[i], value) == 0) {
            return true;
        }
    }
    return false;
}

// ham dung de dem so luong sach theo mot tham so thuoc tinh
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
// size_t attr_index --> index cua thuoc tinh can group trong book array
// const char* value --> gia tri can kiem tra
// Return type: size_t --> count number: gia tri so quyen
size_t getTotalBooks(const books books, size_t attr_index, const char* value) {
    size_t total = 0;
    for (size_t i = 0; i < BOOKCOUNT_MAX; ++i) {
        if (books[i][0][0] != '\0' && strcmp(books[i][attr_index], value) == 0) {
            total += atoi(books[i][7]);
        }
    }
    return total;
}

// Ham dung de dem so luong cuon sach trong thu vien (books 3D-array)
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void countTotalBooks(const books books) {
    // Table formatting
    const int label_width = 30;
    const int count_width = 15;

    // Count total copies (from books)
    size_t total = 0;
    for (size_t i = 0; i < BOOKCOUNT_MAX; ++i) {
        if (books[i][0][0] != '\0') {
            total += atoi(books[i][7]);
        }
    }

    // Print table
    cout << left;
    cout << "+" << string(label_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;
    cout << "| " << setw(label_width) << "Thong ke" << " | " << setw(count_width) << "So luong" << " |" << endl;
    cout << "+" << string(label_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;

    if (total == 0) {
        cout << "Hien khong co sach." << endl;
    } else {
        cout << "| " << setw(label_width) << "Tong so sach cua thu vien" << " | " << setw(count_width) << total << " |" << endl;
    }

    cout << "+" << string(label_width + 2, '-') << "+" << string(count_width + 2, '-') << "+" << endl;
}

// Ham dung de dem so luong cuon sach trong thu vien (books 3D-array), group theo 'The loai' va hien thi theo dang bang
// books books --> 3D C-array [Sach][Thuoc tinh cua sach][Gia tri thuoc tinh]
void countBooksByGenre(const books books) {
    // Array to store unique genres
    char unique_genres[BOOKCOUNT_MAX][BOOKNAME_MAXLENGTH];
    size_t genre_counts[BOOKCOUNT_MAX];
    size_t unique_count = 0;

    // Collect unique genres (The loai, index 5)
    for (size_t i = 0; i < BOOKCOUNT_MAX; ++i) {
        if (books[i][0][0] != '\0' && books[i][5][0] != '\0') {
            if (!isValueInArray(books[i][5], unique_genres, unique_count)) {
                strncpy(unique_genres[unique_count], books[i][5], BOOKNAME_MAXLENGTH);
                unique_genres[unique_count][BOOKNAME_MAXLENGTH - 1] = '\0';
                genre_counts[unique_count] = getTotalBooks(books, 5, unique_genres[unique_count]);
                unique_count++;
            }
        }
    }

    // Table formatting
    const int genre_width = 30;
    const int copies_width = 15;

    cout << left;
    cout << "+" << string(genre_width + 2, '-') << "+" << string(copies_width + 2, '-') << "+" << endl;
    cout << "| " << setw(genre_width) << "The loai" << " | " << setw(copies_width) << "Tong so quyen" << " |" << endl;
    cout << "+" << string(genre_width + 2, '-') << "+" << string(copies_width + 2, '-') << "+" << endl;

    if (unique_count == 0) {
        cout << "Hien khong co sach." << endl;
    } else {
        for (size_t i = 0; i < unique_count; ++i) {
            cout << "| " << setw(genre_width) << unique_genres[i] << " | ";
            cout << setw(copies_width) << genre_counts[i] << " |" << endl;
        }
        cout << "+" << string(genre_width + 2, '-') << "+" << string(copies_width + 2, '-') << "+" << endl;
    }
}