# Library Management System

## Overview

This is a C++ console application for managing a library's book lending and patron tracking system. The application provides a comprehensive set of features for librarians to manage books, patrons, and transactions.

## Features

### Book Management
- Add new books to the library
- Track book information including:
  * ISBN
  * Title
  * Author
  * Copyright date
  * Genre
- Check out and check in books
- List all books in the library

### Patron Management
- Add new library patrons
- Track patron information including:
  * User name
  * Card number
  * Outstanding fees
- View patrons with outstanding fees

### Transaction Tracking
- Record book check-out and check-in activities
- Track which patron checked out which book
- Store transaction dates

## System Requirements

- C++ Compiler (C++11 or later)
- Standard C++ libraries
- Console/Terminal to run the application

## Compilation Instructions

### Using g++
```bash
g++ -std=c++11 library_management.cpp -o library_system
./library_system
```

## Main Menu Options

1. **Add Book**: 
   - Input new book details
   - Specify ISBN, title, author, copyright year, and genre

2. **Add Patron**: 
   - Register new library patrons
   - Enter user name and card number
   - Optional: Add initial outstanding fees

3. **List Books**: 
   - Display all books in the library
   - Shows book details including title, author, ISBN, and genre

4. **List Patrons**: 
   - Show all registered library patrons
   - Displays name, card number, and outstanding fees

5. **Check Out Book**: 
   - Lend a book to a patron
   - Validates:
     * Book availability
     * Patron's fee status
   - Creates a transaction record

6. **Display Patrons with Fees**: 
   - List patrons who have outstanding fees
   - Helps track accounts requiring payment

7. **Exit**: 
   - Close the library management application

## Validation Rules

- Cannot check out books to patrons with outstanding fees
- Each book has a unique ISBN
- Genre selection is restricted to predefined categories
- Input validation for dates and numeric fields

## Error Handling

- Prevents checking out already borrowed books
- Warns about invalid menu selections
- Handles input buffer issues
- Provides clear error messages for user guidance

## Potential Improvements

- Persistent data storage (database/file)
- More advanced fee management
- Book return functionality
- User authentication
- Search and filter capabilities

## Contributing

Contributions are welcome! Please fork the repository and submit pull requests with your enhancements.
## Author

ISHIMWE Ami Paradis
University Of Rwanda
Computer and Software Engineering
