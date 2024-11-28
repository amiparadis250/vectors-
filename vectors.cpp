#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// Enum for Genre
enum Genre { fiction, nonfiction, periodical, biography, children };

// Function to display genre options
void display_genre_options() {
    cout << "Select Genre:\n";
    cout << "0. Fiction\n";
    cout << "1. Nonfiction\n";
    cout << "2. Periodical\n";
    cout << "3. Biography\n";
    cout << "4. Children\n";
}

// Book class
class Book {
private:
    string ISBN;
    string Title;
    string Author;
    int Copyright_date;
    bool Checked_out;
    Genre Book_genre;

public:
    // Default constructor
    Book() : Copyright_date(0), Checked_out(false), Book_genre(fiction) {}

    // Constructor
    Book(string isbn, string title, string author, int copyright_date, Genre genre)
        : ISBN(isbn), Title(title), Author(author), 
          Copyright_date(copyright_date), Checked_out(false), Book_genre(genre) {}

    // Method to input book details
    void input_book() {
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Input ISBN
        cout << "Enter ISBN: ";
        getline(cin, ISBN);

        // Input Title
        cout << "Enter Book Title: ";
        getline(cin, Title);

        // Input Author
        cout << "Enter Author Name: ";
        getline(cin, Author);

        // Input Copyright Date
        cout << "Enter Copyright Year: ";
        cin >> Copyright_date;

        // Input Genre
        display_genre_options();
        int genre_choice;
        cout << "Enter Genre (0-4): ";
        cin >> genre_choice;
        
        // Validate genre input
        if (genre_choice >= 0 && genre_choice <= 4) {
            Book_genre = static_cast<Genre>(genre_choice);
        } else {
            cout << "Invalid genre. Defaulting to Fiction." << endl;
            Book_genre = fiction;
        }

        // Reset checked out status
        Checked_out = false;
    }

    // Getters
    string get_ISBN() const { return ISBN; }
    string get_Title() const { return Title; }
    string get_Author() const { return Author; }
    int get_Copyright_date() const { return Copyright_date; }
    bool is_Checked_out() const { return Checked_out; }
    Genre get_Genre() const { return Book_genre; }

    // Book checkout and check-in functions
    void check_out() { 
        if (!Checked_out) {
            Checked_out = true;
            cout << "Book checked out successfully." << endl;
        } else {
            cout << "Book is already checked out." << endl;
        }
    }

    void check_in() { 
        if (Checked_out) {
            Checked_out = false;
            cout << "Book checked in successfully." << endl;
        } else {
            cout << "Book is not checked out." << endl;
        }
    }

    // Operator overloads
    bool operator==(const Book& other) const { 
        return ISBN == other.ISBN; 
    }

    bool operator!=(const Book& other) const { 
        return !(*this == other); 
    }

    // Overload << operator
    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Title: " << book.Title << endl
           << "Author: " << book.Author << endl
           << "ISBN: " << book.ISBN << endl
           << "Genre: ";
        
        switch (book.Book_genre) {
            case fiction: os << "Fiction"; break;
            case nonfiction: os << "Nonfiction"; break;
            case periodical: os << "Periodical"; break;
            case biography: os << "Biography"; break;
            case children: os << "Children"; break;
        }
        os << endl;
        
        return os;
    }
};

// Patron class
class Patron {
private:
    string User_name;
    string Card_number;
    int Owed_fees;

public:
    // Default constructor
    Patron() : Owed_fees(0) {}

    // Constructor
    Patron(string user_name, string card_number, int owed_fees = 0)
        : User_name(user_name), Card_number(card_number), Owed_fees(owed_fees) {}

    // Method to input patron details
    void input_patron() {
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Input User Name
        cout << "Enter Patron Name: ";
        getline(cin, User_name);

        // Input Card Number
        cout << "Enter Card Number: ";
        getline(cin, Card_number);

        // Input Owed Fees
        cout << "Enter Owed Fees (0 if none): ";
        cin >> Owed_fees;
    }

    // Getters
    string get_User_name() const { return User_name; }
    string get_Card_number() const { return Card_number; }
    int get_Owed_fees() const { return Owed_fees; }

    // Check if user owes fees
    bool owes_fees() const { return Owed_fees > 0; }

    // Setter for fees
    void set_fees(int fees) { Owed_fees = fees; }

    // Display patron details
    void display() const {
        cout << "Name: " << User_name 
             << ", Card Number: " << Card_number 
             << ", Owed Fees: $" << Owed_fees << endl;
    }
};

// Transaction class
class Transaction {
private:
    Book Transacted_book;
    Patron Transacting_patron;
    string Activity;
    string Date;

public:
    // Constructor
    Transaction(Book book, Patron patron, string activity, string date)
        : Transacted_book(book), Transacting_patron(patron), 
          Activity(activity), Date(date) {}

