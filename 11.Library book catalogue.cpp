#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// Maximum number of books the library can hold
const int MAX_BOOKS = 50;

// Book structure to store book information
struct Book {
    string title;
    string author;
    string isbn;
    int year;
    bool isAvailable;
};

// Library class to manage the book collection
class Library {
private:
    Book books[MAX_BOOKS];
    int bookCount;
    
public:
    // Constructor - starts COMPLETELY EMPTY
    Library() {
        bookCount = 0;
        cout << "\n" << string(60, '=') << endl;
        cout << "         🏛️  LIBRARY CATALOGUE SYSTEM 🏛️" << endl;
        cout << "         📚 Fixed Capacity: " << MAX_BOOKS << " books 📚" << endl;
        cout << string(60, '=') << endl;
        cout << "⚠️  Library starts EMPTY. Add books to begin!" << endl;
    }
    
    // Input validation helper
    void clearInputBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    // Check if library is full
    bool isFull() {
        return bookCount >= MAX_BOOKS;
    }
    
    // Check if library is empty
    bool isEmpty() {
        return bookCount == 0;
    }
    
    // Add a new book - COMPLETE USER INPUT
    void addBook() {
        if (isFull()) {
            cout << "\n❌ Library is FULL! Cannot add more books." << endl;
            cout << "📊 Current: " << bookCount << "/" << MAX_BOOKS << endl;
            return;
        }
        
        cout << "\n📚 === ADD NEW BOOK ===" << endl;
        cout << string(35, '-') << endl;
        
        Book newBook;
        
        // Title input
        cout << "📖 Book Title: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newBook.title);
        while (newBook.title.empty()) {
            cout << "⚠️  Title cannot be empty. Enter Book Title: ";
            getline(cin, newBook.title);
        }
        
        // Author input
        cout << "✍️  Author Name: ";
        getline(cin, newBook.author);
        while (newBook.author.empty()) {
            cout << "⚠️  Author cannot be empty. Enter Author Name: ";
            getline(cin, newBook.author);
        }
        
        // ISBN input
        cout << "🆔 ISBN (10/13 digits): ";
        getline(cin, newBook.isbn);
        while (newBook.isbn.empty()) {
            cout << "⚠️  ISBN cannot be empty. Enter ISBN: ";
            getline(cin, newBook.isbn);
        }
        
        // Year input
        cout << "📅 Publication Year (e.g., 2023): ";
        while (!(cin >> newBook.year) || newBook.year < 0 || newBook.year > 2025) {
            cout << "⚠️  Invalid year! Enter valid year (0-2025): ";
            clearInputBuffer();
            cin >> newBook.year;
        }
        clearInputBuffer();
        
        // Availability input
        char availChoice;
        cout << "📊 Is Available? (y/n): ";
        cin >> availChoice;
        clearInputBuffer();
        newBook.isAvailable = (availChoice == 'y' || availChoice == 'Y' || availChoice == '1');
        
        // Add to array
        books[bookCount] = newBook;
        bookCount++;
        
        cout << "\n✅ '" << newBook.title << "' ADDED SUCCESSFULLY!" << endl;
        cout << "📊 Total Books: " << bookCount << "/" << MAX_BOOKS << endl;
    }
    
    // Remove book by index - USER SELECTS
    void removeBook() {
        if (isEmpty()) {
            cout << "\n❌ Library is EMPTY! Add books first." << endl;
            return;
        }
        
        displayBooks();
        
        int index;
        cout << "\n🗑️  Enter book ID to REMOVE (1-" << bookCount << "): ";
        while (!(cin >> index) || index < 1 || index > bookCount) {
            cout << "⚠️  Invalid ID! Enter number between 1-" << bookCount << ": ";
            clearInputBuffer();
            cin >> index;
        }
        clearInputBuffer();
        
        index--; // Convert to 0-based
        
        cout << "\n🗑️  CONFIRM DELETION:" << endl;
        cout << "📖 " << books[index].title << " by " << books[index].author << endl;
        char confirm;
        cout << "Are you sure? (y/n): ";
        cin >> confirm;
        clearInputBuffer();
        
        if (confirm == 'y' || confirm == 'Y') {
            // Shift array
            for (int i = index; i < bookCount - 1; i++) {
                books[i] = books[i + 1];
            }
            bookCount--;
            cout << "\n✅ Book REMOVED successfully!" << endl;
        } else {
            cout << "\n❌ Removal CANCELLED." << endl;
        }
        
        cout << "📊 Total Books: " << bookCount << "/" << MAX_BOOKS << endl;
    }
    
