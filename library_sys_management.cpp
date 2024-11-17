#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm> // For std::find

using namespace std;

// Book class
class Book {
private:
    int bookID;
    string title, author;
    bool isAvailable;

public:
    // Constructor
    Book(int id, string t, string a) : bookID(id), title(t), author(a), isAvailable(true) {}

    // Getters
    int getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool getAvailability() const { return isAvailable; }

    // Methods to update availability
    void borrowBook() { isAvailable = false; }
    void returnBook() { isAvailable = true; }

    // Display book details
    void display() const {
        cout << "Book ID: " << bookID
             << ", Title: " << title
             << ", Author: " << author
             << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// Base class for User
class User {
protected:
    int userID;
    string name;
    vector<int> borrowedBooks;

public:
    User(int id, string n) : userID(id), name(n) {}

    virtual void borrowBook(int bookID) = 0; // Pure virtual function
    virtual void returnBook(int bookID) = 0;

    // Getters
    string getName() const { return name; }
    int getUserID() const { return userID; }
    vector<int> getBorrowedBooks() const { return borrowedBooks; }

    // Display borrowed books
    void displayBorrowedBooks() const {
        cout << name << "'s Borrowed Books: ";
        for (int id : borrowedBooks)
            cout << id << " ";
        cout << endl;
    }
};

// Derived class for Student
class Student : public User {
private:
    const int borrowLimit = 3;

public:
    Student(int id, string n) : User(id, n) {}

    void borrowBook(int bookID) override {
        if (borrowedBooks.size() >= borrowLimit) {
            cout << "Borrow limit reached for " << name << ". Cannot borrow more books.\n";
        } else {
            borrowedBooks.push_back(bookID);
            cout << name << " borrowed book with ID " << bookID << endl;
        }
    }

    void returnBook(int bookID) override {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookID);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            cout << name << " returned book with ID " << bookID << endl;
        } else {
            cout << "Book ID " << bookID << " not found in " << name << "'s borrowed list.\n";
        }
    }
};

// Derived class for Faculty
class Faculty : public User {
private:
    const int borrowLimit = 5;

public:
    Faculty(int id, string n) : User(id, n) {}

    void borrowBook(int bookID) override {
        if (borrowedBooks.size() >= borrowLimit) {
            cout << "Borrow limit reached for " << name << ". Cannot borrow more books.\n";
        } else {
            borrowedBooks.push_back(bookID);
            cout << name << " borrowed book with ID " << bookID << endl;
        }
    }

    void returnBook(int bookID) override {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookID);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            cout << name << " returned book with ID " << bookID << endl;
        } else {
            cout << "Book ID " << bookID << " not found in " << name << "'s borrowed list.\n";
        }
    }
};

// Library system
class Library {
private:
    vector<Book> books;
    map<int, User*> users;

public:
    // Add a new book
    void addBook() {
        int id;
        string title, author;
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));
        cout << "Book added successfully!\n";
    }

    // Display all books
    void displayBooks() const {
        cout << "\nAvailable Books:\n";
        for (const auto& book : books) {
            book.display();
        }
    }

    // Find book by ID
    Book* findBook(int bookID) {
        for (auto& book : books) {
            if (book.getBookID() == bookID)
                return &book;
        }
        return nullptr;
    }

    // Add a user
    void addUser() {
        int id, userType;
        string name;

        cout << "Enter User ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter User Name: ";
        getline(cin, name);
        cout << "Select User Type (1-Student, 2-Faculty): ";
        cin >> userType;

        if (userType == 1) {
            users[id] = new Student(id, name);
            cout << "Student added successfully!\n";
        } else if (userType == 2) {
            users[id] = new Faculty(id, name);
            cout << "Faculty added successfully!\n";
        } else {
            cout << "Invalid user type!\n";
        }
    }

    // Borrow a book
    void borrowBook() {
        int userID, bookID;
        cout << "Enter User ID: ";
        cin >> userID;
        cout << "Enter Book ID: ";
        cin >> bookID;

        if (users.find(userID) == users.end()) {
            cout << "User ID not found.\n";
            return;
        }

        Book* book = findBook(bookID);
        if (!book || !book->getAvailability()) {
            cout << "Book not available for borrowing.\n";
            return;
        }

        users[userID]->borrowBook(bookID);
        book->borrowBook();
    }

    // Return a book
    void returnBook() {
        int userID, bookID;
        cout << "Enter User ID: ";
        cin >> userID;
        cout << "Enter Book ID: ";
        cin >> bookID;

        if (users.find(userID) == users.end()) {
            cout << "User ID not found.\n";
            return;
        }

        Book* book = findBook(bookID);
        if (!book) {
            cout << "Invalid book ID.\n";
            return;
        }

        users[userID]->returnBook(bookID);
        book->returnBook();
    }
};

// Main function
int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add User\n";
        cout << "3. Display Books\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.addUser();
                break;
            case 3:
                library.displayBooks();
                break;
            case 4:
                library.borrowBook();
                break;
            case 5:
                library.returnBook();
                break;
            case 6:
                cout << "Exiting... Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