    // Display transaction
    void display() const {
        cout << "Transaction Details:" << endl;
        cout << "Activity: " << Activity << endl;
        cout << "Book: " << Transacted_book.get_Title() << endl;
        cout << "Patron: " << Transacting_patron.get_User_name() << endl;
        cout << "Date: " << Date << endl;
    }
};

// Library class
class Library {
private:
    vector<Book> Books;
    vector<Patron> Patrons;
    vector<Transaction> Transactions;

public:
    // Add a book to the library with user input
    void add_book() {
        Book new_book;
        new_book.input_book();
        Books.push_back(new_book);
        cout << "Book added to the library successfully!" << endl;
    }

    // Add a patron to the library with user input
    void add_patron() {
        Patron new_patron;
        new_patron.input_patron();
        Patrons.push_back(new_patron);
        cout << "Patron added to the library successfully!" << endl;
    }

    // List all books in the library
    void list_books() {
        if (Books.empty()) {
            cout << "No books in the library." << endl;
            return;
        }
        
        cout << "Library Books:" << endl;
        for (const auto& book : Books) {
            cout << book << endl;
        }
    }

    // List all patrons in the library
    void list_patrons() {
        if (Patrons.empty()) {
            cout << "No patrons in the library." << endl;
            return;
        }
        
        cout << "Library Patrons:" << endl;
        for (const auto& patron : Patrons) {
            patron.display();
        }
    }

    // Check out a book with user interaction
    void check_out_book() {
        string isbn, card_number, date;

        // Display available books
        cout << "Available Books:" << endl;
        for (const auto& book : Books) {
            if (!book.is_Checked_out()) {
                cout << "ISBN: " << book.get_ISBN() 
                     << ", Title: " << book.get_Title() << endl;
            }
        }

        // Get book ISBN
        cout << "Enter Book ISBN to check out: ";
        cin >> isbn;

        // Find the book
        auto book_it = find_if(Books.begin(), Books.end(), 
            [&isbn](const Book& b) { return b.get_ISBN() == isbn; });
        
        if (book_it == Books.end()) {
            cout << "Book not found in the library." << endl;
            return;
        }

        // Display available patrons
        cout << "Available Patrons:" << endl;
        for (const auto& patron : Patrons) {
            patron.display();
        }

        // Get patron card number
        cout << "Enter Patron Card Number: ";
        cin >> card_number;

        // Find the patron
        auto patron_it = find_if(Patrons.begin(), Patrons.end(), 
            [&card_number](const Patron& p) { return p.get_Card_number() == card_number; });
        
        if (patron_it == Patrons.end()) {
            cout << "Patron not found in the library." << endl;
            return;
        }

        // Check for fees
        if (patron_it->owes_fees()) {
            cout << "Patron owes fees. Cannot check out book." << endl;
            return;
        }

        // Check if book is already checked out
        if (book_it->is_Checked_out()) {
            cout << "Book is already checked out." << endl;
            return;
        }

        // Get transaction date
        cout << "Enter Check Out Date (YYYY-MM-DD): ";
        cin >> date;

        // Perform check out
        book_it->check_out();
        
        // Create and store transaction
        Transactions.emplace_back(*book_it, *patron_it, "Check out", date);
        
        cout << "Book checked out successfully." << endl;
    }

    // Return names of patrons who owe fees
    vector<string> patrons_who_owe_fees() const {
        vector<string> fee_owing_patrons;
        
        for (const auto& patron : Patrons) {
            if (patron.owes_fees()) {
                fee_owing_patrons.push_back(patron.get_User_name());
            }
        }
        
        return fee_owing_patrons;
    }

    // Display patrons with fees
    void display_patrons_with_fees() {
        vector<string> fee_patrons = patrons_who_owe_fees();
        
        if (fee_patrons.empty()) {
            cout << "No patrons currently owe fees." << endl;
            return;
        }
        
        cout << "Patrons owing fees:" << endl;
        for (const auto& name : fee_patrons) {
            cout << name << endl;
        }
    }
};

// Display main menu
void display_menu() {
    cout << "\n--- Library Management System ---" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Add Patron" << endl;
    cout << "3. List Books" << endl;
    cout << "4. List Patrons" << endl;
    cout << "5. Check Out Book" << endl;
    cout << "6. Display Patrons with Fees" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

// Main function
int main() {
    Library library;
    int choice;

    do {
        // Clear any previous input errors
        cin.clear();
        
        // Display menu and get choice
        display_menu();
        cin >> choice;

        // Process user choice
        switch(choice) {
            case 1:
                library.add_book();
                break;
            case 2:
                library.add_patron();
                break;
            case 3:
                library.list_books();
                break;
            case 4:
                library.list_patrons();
                break;
            case 5:
                library.check_out_book();
                break;
            case 6:
                library.display_patrons_with_fees();
                break;
            case 7:
                cout << "Exiting Library Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}