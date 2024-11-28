#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Enum for Genre
enum Genre { fiction, nonfiction, periodical, biography, children };

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
    // Constructor
    Book(string isbn, string title, string author, int copyright_date, Genre genre)
        : ISBN(isbn), Title(title), Author(author), Copyright_date(copyright_date),
          Checked_out(false), Book_genre(genre) {}

    // Getters
    string get_ISBN() const { return ISBN; }
    string get_Title() const { return Title; }
    string get_Author() const { return Author; }
    int get_Copyright_date() const { return Copyright_date; }
    bool is_Checked_out() const { return Checked_out; }
    Genre get_Genre() const { return Book_genre; }

    // Book checkout and check-in functions
    void check_out() { Checked_out = true; }
    void check_in() { Checked_out = false; }

    // Operator overloads
    bool operator==(const Book& other) const { return ISBN == other.ISBN; }
    bool operator!=(const Book& other) const { return !(*this == other); }

    friend ostream& operator<<(ostream& os, const Book& book) {
        os << "Title: " << book.Title << "\nAuthor: " << book.Author
           << "\nISBN: " << book.ISBN << "\nGenre: "
           << (book.Book_genre == fiction ? "Fiction" :
               book.Book_genre == nonfiction ? "Nonfiction" :
               book.Book_genre == periodical ? "Periodical" :
               book.Book_genre == biography ? "Biography" : "Children")
           << endl;
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
    // Constructor
    Patron(string user_name, string card_number, int owed_fees = 0)
        : User_name(user_name), Card_number(card_number), Owed_fees(owed_fees) {}

    // Getters
    string get_User_name() const { return User_name; }
    string get_Card_number() const { return Card_number; }
    int get_Owed_fees() const { return Owed_fees; }

    // Function to check if the user owes fees
    bool owes_fees() const { return Owed_fees > 0; }

    // Setter for fees
    void set_fees(int fees) { Owed_fees = fees; }
};

// Transaction class
class Transaction {
private:
    Book Transacted_book;
    Patron Transacting_patron;
    string Activity; // "Check out" or "Check in"
    string Date;

public:
    // Constructor
    Transaction(Book book, Patron patron, string activity, string date)
        : Transacted_book(book), Transacting_patron(patron), Activity(activity), Date(date) {}

    // Display transaction
    void display_transaction() const {
        cout << "Transaction: " << Activity
             << "\nBook: " << Transacted_book.get_Title()
             << "\nPatron: " << Transacting_patron.get_User_name()
             << "\nDate: " << Date << endl;
    }
};

// Library class
class Library {
private:
    vector<Book> Books;
    vector<Patron> Patrons;
    vector<Transaction> Transactions;

public:
    // Add a book to the library
    void add_book(const Book& book) {
        Books.push_back(book);
    }

    // Add a patron to the library
    void add_patron(const Patron& patron) {
        Patrons.push_back(patron);
    }

    // Check out a book
    void check_out_book(const string& isbn, const string& card_number, const string& date) {
        // Find the book
        auto book_it = find_if(Books.begin(), Books.end(), [&isbn](const Book& b) {
            return b.get_ISBN() == isbn;
        });
        if (book_it == Books.end()) {
            cout << "Error: Book not found.\n";
            return;
        }

        // Find the patron
        auto patron_it = find_if(Patrons.begin(), Patrons.end(), [&card_number](const Patron& p) {
            return p.get_Card_number() == card_number;
        });
        if (patron_it == Patrons.end()) {
            cout << "Error: Patron not found.\n";
            return;
        }

        // Check if patron owes fees
        if (patron_it->owes_fees()) {
            cout << "Error: Patron owes fees.\n";
            return;
        }

        // Check if the book is already checked out
        if (book_it->is_Checked_out()) {
            cout << "Error: Book is already checked out.\n";
            return;
        }

        // Check out the book
        book_it->check_out();
        Transactions.emplace_back(*book_it, *patron_it, "Check out", date);
        cout << "Book checked out successfully.\n";
    }

    // Get patrons who owe fees
    vector<string> patrons_who_owe_fees() const {
        vector<string> names;
        for (const auto& patron : Patrons) {
            if (patron.owes_fees()) {
                names.push_back(patron.get_User_name());
            }
        }
        return names;
    }
};

// Main function
int main() {
    Library library;

    // Create books
    Book book1("1234", "The Great Gatsby", "F. Scott Fitzgerald", 1925, fiction);
    Book book2("5678", "A Brief History of Time", "Stephen Hawking", 1988, nonfiction);

    // Add books to library
    library.add_book(book1);
    library.add_book(book2);

    // Create patrons
    Patron patron1("Silas HAKUZWIMANA", "1111");
    Patron patron2("Fabrice NDAYISABA", "2222", 10); // Owes fees

    // Add patrons to library
    library.add_patron(patron1);
    library.add_patron(patron2);

    // Attempt to check out a book
    library.check_out_book("1234", "1111", "2024-11-20");

    // List patrons who owe fees
    vector<string> patrons_with_fees = library.patrons_who_owe_fees();
    cout << "\nPatrons who owe fees:\n";
    for (const string& name : patrons_with_fees) {
        cout << name << endl;
    }

    return 0;
}