#include"book_class.hpp";
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
