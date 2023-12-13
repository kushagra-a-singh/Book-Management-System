#include "bookClass.cpp"

// Function to delete book details
void deleteBookDetails(bool buy);

// Function to buy a book
void buyBook() {
    int n_shelf, quantity;
    string book_title;

    // Lop until a valid book title is entered
    while (true) {
        cout << "Enter Book's title:: \n";
        cout << "-> ";
        cin.clear();
        cin.sync();
        getline(cin, book_title);

        // Check if the book exists in the shelf
        n_shelf = books_title_shelf[book_title];
        if (!shelfs[n_shelf].count(book_title)) {
            cout << "---------------This book does not exists!!---------------\n";
        } else {
            break;
        }
    }

    // Get the quantity of the book to buy
    cout << "Enter the quantity:: \n";
    cout << "-> ";
    cin >> quantity;

    // Buy the book
    shelfs[n_shelf][book_title].buyThisBook(quantity);
}

// Function to search for books in a shelf
void searchInshelf() {
    int n_shelf;

    // Get the shelf position to search
    cout << "Enter shelf position to search:: \n";
    cout << "-> ";
    cin >> n_shelf;

    // Look through all the books in the shelf and display their details
    for (auto& shelf_book : shelfs[n_shelf]) {
        cout << "-------------------------------------------------------------------------------------------------------------------------------------";
        shelf_book.second.getDetails();
    }
}

// Function to search for a book by title
void searchForBook() {
    string book_title;

    // Loop until a valid book title is entered
    while (true) {
        cout << "Enter Book's title to search:: \n";
        cout << "-> ";
        cin.clear();
        cin.sync();
        getline(cin, book_title);

        // Check if the book exists in the shelf
        if (!books_title_shelf[book_title]) {
            cout << "---------------This book does not exists!!---------------\n";
        } else {
            break;
        }
    }

    // Display the shelf position and details of the book
    int n_shelf = books_title_shelf[book_title];
    cout << "-> This book is in the shelf position -> " + to_string(n_shelf);
    cout << "\n---------------Book Details---------------\n";
    shelfs[n_shelf][book_title].getDetails();
}

// Function to edit book details
void editBookDetails() {
    string book_title;
    int n_shelf;

    // Loop until a valid book title is entered
    while (true) {
        cout << "Enter Book's title to edit:: \n";
        cout << "-> ";
        cin.clear();
        cin.sync();
        getline(cin, book_title);

        // Check if the book exists in the shelf
        if (!books_title_shelf[book_title]) {
            cout << "---------------This book does not exists!!---------------\n";
        } else {
            break;
        }
    }

    // Edit the details of the book
    n_shelf = books_title_shelf[book_title];;
    shelfs[n_shelf][book_title].editDetails();
}


// Deletes a book's details from the shelf and the book database.
void deleteBookDetails(bool buy) {
    // Prompt user to enter the book's title to be deleted.
    cout << "Enter the book's title to be deleted:: \n";
    cout << "-> ";
    string book_title;
    cin.clear();
    cin.sync();
    getline(cin, book_title);
    
    // Check if the book exists in the book database.
    if (books_title_shelf.find(book_title) != books_title_shelf.end()) {
        // If the book exists, delete it from the shelf and the book database.
        int shelf_position = books_title_shelf[book_title];
        shelfs[shelf_position].erase(book_title);
        books_title_shelf.erase(book_title);
        cout << "---------------The book ( " << book_title << " ) has been deleted successfully!---------------\n";

        // Remove the book's details from the book database file.
        ifstream book_file;
        book_file.open("database.txt");
        string line;
        ofstream temp_file;
        temp_file.open("temp_data.txt");
        while (getline(book_file, line)) {
            if (line.find(book_title) == string::npos) {
                temp_file << line << "\n";
            }
        }
        book_file.close();
        temp_file.close();
        remove("database.txt");
        rename("temp_data.txt", "database.txt");

    } else {
        // If the book does not exist in the book database, display an error message.
        cout << "The book ( " << book_title << " ) does not exist in the records!\n";
    }
}

// Runs the entire book inventory management system.
void runSystem() {
    int n_choice;
    do {
        // Display the available options for the user to choose from.
        cout << "----------------------------------------------------CHOOSE YOUR PREFERRED CHOICE FROM BELOW------------------------------------------\n";
        cout << "1- Enter new book\n";
        cout << "2- Buy book\n";
        cout << "3- Show available books in a Book Shelf\n";
        cout << "4- Check availability for a book in Library\n";
        cout << "5- Edit book details\n";
        cout << "6- Delete book\n";
        cout << "7- Exit\n";
        cout << "-> Enter choice:: ";

        // Get the user's choice.
        cin >> n_choice;

        // Check if the user's input is valid.
        if (!isValidInput(n_choice, 1, 7)) {
            cout << "Invalid input, please try again.\n";
        } else {
            // Execute the chosen option.
            switch (n_choice) {
                case 1: {
                    book new_book;
                    new_book.registerThisBook();
                    break;
                }
                case 2: {
                    buyBook();
                    break;
                }
                case 3: {
                    searchInshelf();
                    break;
                }
                case 4: {
                    searchForBook();
                    break;
                }
                case 5: {
                    editBookDetails();
                    break;
                }
                case 6: {
                    deleteBookDetails(false);
                    break;    
                }

                case 7: {
                    // Exit the program.
                    cout << "Exiting program...\n";
                    break;
                }
            }
        }
    } while (n_choice != 7);
}

// The main function of the program.
int main() {
    // Load books from the book database file.
    loadBooks();

    // Run the book inventory management system.
    runSystem();

    // Save books to the book database file.
    saveBooks();
}
