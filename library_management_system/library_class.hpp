#include"member_class.hpp";
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
