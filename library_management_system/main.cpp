#include"library_class.hpp";
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