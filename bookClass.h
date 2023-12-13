// Include guards to prevent multiple inclusions of the header file
#ifndef BOOK_SYSTEM_BOOKCLASS_H
#define BOOK_SYSTEM_BOOKCLASS_H

// Include necessary libraries
#include <bits/stdc++.h>
using namespace std;

// Function to print a line of "-" characters around a string to separate it from other content
void separatedLine(string paragraph){
    int screen_width = 206;
    // If the paragraph is not empty, add spaces at the beginning and end
    if(paragraph.size()){
        paragraph = ' ' + paragraph + ' ';
    }
    // Calculate the width of each part of the line
    int part_width = screen_width/2 - paragraph.size()/2;
    // Print the line of "-" characters
    cout << string(part_width,'-') << paragraph <<string(part_width,'-') << '\n';
}

// Function to check if an input is within specified boundaries
bool isValidInput(int& input, int start, int end){
    // If the input is within the boundaries, return true
    if(input >= start && input <= end){
        return true;
    }
    // If the input is not within the boundaries, output a message and return false
    cout << "---------------Enter correct choice!!---------------\n";
    return false;
}

// Class representing a book
class book {
private:
    string title; // Book title
    string authorName; // Book author's name
    int price; // Book price
    int quantity; // Book quantity
public:
    // Function to register a new book
    void registerThisBook();
    // Function to load book details from a vector
    void loadDetails(vector<string>tmp);
    // Function to save book details to a string
    string saveDetails();
    // Function to get book details
    void getDetails();
    // Function to buy a book
    void buyThisBook(int& tar_amount);
    // Function to edit book details
    void editDetails();
    // Function to delete a book
    void deleteBook(bool buy);
    // Function to delete book details
    void deleteBookDetails(bool buy);
};

// Map to store book titles and quantities in shelf
map<string,int>books_title_shelf;
// Map to store book details for each shelf
map<int,map<string,book>>shelfs;

// Function to save book details to a file
void saveBooks(){
    // Open the file for writing
    fstream file;
    file.open("database.txt");
    // Iterate through the maps of book details
    for(auto& shelf : shelfs){
        for(auto& shelf_book : shelf.second){
            // Write the shelf ID and book details to the file in a specific format
            file << shelf.first << ',' << shelf_book.second.saveDetails() << '\n';
        }
    }
    // Close the file
    file.close();
}

// Function to load book details from a file
void loadBooks(){
    // Open the file for reading
    fstream file;
    file.open("database.txt");
    string line;
    vector<string>book_file_details;
    // Read the file line by line
    while (getline(file, line)){
        book_file_details.clear();
        istringstream all(line);
        string tmp;
        // Split the line into separate strings using a delimiter
        while (getline(all,tmp,',')){
            book_file_details.push_back(tmp);
        }
        // Create a new book object and load the details into it
        book newBook;
        newBook.loadDetails(book_file_details);
    }
    // Close the file
    file.close();
}

// End of the header file
#endif //BOOK_SYSTEM_BOOKCLASS_H
