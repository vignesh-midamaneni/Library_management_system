/*
    Library Management System (C++ Implementation)

    Description:
    This program implements a basic Library Management System with the following features:
    - Add and manage books (with title, author, ISBN, available and total copies)
    - Register library members with optional borrowing limits
    - Borrow and return books with proper error handling
    - View member and book details
    - Update book information such as ISBN and copies count

    Core Components:
    - 'book' class: Represents a book with relevant metadata and borrowing logic
    - 'member' class: Represents a library member who can borrow and return books
    - 'library' class: Manages collections of books and members, and orchestrates operations
    - 'main' function: Parses user commands and performs respective library operations

    Supported Commands:
    - Book [book info / ExistingBook / None]
    - Member [id name [limit] / NoBorrowLimit id name]
    - Borrow [memberId isbn]
    - Return [memberId isbn]
    - PrintBook [isbn]
    - PrintMember [memberId]
    - PrintLibrary
    - UpdateCopiesCount [isbn newCount]
    - Done

    Developed for academic and educational purposes.

Author: Vignesh Midamaneni
---------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// -------------------- Book Class --------------------
class book
{
public:
    // Constructors
    book(string t, string au, string isbn_c, int copies_ava, int tot_cop);
    book();                      // default constructor
    book(book b, string n_isbn); // copy constructor with new ISBN

    // Getter functions
    string get_isbn();
    int get_copAvaliable();
    int get_totCop();

    // Utility functions
    void set_copies(int count); // update total and available copies
    bool borrowbook();          // borrow a book if available
    bool returnbook();          // return a book if within limits
    void print_details();       // print book details

    string title, author;

private:
    string isbn;
    int copies_avaliable;
    int total_copies;
};

// -------------------- Member Class --------------------
class member
{
public:
    // Constructors
    member(string memberId, string name, int borrowLimit);
    member(string memberId, string name); // default limit is 3

    // Getter
    string get_mem_id();

    // Utility functions
    bool borrow_book(string isbn); // add book to member's list
    bool return_book(string isbn); // return book
    void print_details();          // print borrowed book info

    string mem_name;

private:
    string mem_id;
    map<string, int> borrowed_books; // map of borrowed books and counts
    int borrowedcount;
    int borrow_limit;
};

// -------------------- Library Class --------------------
class library
{
public:
    // Book and Member operations
    bool add_book(book &b);
    bool register_member(member &m);
    member *getMember(string memberId);
    book *getBook(string isbn);

    bool borrow_book(string m_id, string isbn_c);
    bool return_book(string m_id, string isbn_c);

    // Printing and updates
    void print_details();
    bool update_isbn(string o_isbn, string n_isbn);
    void printBook(string isbn);
    void printMember(string m_id);
    bool updateCopies(string isbn, int n_count);

private:
    vector<book> books;
    vector<member> members;
};

// -------------------- Book Implementation --------------------
book::book(string t, string au, string isbn_c, int copies_ava, int tot_cop)
    : title(t), author(au), isbn(isbn_c), copies_avaliable(copies_ava), total_copies(tot_cop) {}

book::book() : title("UnknownTitle"), author("UnknownAuthor"), isbn("ISBN"), copies_avaliable(0), total_copies(5) {}

book::book(book b, string n_isbn)
    : title(b.title), author(b.author), isbn(n_isbn), copies_avaliable(b.copies_avaliable), total_copies(b.total_copies) {}

string book::get_isbn() { return isbn; }

int book::get_copAvaliable() { return copies_avaliable; }

int book::get_totCop() { return total_copies; }

void book::set_copies(int count)
{
    // Ensure new count doesn't go negative
    if (count + total_copies < 0 || count + copies_avaliable < 0)
    {
        cout << "Invalid request! Count becomes negative\n";
        return;
    }
    copies_avaliable += count;
    total_copies += count;
}

bool book::borrowbook()
{
    if (copies_avaliable > 0)
    {
        copies_avaliable--;
        return true;
    }
    else
    {
        cout << "Invalid request! Copy of book not available\n";
        return false;
    }
}

bool book::returnbook()
{
    if (copies_avaliable < total_copies)
    {
        copies_avaliable++;
        return true;
    }
    else
    {
        cout << "Invalid request! Copy of book exceeds total copies\n";
        return false;
    }
}

void book::print_details()
{
    cout << title << " " << author << endl;
}

// -------------------- Member Implementation --------------------
member::member(string memberId, string name, int borrowLimit)
    : mem_id(memberId), mem_name(name), borrow_limit(borrowLimit), borrowedcount(0) {}

member::member(string memberId, string name)
    : mem_id(memberId), mem_name(name), borrow_limit(3), borrowedcount(0) {}

string member::get_mem_id() { return mem_id; }

bool member::borrow_book(string isbn)
{
    // Count total currently borrowed books
    borrowedcount = 0;
    for (auto it : borrowed_books)
        borrowedcount += it.second;

    if (borrowedcount < borrow_limit)
    {
        borrowed_books[isbn]++;
        borrowedcount++;
        return true;
    }
    else
    {
        cout << "Invalid request! Borrow limit exceeded\n";
        return false;
    }
}

bool member::return_book(string isbn)
{
    if (borrowed_books[isbn] > 0)
    {
        borrowed_books[isbn]--;
        borrowedcount--;
        return true;
    }
    else
    {
        cout << "Invalid request! Book not borrowed\n";
        return false;
    }
}

void member::print_details()
{
    for (auto it : borrowed_books)
    {
        if (it.second != 0)
            cout << mem_id << " " << mem_name << " " << it.first << " " << it.second << endl;
    }
}

// -------------------- Library Implementation --------------------
bool library::add_book(book &b)
{
    for (auto &a : books)
    {
        if (a.get_isbn() == b.get_isbn())
        {
            cout << "Invalid request! Book with same isbn already exists\n";
            return false;
        }
    }
    books.push_back(b);
    return true;
}

bool library::register_member(member &m)
{
    for (auto &a : members)
    {
        if (a.get_mem_id() == m.get_mem_id())
        {
            cout << "Invalid request! Member with same id already exists\n";
            return false;
        }
    }
    members.push_back(m);
    return true;
}

member *library::getMember(string memberId)
{
    for (auto &m : members)
    {
        if (m.get_mem_id() == memberId)
            return &m;
    }
    return nullptr;
}

book *library::getBook(string isbn)
{
    for (auto &b : books)
    {
        if (b.get_isbn() == isbn)
            return &b;
    }
    return nullptr;
}

bool library::borrow_book(string m_id, string isbn_c)
{
    member *member = getMember(m_id);
    book *book = getBook(isbn_c);
    if (!member || !book)
        return false;

    if (book->borrowbook())
    {
        if (member->borrow_book(book->get_isbn()))
        {
            return true;
        }
        else
        {
            book->returnbook(); // rollback book availability if member fails
            return false;
        }
    }
    return false;
}

bool library::return_book(string m_id, string isbn_c)
{
    member *member = getMember(m_id);
    book *book = getBook(isbn_c);
    if (!member || !book)
        return false;

    if (book->returnbook())
    {
        if (member->return_book(book->get_isbn()))
        {
            return true;
        }
        else
        {
            book->borrowbook(); // rollback book if member fails to return
            return false;
        }
    }
    return false;
}

void library::print_details()
{
    for (auto &b : books)
        cout << b.title << " " << b.author << " " << b.get_copAvaliable() << endl;
    for (auto &m : members)
        cout << m.get_mem_id() << " " << m.mem_name << endl;
}

bool library::update_isbn(string o_isbn, string n_isbn)
{
    for (auto &b : books)
    {
        if (b.get_isbn() == o_isbn)
        {
            book p(b, n_isbn); // clone with new ISBN
            books.push_back(p);
            return true;
        }
    }
    return false;
}

void library::printBook(string isbn)
{
    for (auto &b : books)
    {
        if (b.get_isbn() == isbn)
        {
            b.print_details();
            return;
        }
    }
}

void library::printMember(string m_id)
{
    for (auto &m : members)
    {
        if (m.get_mem_id() == m_id)
        {
            m.print_details();
            return;
        }
    }
}

bool library::updateCopies(string isbn, int n_count)
{
    for (auto &b : books)
    {
        if (b.get_isbn() == isbn)
        {
            b.set_copies(n_count);
            return true;
        }
    }
    return false;
}

// -------------------- Main Function --------------------
int main()
{
    library lib;
    string command;
    while (getline(cin, command))
    {
        if (command == "Done")
            break;

        // Add Book
        if (command == "Book")
        {
            string l;
            getline(cin, l);
            istringstream ss(l);
            string f;
            ss >> f;

            if (f == "None")
            {
                // Default book
                book b;
                lib.add_book(b);
            }
            else if (f == "ExistingBook")
            {
                string oldisbn, newisbn;
                ss >> oldisbn >> newisbn;
                lib.update_isbn(oldisbn, newisbn);
            }
            else
            {
                // Custom book
                string title = f, author, isbn;
                int copiesAvailable, totalCopies;
                ss >> author >> isbn >> copiesAvailable >> totalCopies;
                book bl(title, author, isbn, copiesAvailable, totalCopies);
                lib.add_book(bl);
            }
        }

        // Register Member
        else if (command == "Member")
        {
            string line;
            getline(cin, line);
            istringstream ss(line);
            string first, id, name;
            int limit;
            ss >> first;

            if (first == "NoBorrowLimit")
            {
                ss >> id >> name;
                limit = 3; // default limit
            }
            else
            {
                id = first;
                ss >> name >> limit;
            }
            member ml(id, name, limit);
            lib.register_member(ml);
        }

        // Borrow a book
        else if (command == "Borrow")
        {
            string memberId, isbn;
            cin >> memberId >> isbn;
            lib.borrow_book(memberId, isbn);
        }

        // Return a book
        else if (command == "Return")
        {
            string memberId, isbn;
            cin >> memberId >> isbn;
            lib.return_book(memberId, isbn);
        }

        // Print book details
        else if (command == "PrintBook")
        {
            string isbn;
            cin >> isbn;
            lib.printBook(isbn);
        }

        // Print member borrowed books
        else if (command == "PrintMember")
        {
            string memberId;
            cin >> memberId;
            lib.printMember(memberId);
        }

        // Print library summary
        else if (command == "PrintLibrary")
        {
            lib.print_details();
        }

        // Update book copies
        else if (command == "UpdateCopiesCount")
        {
            string isbn;
            int newCount;
            cin >> isbn >> newCount;
            lib.updateCopies(isbn, newCount);
        }
    }
    return 0;
}