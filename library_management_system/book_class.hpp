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