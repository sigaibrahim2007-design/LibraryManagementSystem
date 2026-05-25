#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book() {}

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        issued = false;
    }
};

class Library {
private:
    vector<Book> books;

public:

    void loadBooks() {
        books.clear();

        ifstream file("library.txt");

        if (!file)
            return;

        Book b;

        while (file >> b.id) {
            file.ignore();

            getline(file, b.title);
            getline(file, b.author);

            file >> b.issued;
            file.ignore();

            books.push_back(b);
        }

        file.close();
    }

    void saveBooks() {
        ofstream file("library.txt");

        for (Book b : books) {
            file << b.id << endl;
            file << b.title << endl;
            file << b.author << endl;
            file << b.issued << endl;
        }

        file.close();
    }

    void addBook() {
        int id;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore();

        for (Book b : books) {
            if (b.id == id) {
                cout << "Book ID already exists!\n";
                return;
            }
        }

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));

        saveBooks();

        cout << "Book Added Successfully!\n";
    }

    void displayBooks() {

        if (books.empty()) {
            cout << "\nNo books available.\n";
            return;
        }

        cout << "\n===== Book List =====\n";

        for (Book b : books) {

            cout << "\nID: " << b.id;
            cout << "\nTitle: " << b.title;
            cout << "\nAuthor: " << b.author;

            if (b.issued)
                cout << "\nStatus: Issued";
            else
                cout << "\nStatus: Available";

            cout << "\n-------------------";
        }
    }

    void searchTitle() {

        string title;

        cin.ignore();

        cout << "\nEnter title: ";
        getline(cin, title);

        bool found = false;

        for (Book b : books) {

            if (b.title == title) {

                cout << "\nBook Found";
                cout << "\nID: " << b.id;
                cout << "\nTitle: " << b.title;
                cout << "\nAuthor: " << b.author;

                found = true;
            }
        }

        if (!found)
            cout << "Book not found!\n";
    }

    void searchAuthor() {

        string author;

        cin.ignore();

        cout << "\nEnter author: ";
        getline(cin, author);

        bool found = false;

        for (Book b : books) {

            if (b.author == author) {

                cout << "\nBook Found";
                cout << "\nID: " << b.id;
                cout << "\nTitle: " << b.title;

                found = true;
            }
        }

        if (!found)
            cout << "Author not found!\n";
    }

    void issueBook() {

        int id;

        cout << "\nEnter Book ID: ";
        cin >> id;

        for (Book &b : books) {

            if (b.id == id) {

                if (b.issued) {
                    cout << "Book already issued!\n";
                    return;
                }

                b.issued = true;

                saveBooks();

                cout << "Book issued successfully!\n";

                return;
            }
        }

        cout << "Book not found!\n";
    }

    void returnBook() {

        int id;

        cout << "\nEnter Book ID: ";
        cin >> id;

        for (Book &b : books) {

            if (b.id == id) {

                if (!b.issued) {
                    cout << "Book already available!\n";
                    return;
                }

                b.issued = false;

                saveBooks();

                cout << "Book returned successfully!\n";

                return;
            }
        }

        cout << "Book not found!\n";
    }

};

int main() {

    Library library;

    library.loadBooks();

    int choice;

    do {

        cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====";

        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search By Title";
        cout << "\n4. Search By Author";
        cout << "\n5. Issue Book";
        cout << "\n6. Return Book";
        cout << "\n7. Exit";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                library.addBook();
                break;

            case 2:
                library.displayBooks();
                break;

            case 3:
                library.searchTitle();
                break;

            case 4:
                library.searchAuthor();
                break;

            case 5:
                library.issueBook();
                break;

            case 6:
                library.returnBook();
                break;

            case 7:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid choice!";
        }

    } while(choice != 7);

    return 0;
}