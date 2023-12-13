#include "bookClass.h"

// function to register a book
void book::registerThisBook() {
    int n_shelf;
    // get shelf position for the book
    cout << "Enter shelf position to keep at:: \n";
    cout << "-> ";
    cin >> n_shelf;

    // get title for the book
    while (true){
        cout << "Enter book's Title:: \n";
        cout << "-> ";
        cin.clear();
        cin.sync();
        getline(cin, title);
        // check if title already exists in the library
        if(books_title_shelf.count(title)){
            cout << "---------------This book already exists!!---------------\n";
        }else{
            break;
        }
    }

    // get author's name for the book
    cout << "Enter author's name:: \n";
    cout << "-> ";
    cin.clear();
    cin.sync();
    getline(cin, authorName);

    // get price and quantity for the book
    cout << "Enter book's price:: \n";
    cout << "-> ";
    cin >> price;

    cout << "Enter the quantity of this book:: \n";
    cout << "-> ";
    cin >> quantity;

    // add book details to shelfs and books_title_shelf maps
    shelfs[n_shelf][title] = *this;
    books_title_shelf[title] = n_shelf;
    cout << "---------------This book has been registered successfully!!---------------\n";
}

// function to save book details as string
string book::saveDetails() {
    string tmp = title + ',' + authorName + ',' + to_string(price) + ',' + to_string(quantity);
    return tmp;
}

// function to load book details from vector of strings
void book::loadDetails(vector<string> tmp) {
    title = tmp[1];
    authorName = tmp[2];
    price = stoi(tmp[3]);
    quantity = stoi(tmp[4]);
    shelfs[stoi(tmp[0])][title] = *this;
    books_title_shelf[title] = stoi(tmp[0]);
}

// function to display book details
void book::getDetails() {
    cout << left;
    cout << setw(14) << "Book's title: " << "( " <<  title << " )\n";
    cout << setw(14)<< "Author's name: " << "( " << authorName << " )\n";
    cout << setw(14) << "Book's price: " << "( " << price << " )\n";
    cout << setw(14) << "Book's quantity: " << "( " << quantity << " )\n";
}

// function to buy a book
void book::buyThisBook(int& tar_amount) {
    if(tar_amount > quantity){
        cout << "there are only " << quantity << " books\n";
    }else{
        int final_price = tar_amount * price;
        quantity -= tar_amount;
        cout << "Successfully purchased!! You bought ( " + to_string(tar_amount) + " ) with total price: ( " + to_string(tar_amount * price) + " ), ";
        cout << "now there are ( " + to_string(quantity) + " ) books available\n";
    }
}

// Allows the user to modify the details of a book
void book::editDetails() {
    int n_choice;
    // Present a menu of choices to the user
    cout << "---------------What do you want to change in the book??\n";
    cout << "1- Book's title\n";
    cout << "2- Author's name\n";
    cout << "3- Book's price\n";
    cout << "4- Book's quantity\n";
    cout << "-> ";
    // Ensure that the user inputs a valid choice
    while (true){
        cin >> n_choice;
        if(isValidInput(n_choice,1,4)){
            break;
        }else{
            cout << "----------Enter correct choice:: ";
        }
    }
    // Modify the book attribute based on the user's choice
    if(n_choice == 1){
        string book_title;
        cout << "Enter the new Book's title:: \n";
        cout << "-> ";
        // Clear the input stream and accept the new book title
        cin.clear();
        cin.sync();
        getline(cin, book_title);
        title = book_title;
        cout << "----------The book's title has been changed successfully to: ( " + book_title + " )\n";
    }else if(n_choice == 2){
        string s_author;
        cout << "Enter the new author's name:: \n";
        cout << "-> ";
        // Clear the input stream and accept the new author's name
        cin.clear();
        cin.sync();
        getline(cin, s_author);
        authorName = s_author;
        cout << "-----Successfully, author's name has been changed to: ( " + s_author + " )\n";
    }else if(n_choice == 3){
        cout << "Enter book price:: \n";
        cout << "-> ";
        // Accept the new book price
        cin >> price;
        cout << "-----Successfully, book's price has been changed to: ( " + to_string(price) + " )\n";
    }else{
        cout << "Enter the new quantity:: \n";
        cout << "-> ";
        // Accept the new book quantity
        cin >> quantity;
        cout << "-----Successfully, book's quantity has been changed to: ( " + to_string(quantity) + " )\n";
    }
}

// This member function of the `book` class deletes a book from the `shelfs` container.
void book::deleteBook(bool buy) {
    int n_choice;

    // Prompt the user if they are sure they want to delete the book.
    cout << "---------------Are you sure you want to delete this book??\n";
    cout << "1- Yes\n";
    cout << "2- No\n";
    cout << "-> ";

    // Loop until the user enters a valid input.
    while (true){
        cin >> n_choice;

        // Check if the input is valid.
        if(isValidInput(n_choice,1,2)){
            break;
        }else{
            cout << "----------Enter correct choice:: ";
        }
    }

    // If the user selected "Yes".
    if(n_choice == 1){

        // Check if the book exists in `books_title_shelf`.
        if(books_title_shelf.count(title)){
            int shelf_position = books_title_shelf[title];

            // Erase the book from the `shelfs` container and `books_title_shelf`.
            shelfs[shelf_position].erase(title);
            books_title_shelf.erase(title);

            cout << "----------The book has been deleted successfully!\n";
        }else{
            // If the book does not exist, inform the user.
            cout << "---------------The book you are trying to delete does not exist!!---------------\n";
        }
    }else{
        // If the user selected "No", inform them that the book has not been deleted.
        cout << "----------The book has not been deleted!\n";

        // If `buy` is false (i.e. the function was not called from the `buyBook` function), prompt the user to press enter to continue.
        if(!buy){
            cout << "Please press enter to continue...\n";
            cin.ignore();
            cin.get();
        }
    }
}