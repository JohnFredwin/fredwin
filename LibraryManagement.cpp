#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

int id = 1;
const char fileName[] = "Books.csv";
string title;
string author;
string genre;

class Library
{
public:
    void addBook()
    {
        system("cls");
        fstream add("Books.csv", ios::app);
        cin.ignore();
        cout << "Enter the book Title: ";
        getline(cin, title);
        cout << "Enter the author name: ";
        getline(cin, author);
        cout << "Enter the genre of the book: ";
        getline(cin, genre);
        add << id << ",";
        add << title << ",";
        add << author << ",";
        add << genre << "," << endl;
        id++;
        add.close();
    }

    void displayBooks()
    {
        system("cls");
        fstream display("Books.csv", ios::in);
        string line;
        auto decoration = std::string(120, '=');
        cout << decoration;
        cout << endl;
        cout << left << setw(30) << "Id" << left << setw(30) << "Title" << left << setw(30) << "Author Name" << left << setw(30) << "Genre" << endl;
        cout << decoration;
        cout << endl;
        cin.ignore();
        while (getline(display, line))
        {
            string word;
            for (int i = 0; i < line.length(); i++)
            {
                if (line[i] == ',')
                {
                    int last = word.length() - 1;
                    cout << left << setw(30) << word.substr(0, word.length());
                    word = "";
                    continue;
                }
                word += line[i];
            }
            cout << endl;
        }
        display.close();
    }

    void updateBook()
    {
        system("cls");
    update:
        int toChange;
        string line;
        string idExists;
        string updateLine;
        bool found;
        ifstream update("Books.csv");
        cout << "Enter a book id to update: ";
        cin >> toChange;
        while (true)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                cout << "Please enter a valid id to update! " << endl;
                goto update;
            }
            else if (!cin.fail())
                break;
        }
        while (getline(update, line))
        {
            fstream updated("Temp.csv", ios::app);
            idExists = line[0];
            if (to_string(toChange) == idExists)
            {
                string temp;
                updated << toChange << ",";
                cout << "Enter the details to be updated: " << endl;
                cout << "Title:";
                cin.ignore();
                getline(cin, temp);
                updated << temp << ",";
                cout << "Author name: ";
                getline(cin, temp);
                updated << temp << ",";
                cout << "Genre: ";
                getline(cin, temp);
                updated << temp << "," << endl;
                found = true;
                continue;
            }
            updated << line << endl;
            updated.close();
        }
        if (found)
        {
            cout << "Updated";
        }
        else
        {
            cout << "No such id exists";
        }
        update.close();
        remove(fileName);
        rename("Temp.csv", fileName);
    }

    void deleteBook()
    {
        system("cls");
    del:
        ifstream del(fileName);
        int rem;
        string line;
        string eraseLine;
        bool found;
        cout << "Enter an id to remove a book: ";
        cin >> rem;
        while (true)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                cout << "Please enter a valid id to delete! " << endl;
                goto del;
            }
            else if (!cin.fail())
                break;
        }
        while (getline(del, line))
        {
            string deleteId;
            deleteId += line[0];
            if ((to_string(rem) == deleteId))
            {
                eraseLine = line;
                found = true;
                continue;
            }
            string line2;
            fstream temp("text.csv", ios::app);
            temp << "";
            temp << line << endl;
            temp.close();
        }
        if (found)
            cout << "Book successfully deleted";
        else
            cout << "Id not found";
        del.close();
        remove(fileName);
        rename("text.csv", fileName);
    }
};

void menu()
{
    Library obj;
    char again;
    do
    {
        system("cls");
    menu:

        int choice;
        cout << "Menu:" << endl;
        cout << "\t1. Add a book" << endl;
        cout << "\t2. Display the books" << endl;
        cout << "\t3. Update a book" << endl;
        cout << "\t4. Delete a book" << endl;
        cout << "\t5. Exit" << endl;
        cout << "\n\tChoose from the menu: " << endl
             << "\t";
        cin >> choice;

        while (true)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                cout << "Please enter a number from the given list: " << endl;
                goto menu;
            }
            else if (!cin.fail())
                break;
        }
        switch (choice)
        {
        case 1:
            obj.addBook();
            break;
        case 2:
            obj.displayBooks();
            break;
        case 3:
            obj.updateBook();
            break;
        case 4:
            obj.deleteBook();
            break;
        case 5:
            exit(0);
        default:
            system("cls");
            cout << "Please enter a number from the given list: " << endl;
            goto menu;
        }

    unexpected:
        cout << endl
             << "Do you wish to continue(y/n)? ";
        cin >> again;

        if (!(again == 'y' | again == 'n'))
            goto unexpected;

    } while (again == 'y');
}
void findId()
{
    fstream idNumber("Books.csv", ios::in);
    string line;
    char z = id;
    int count = 0;
    while (getline(idNumber, line))
    {
        count++;
        id = count + 1;
    }
}
int main()
{
    findId();
    menu();
    return 1;
}