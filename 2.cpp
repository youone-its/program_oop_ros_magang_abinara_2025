#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Book {
private:
    int isbn;
    string title;
    string author;
    bool available;

public:
    Book(int isbn, const string& title, const string& author) 
        : isbn(isbn), title(title), author(author), available(true) {}
    
    int getISBN() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isAvailable() const { return available; }
    
    void setAvailable(bool avail) { available = avail; }
    
    void display() const {
        cout << "ISBN: " << isbn << ", Title: " << title 
                  << ", Author: " << author << ", Available: " 
                  << (available ? "Yes" : "No") << endl;
    }
};

class Library {
private:
    vector<Book> books;
    
public:
    void addBook(int isbn, const string& title, const string& author) {
        books.emplace_back(isbn, title, author);
        cout << "Book added successfully!\n";
    }
    
    void displayAllBooks() const {
        if (books.empty()) {
            cout << "No books in library.\n";
            return;
        }
        for (const auto& book : books) {
            book.display();
        }
    }
    
    Book* findBook(int isbn) {
        auto it = find_if(books.begin(), books.end(),
            [isbn](const Book& b) { return b.getISBN() == isbn; });
        return (it != books.end()) ? &(*it) : nullptr;
    }
    
    bool updateBook(int isbn, const string& title, const string& author) {
        Book* book = findBook(isbn);
        if (book) {
            cout << "Book updated successfully!\n";
            return true;
        }
        cout << "Book not found!\n";
        return false;
    }
    
    bool removeBook(int isbn) {
        auto it = find_if(books.begin(), books.end(),
            [isbn](const Book& b) { return b.getISBN() == isbn; });
        if (it != books.end()) {
            books.erase(it);
            cout << "Book removed successfully!\n";
            return true;
        }
        cout << "Book not found!\n";
        return false;
    }
};

int main() {
    Library library;
    library.addBook(12345, "C++ Programming", "John Doe");
    library.addBook(67890, "Data Structures", "Jane Smith");
    library.displayAllBooks();
    library.removeBook(12345);
    library.displayAllBooks();
    return 0;
}