    // Search by title - COMPLETE USER INPUT
    void searchByTitle() {
        if (isEmpty()) {
            cout << "\n❌ Library is EMPTY! Add books first." << endl;
            return;
        }
        
        string searchTitle;
        cout << "\n🔍 === SEARCH BOOKS ===" << endl;
        cout << "Enter title keywords: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, searchTitle);
        
        if (searchTitle.empty()) {
            cout << "⚠️  Search term cannot be empty!" << endl;
            return;
        }
        
        bool found = false;
        cout << "\n📚 Search Results for '" << searchTitle << "':" << endl;
        cout << string(70, '=') << endl;
        
        for (int i = 0; i < bookCount; i++) {
            // Case-insensitive partial match
            string title = books[i].title;
            string search = searchTitle;
            for (char& c : title) c = tolower(c);
            for (char& c : search) c = tolower(c);
            
            if (title.find(search) != string::npos) {
                displayBookDetails(i + 1, books[i]);
                found = true;
            }
        }
        
        if (!found) {
            cout << "😞 No books found matching '" << searchTitle << "'" << endl;
        }
        cout << string(70, '=') << endl;
    }
    
    // Display all books
    void displayBooks() {
        if (isEmpty()) {
            cout << "\n📚 Library is EMPTY! Use option 2 to add books." << endl;
            return;
        }
        
        cout << "\n📚 LIBRARY CATALOGUE (" << bookCount << "/" << MAX_BOOKS << ")" << endl;
        cout << string(85, '=') << endl;
        cout << left << setw(4) << "ID" 
             << setw(28) << "TITLE" 
             << setw(22) << "AUTHOR" 
             << setw(14) << "ISBN" 
             << setw(7) << "YEAR" 
             << setw(12) << "STATUS" << endl;
        cout << string(85, '-') << endl;
        
        for (int i = 0; i < bookCount; i++) {
            cout << left << setw(4) << (i + 1)
                 << setw(28) << books[i].title.substr(0, 25) + (books[i].title.length() > 25 ? "..." : "")
                 << setw(22) << books[i].author.substr(0, 19) + (books[i].author.length() > 19 ? "..." : "")
                 << setw(14) << books[i].isbn.substr(0, 11) + (books[i].isbn.length() > 11 ? "..." : "")
                 << setw(7) << books[i].year
                 << setw(12) << (books[i].isAvailable ? "✅ Available" : "🔒 Issued") << endl;
        }
        cout << string(85, '=') << endl;
    }
    
    // Display detailed book info
    void displayBookDetails(int id, Book book) {
        cout << "\n📖 BOOK #" << id << endl;
        cout << string(25, '-') << endl;
        cout << "Title:  " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "ISBN:   " << book.isbn << endl;
        cout << "Year:   " << book.year << endl;
        cout << "Status: " << (book.isAvailable ? "✅ Available" : "🔒 Issued") << endl;
    }
    
    // Library status
    void showStatus() {
        cout << "\n📊 === LIBRARY STATUS ===" << endl;
        cout << string(30, '-') << endl;
        cout << "Total Books:     " << bookCount << "/" << MAX_BOOKS << endl;
        cout << "Empty Slots:     " << (MAX_BOOKS - bookCount) << endl;
        cout << "Status:          " << (isFull() ? "🚫 FULL" : "✅ SPACE AVAILABLE") << endl;
        
        if (!isEmpty()) {
            int available = 0;
            for (int i = 0; i < bookCount; i++) {
                if (books[i].isAvailable) available++;
            }
            cout << "Available Books: " << available << endl;
            cout << "Issued Books:    " << (bookCount - available) << endl;
        }
    }
    
    // Interactive menu
    void displayMenu() {
        cout << "\n" << string(60, '=') << endl;
        cout << "🏛️  LIBRARY MANAGEMENT SYSTEM" << endl;
        cout << string(60, '=') << endl;
        cout << "1️⃣  📖  View All Books" << endl;
        cout << "2️⃣  ➕  Add New Book" << endl;
        cout << "3️⃣  🗑️  Remove Book" << endl;
        cout << "4️⃣  🔍  Search by Title" << endl;
        cout << "5️⃣  📊  Library Status" << endl;
        cout << "0️⃣  ❌  Exit Program" << endl;
        cout << string(60, '=') << endl;
        cout << "📝 Enter choice (0-5): ";
    }
    
    // Main program loop
    void run() {
        int choice;
        
        cout << "\n🎯 Welcome! Library starts EMPTY.\n" << endl;
        
        while (true) {
            displayMenu();
            
            // Input validation for menu choice
            while (!(cin >> choice) || choice < 0 || choice > 5) {
                cout << "⚠️  Invalid! Enter 0-5: ";
                clearInputBuffer();
                cin >> choice;
            }
            clearInputBuffer();
            
            switch (choice) {
                case 1:
                    displayBooks();
                    break;
                case 2:
                    addBook();
                    break;
                case 3:
                    removeBook();
                    break;
                case 4:
                    searchByTitle();
                    break;
                case 5:
                    showStatus();
                    break;
                case 0:
                    cout << "\n👋 Thank you for using Library System!" << endl;
                    cout << "📚 Goodbye! 📚" << endl;
                    return;
                default:
                    cout << "\n❌ Invalid choice!" << endl;
            }
            
            // Pause for user
            cout << "\n⏸️  Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
};

// Main function
int main() {
    cout << string(80, '*') << endl;
    cout << "🚀 Starting Library Catalogue System..." << endl;
    cout << string(80, '*') << endl;
    
    Library library;
    library.run();
    
    return 0;
}
