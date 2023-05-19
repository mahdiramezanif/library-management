#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <stdlib.h>

using namespace std;

void change_line(int line_number, string new_string, string file_address);
void print_main_menu();
void print_manager_menu();
void print_manage_books();
void print_member_menu();
bool search(string s, string find);
string get_last_line(string s);
void plus_plus_to_end(string s);
void list_of_books();
void member_sing_up();
void add_book();
void edit_book_cout();
void edit_book();
int difference_data(string day1, string mon1, string year1, string day2, string mon2, string year2);
int calculate_user_number(string username, string pass);
void membership_renewal(int i);
void sorted(vector<string> &v, vector<int> &b);
void all_book_sorted(int l); // l is 2 for title and 4 for author
void search_in(int x);       // x is 2 for title and 4 for author
int number_of_borrowed_book(int number_of_member);
void Show_borrowed_books(int number_of_member);
float calculate_fine(string s);
void Pay_fine(int number_of_member);
void borrow_book(int number_of_member);

int main()
{
    int choose_main_menu, choose_manager_menu, choose_manage_books;
    float fine_per_day;
    string s, s0, s1, s2;

    char manager_username[8] = "manager", manager_password[8] = "12345";

main_menu:
{
    // what do you want to do in main menu ?
    print_main_menu();
    cin >> choose_main_menu;
    system("cls");
}

    switch (choose_main_menu)
    {
    case 1:
        cout << "Enter Username:\n";
        cin >> manager_username;

        cout << "Enter Password:\n";
        cin >> manager_password;

        system("cls");

        if (strcmp(manager_username, "manager") == 0 && strcmp(manager_password, "12345") == 0) // check if username and password is true or not
        {
        manager_menu:
        {
            // what do you want to do in manager menu ?
            print_manager_menu();
            cin >> choose_manager_menu;
            system("cls");
        }

            switch (choose_manager_menu)
            {
            case 1:
            manage_books:
            {
                // what do you want to do in manage books ?
                print_manage_books();
                cin >> choose_manage_books;
            }

                switch (choose_manage_books)
                {
                case 1:
                    add_book();
                    system("cls");
                    goto manager_menu;
                    break;

                case 2:
                    edit_book();
                    system("cls");
                    goto manager_menu;
                    break;

                case 3:
                    system("cls");
                    goto manager_menu;
                    break;

                case 4:
                    return 0;

                default:
                    cout << "Enter a valid number!\n";
                    goto manager_menu;
                }
                break;

            case 2:
                goto main_menu;
                break;

            case 3:
                return 0;

            default:
                cout << "Enter a valid number!\n";
                goto manager_menu;
            }
        }

        else
        {
            // If username or password is incorrect:
            cout << "Invalid Username or Password!\n";
            goto main_menu;
        }

        break;

    case 2: // member login
    {
        string username, pass;

        cout << "Please enter your username : \n";
        getline(cin, username);
        getline(cin, username);

        cout << "Please enter your password : \n";
        getline(cin, pass);

        system("cls");

        // we want to know the number of member that has this username and password.
        // if there is no member with this username and password, we use 0 as member number.
        int number_of_user = calculate_user_number(username, pass);

        if (number_of_user == 0)
        {
            cout << "Invalid username or password!\n";
            goto main_menu;
        }

        else
        {
            int choose_member_menu;
        member_menu:
        {
            print_member_menu();
            cin >> choose_member_menu;
            system("cls");
        }

            switch (choose_member_menu)
            {
            case 1:
                membership_renewal(number_of_user);
                system("cls");
                goto member_menu;
                break;

            case 2:
                all_book_sorted(2);
                goto member_menu;
                break;

            case 3:
                all_book_sorted(4);
                goto member_menu;
                break;

            case 4:
                Show_borrowed_books(number_of_user);
                goto member_menu;
                break;

            case 5:
                search_in(2);
                goto member_menu;
                break;

            case 6:
                search_in(4);
                goto member_menu;
                break;

            case 7:
                Pay_fine(number_of_user);
                goto member_menu;
                break;

            case 8:
                borrow_book(number_of_user);
                system("cls");
                goto main_menu;
                break;

            case 9:
                goto member_menu;
                break;

            case 10:
                return 0;
                break;

            default:
                cout << "Enter a valid number!\n";
                goto member_menu;
                break;
            }
        }
    }
    break;

    case 3:
        member_sing_up();
        system("cls");
        goto main_menu;
        break;

    case 4:
        return 0;

    default:
        cout << "Enter a valid number!\n";
        goto main_menu;
    }
}

// In change_line function, we want to change line number "line_number" of file "file_address" with string "new_string" :
void change_line(int line_number, string new_string, string file_address)
{
    ofstream new_file;
    new_file.open("new_file.txt");
    // new_file is a tempt file to write changed information from edit (original) file
    ifstream edit;
    edit.open(file_address);
    int i = 1;   // i count the number of line that we are reading from edit file.
    string line; // a tempt string

    while (getline(edit, line))
    {
        if (i != line_number)         // If what we read is not my choosen line
            new_file << line << endl; // transfer informations from edit file to new_file

        else                                // If what we read is my choosen line
            new_file << new_string << endl; // write new_string to new_file
        
        i++;
    }
    new_file.close();
    edit.close();
    // now new_file contains new informations

    // now we want to copy informations from new_file to edit (original) file
    ifstream new_file_2;
    new_file_2.open("new_file.txt");
    ofstream edit_2;
    edit_2.open(file_address);

    while (getline(new_file_2, line))
    {
        edit_2 << line << endl;
    }
    new_file_2.close();
    edit_2.close();
}

void print_main_menu()
{
    cout << "**Manage Library**\n";
    cout << "1. Manager\n";
    cout << "2. Member Login\n";
    cout << "3. Member Signup\n";
    cout << "4. Exit\n";
}

void print_manager_menu()
{
    cout << "**Manager Menu**\n";
    cout << "1. Manage Books\n";
    cout << "2. Back\n";
    cout << "3. Exit\n";
}

void print_member_menu()
{
    cout << "**Member Menu**\n";
    cout << "1. Membership renewal\n";
    cout << "2. Show all books (sorted by title)\n";
    cout << "3. Show all books (sorted by author)\n";
    cout << "4. Show borrowed books\n";
    cout << "5. Search in title\n";
    cout << "6. Search in author\n";
    cout << "7. Pay fine\n";
    cout << "8. Borrow available book\n";
    cout << "9. Back\n";
    cout << "10. Exit\n";
}

void print_manage_books()
{
    cout << "**Manage Books**\n";
    cout << "1. Add new book\n";
    cout << "2. View and manage a book\n";
    cout << "3. Back\n";
    cout << "4. Exit\n";
}

bool search(string s, string find) // "find" is the string that we want to know if it exist in string "s" or no
{
    int l_s = s.length();       // l_s is length of "s"
    int l_find = find.length(); // l_find is length of "find"
    // first_letter_found is true if first letter of "find" string is founded in string "s"
    bool first_letter_found = false;
    int l = 0, i = 0, j = 0; // l is the number of letters of "find" string that have founded till now

    if (l_s < l_find) // It means length of find string is more than "s" string
        return false;

    while (true)
    {
        if (l != l_find) // It means "find" string has not founded yet
        {
            if (first_letter_found)
            {
                if (s[i] != find[j]) // It means next letter of tow string (after first string founded) is not same
                {
                    first_letter_found = false; // so that, "find" string is not there
                    l = 0;                      // thus, number of letters that have founded must be 0
                    j = 0;                      // and we should back to the first letter of "find" string
                }

                i++;
                j++;
                l++;
            }

            else
            {
                if (i > l_s) // it means we have checked all letters of "s" string
                    return false;

                else
                {
                    if (s[i] == find[j])
                    {
                        first_letter_found = true;
                        l++;
                        j++;
                    }
                    i++;
                }
            }
        }

        else // It means (l == l_find) and it means "find" string has founded
            return true;
    }
}

string get_last_line(string s) // It use to read last line of a file
{
    int i;
    string line;
    ifstream my_file;
    my_file.open(s);

    while (getline(my_file, line))
        i = 2; // a tempt command to complete while loop

    my_file.close();

    return line;
}

void plus_plus_to_end(string s) // This function read last line of a file, add it with 1 and write it to end of file
{
    int i;
    string line;
    line = get_last_line(s);
    i = stoi(line); // convert line to int
    i++;
    line = to_string(i);

    ofstream my_file_2;
    my_file_2.open(s, ios::app); //(ios::app) means we don't want to clean file and overwrite to it,
    // but we want to write to the end of file
    my_file_2 << endl
              << line;
    my_file_2.close();
}

void list_of_books() // this function is used to show all books
{
    ifstream edit;
    string line;
    int i = 1, j = 1; // j is the number of books
    edit.open("books.txt");

    while (getline(edit, line))
    {
        if (i % 16 == 1) // It means we are at first of a book information
        {
            cout << endl
                 << j << ".\n"; // In this line, we print number of book
            j++;
        }

        if (i % 2 == 1) // It means line is name of information (for example: title)
            cout << line << "\t\t";

        else // It means line is information (for example: chemestry)
            cout << line << endl;

        i++;
    }
    edit.close();
}

void member_sing_up()
{
    string m = "number_of_members.txt", line, s, day, month, year;
    int y;

    plus_plus_to_end(m); // It add number of members and write number of members to the
    // end of file "number_of_members.txt"
    line = get_last_line(m); // It read nwe number of members

    s = line + ".txt"; // s is address of file that will contain information of new member
    ofstream file;
    file.open(s);

    cout << "Please enter your name : ";
    getline(cin, line);
    getline(cin, line);
    file << "Name : \n";
    file << line;
    file << endl;

    cout << "Please enter your username : ";
    cin >> line;
    file << "User name : \n";
    file << line;
    file << endl;

    cout << "Please enter your password : ";
    cin >> line;
    file << "Password : \n";
    file << line;
    file << endl;

    cout << "Please enter your phone No. : ";
    cin >> line;
    file << "phone No. : \n";
    file << line;
    file << endl;

    cout << "Please enter your joining data (Day) : ";
    cin >> day;
    file << "joining data (Day) : \n";
    file << day;
    file << endl;

    cout << "Please enter your joining data (month) : ";
    cin >> month;
    file << "joining data (month) : \n";
    file << month;
    file << endl;

    cout << "Please enter your joining data (year) : ";
    cin >> year;
    file << "joining data (year) : \n";
    file << year;
    file << endl;

    file << "exp data (Day) : \n";
    file << day;
    file << endl;

    file << "exp data (month) : \n";
    file << month;
    file << endl;

    file << "exp data (year) : \n";
    y = stoi(year);
    y++;
    year = to_string(y);
    file << year;
    file << endl;

    file << "limit of borrowed book : \n";
    file << "5\n";

    file << "borrowed books count : \n";
    file << "0\n";

    file << "borrowed books list : \n";
    for (int i = 0; i < 5; i++) // we want to write a block 5 times
    {
        file << "No book\n";
        file << "day\n";
        file << "month\n";
        file << "year\n";
    }
    file << "total fine : \n";
    file << "0";
}

void add_book()
{
    string title, author, fine;

    ofstream my_file;
    // In next line, (ios::app) means we want to write to the end of file and don't want to overwrite it
    my_file.open("books.txt", ios::app);

    cout << "Please enter book's title:\n";
    getline(cin, title);
    getline(cin, title);
    my_file << "title : \n"
            << title << endl;

    cout << "Please enter book's author:\n";
    getline(cin, author);
    my_file << "author : \n"
            << author << endl;

    my_file << "ID : \n"
            << title + author << endl;

    cout << "Please enter book's fine price per day:\n";
    getline(cin, fine);
    my_file << "fine price per day : \n"
            << fine << endl;

    my_file << "is book borrowed?\n"
            << "No\n";

    my_file << "last one who borrowed this book: \n"
            << "No one\n";

    my_file << "last time borrowed this book:\n"
            << "No data\n";

    my_file << "last time returned this book:\n"
            << "No data\n";

    my_file.close();
}

void edit_book_cout()
{
    cout << "Which part do you want to edit ? \n";
    cout << "1. title \n"
         << "2. author \n";
    cout << "3. fine \n"
         << "4. is borrowed? \n"
         << "5. last one borrowed \n";
    cout << "6. last time borrowed \n"
         << "7. last time returned \n";
}

void edit_book()
{
edit_book_menu:
{
    cout << "choose a book to edit:\n";
    list_of_books();
}

    int i = 1, j = 1, k, book_edit, l = 1;

    cin >> k; // k is the number of book that we want to edit

    edit_book_cout();
    cin >> book_edit; // book_edit is part of book that we want to edit it

    // first, we are going to copy other books to a new file and
    // selected book on a struct
    ifstream edit;
    string line, s;
    ofstream new_file;
    struct
    {
        string title;
        string author;
        string id = title + author;
        string fin;
        string is_borrowed;
        string last_one_borrowed;
        string last_time_borrowed;
        string last_time_returned;
    } book;

    new_file.open("new_file.txt");
    edit.open("books.txt");

    while (getline(edit, line))
    {
        if (i < 16 * (k - 1) + 1 || i > 16 * k) // It means line is not for selected book
            new_file << line << endl;

        else
        {
            switch (l)
            {
            case 2:
                book.title = line;
                break;

            case 4:
                book.author = line;
                break;

            case 8:
                book.fin = line;
                break;

            case 10:
                book.is_borrowed = line;
                break;

            case 12:
                book.last_one_borrowed = line;
                break;

            case 14:
                book.last_time_borrowed = line;
                break;

            case 16:
                book.last_time_returned = line;
                break;
            }
            l++;
        }

        i++;
    }

    new_file.close();
    edit.close();

    // now new_file contains information of books that we dont want to edit it
    // and struct book contain old informations of edited book
    switch (book_edit)
    {
    case 1:
        cout << "Please enter new title : \n";
        getline(cin, book.title);
        getline(cin, book.title);
        break;

    case 2:
        cout << "Please enter new author : \n";
        getline(cin, book.author);
        getline(cin, book.author);
        break;

    case 3:
        cout << "Please enter new fin : \n";
        getline(cin, book.fin);
        getline(cin, book.fin);
        break;

    case 4:
        cout << "is borrowed?\n";
        getline(cin, book.is_borrowed);
        getline(cin, book.is_borrowed);
        break;

    case 5:
        cout << "Please enter last one borrowed : \n";
        getline(cin, book.last_one_borrowed);
        getline(cin, book.last_one_borrowed);
        break;

    case 6:
        cout << "Please enter last time borrowed : \n";
        getline(cin, book.last_time_borrowed);
        getline(cin, book.last_time_borrowed);
        break;

    case 7:
        cout << "Please enter last time returned : \n";
        getline(cin, book.last_time_returned);
        getline(cin, book.last_time_returned);
        break;

    default:
        cout << "Enter a valid number !";
        goto edit_book_menu;
        break;
    }

    // now we copy new file to original file
    ofstream edit_2;
    ifstream new_file_2;

    new_file_2.open("new_file.txt");
    edit_2.open("books.txt");
    while (getline(new_file_2, line))
    {
        edit_2 << line << endl;
    }
    new_file_2.close();

    edit_2 << "title : \n"
           << book.title << endl;

    edit_2 << "author : \n"
           << book.author << endl;

    edit_2 << "ID : \n"
           << book.title + book.author << endl;

    edit_2 << "fine : \n"
           << book.fin << endl;

    edit_2 << "is borrowed? : \n"
           << book.is_borrowed << endl;

    edit_2 << "last one who borrowed : \n"
           << book.last_one_borrowed << endl;

    edit_2 << "last time borrowed : \n"
           << book.last_time_borrowed << endl;

    edit_2 << "last time returned : \n"
           << book.last_time_returned << endl;

    edit_2.close();
}

// next function calculate difference data (in Day) between toe data
int difference_data(int d1, int m1, int y1, int d2, int m2, int y2)
{
    long int total_1 = 0, total_2 = 0;

    if (m1 < 8)
        total_1 += 31 * (m1 - 1);

    else
        total_1 += 30 * (m1 - 1);

    total_1 += (d1 + 365 * y1);

    if (m2 < 8)
        total_2 += 31 * (m2 - 1);

    else
        total_2 += 30 * (m2 - 1);

    total_2 += (d2 + 365 * y2);

    return total_2 - total_1;
}

int calculate_user_number(string username, string pass)
{
    string number_of_members, line, s1, s2;
    int j, k, x;

    number_of_members = get_last_line("number_of_members.txt");
    // now number of members, is number of users
    k = stoi(number_of_members);

    for (int i = 1; i <= k; i++)
    {
        j = 0;

        s1 = to_string(i);
        s2 = s1 + ".txt";
        // now s2 is address of i_th member's file
        ifstream file;
        file.open(s2);

        while (getline(file, line))
        {
            j++;

            if (j == 4)               // It means line contain users's username
                if (username != line) // (1)
                {
                    file.close();
                    break;
                }

            if (j == 6) // It means line contain users's password
            {
                if (pass != line) //(2)
                {
                    file.close();
                    break;
                }

                else // If this else runs, it means (1) and (2) were false, so
                // this is the user that we are looking for it
                {
                    file.close();
                    return i;
                }
            }
        }
    }

    return 0; // It means no user were found with this information
}

void membership_renewal(int i)
{
    string line, s1, s2, s3, s4;

    s1 = to_string(i);
    s2 = s1 + ".txt";

pay_renewal_massage:
{
    cout << "Please pay for renewal . \n";
    cout << "Is member payed ? ('y' or 'n') (enter 'e' for exit)\n";
    cin >> s3;
}

    if (s3 == "n")
        goto pay_renewal_massage;

    if (s3 == "y")
    {
        int j = 1, k;
        string line;
        ifstream file;
        file.open(s2);

        while (getline(file, line))
        {
            if (j == 20) // It means line contain old exp. data
            {
                k = stoi(line);
                k++;
                s4 = to_string(k);
                break;
                // now s4 is new exp. data
            }

            j++;
        }
        file.close();

        // now we change 20th line of file to s4:
        change_line(20, s4, s2);
    }
}

void sorted(vector<string> &v, vector<int> &b)
{
    int a, tempt;
    a = v.size();
    string s;

    for (int i = 0; i < (a - 1); i++)
        for (int j = i + 1; j < a; j++)
        {
            if (v[i].compare(v[j]) > 0)
            {
                s = v[i];
                v[i] = v[j];
                v[j] = s;

                tempt = b[i];
                b[i] = b[j];
                b[j] = tempt;
            }
        }
}

void all_book_sorted(int l) // l is 2 for title and 4 for author
{
    vector<string> v;
    vector<int> b;
    string line;
    int size_of_vector = 1;

    ifstream file;
    file.open("books.txt");
    int i = 1;
    while (getline(file, line))
    {
        if (i % 16 == l)
        {
            v.push_back(line);
            b.push_back(size_of_vector);
            size_of_vector++;
        }
        i++;
    }
    file.close();

    sorted(v, b);

    for (int j = 0; j < size_of_vector - 1; j++)
    {
        cout << j + 1 << ".\n";
        ifstream file_2;
        file_2.open("books.txt");
        int i = 1;

        while (getline(file_2, line))
        {
            if (i > ((b[j] - 1) * 16) && i <= (b[j] * 16))
            {
                if (i%2==1)
                    cout << line << "\t\t";

                else
                    cout << line << endl;
            }
            i++;
        }
        file_2.close();
    }
}

void search_in(int x) // x is 2 for title and 4 for author
{
    ifstream file;
    string line, s;
    cout << "Enter what you want to search : \n";
    getline(cin, s);
    getline(cin, s);
    int i = 1;
    vector<int> v = {};

    file.open("books.txt");
    while (getline(file, line))
    {
        if (i % 16 == x)
            if (search(line, s))
                v.push_back((i / 16) + 1);

        i++;
    }
    file.close();

    // now, v contain number of books that have searched string.

    ifstream file_2;
    int j = v.size();
    if (j == 0)
        cout << "Ther is no book!\n";

    else
    {
        for (int k = 0; k < j; k++)
        {
            i = 1;
            int n = v[k];
            cout << k + 1 << ".\n";

            file_2.open("books.txt");
            while (getline(file_2, line))
            {
                if (i > (16 * (n - 1)) && i <= (16 * n))
                {
                if (i%2==1)
                    cout << line << "\t\t";

                else
                    cout << line << endl;
                }

                i++;
            }
            file_2.close();
        }
    }
}

int number_of_borrowed_book(int number_of_member)
{
    string s1, s2, line;
    int x, i = 1;

    s1 = to_string(number_of_member);
    s2 = s1 + ".txt";

    ifstream file;
    file.open(s2);

    while (getline(file, line))
    {
        if (i == 24)
        {
            x = stoi(line);
            return x;
        }

        i++;
    }
    file.close();
}

void Show_borrowed_books(int number_of_member)
{
    string s1, s2, line;
    int x, i = 1, j = 1, k;
    k = number_of_borrowed_book(number_of_member);

    if (k == 0)
        cout << "There is no borrowed book. \n";

    else
    {
        s1 = to_string(number_of_member);
        s2 = s1 + ".txt";

        ifstream file;
        file.open(s2);

        while (getline(file, line))
        {
            x = i - 25;
            if (x > 0)
            {
                if (j <= (k + 1))
                {
                    if (x % 4 == 1)
                    {
                        if (j != (k + 1))
                            cout << j << ".\n";
                        j++;
                    }
                    if (j != (k + 1))
                        cout << line;
                }
            }
            i++;
        }
        file.close();
    }
}

float calculate_fine(string s)
{
    int i = 1, j = 0;
    float fin;
    string line;

    ifstream file;
    file.open("books.txt");
    while (getline(file, line))
    {
        if (i % 16 == 6 && line == s)
        {
            getline(file, line);
            getline(file, line);
            fin = stof(line);
            file.close();
            return fin;
        }

        i++;
    }
}

void Pay_fine(int number_of_member)
{
    string s1, s2, line;
    int x, i = 1, j = 1, to_day, to_month, to_year, day, month, year, k;
    float total_fin = 0, fin;

    cout << "Please Enter data (day) : \n";
    cin >> to_day;

    cout << "Please Enter data (month) : \n";
    cin >> to_month;

    cout << "Please Enter data (year) : \n";
    cin >> to_year;

    k = number_of_borrowed_book(number_of_member);

    if (k == 0)
        cout << "There is no borrowed book. \n";

    else
    {
        s1 = to_string(number_of_member);
        s2 = s1 + ".txt";

        ifstream file;
        file.open(s2);

        while (getline(file, line))
        {
            x = i - 25;
            if (x > 0 && j <= k)
            {
                if (x % 4 == 1)
                    fin = calculate_fine(line);

                if (x % 4 == 2)
                    day = stoi(line);

                if (x % 4 == 3)
                    month = stoi(line);

                if (x % 4 == 0)
                {
                    year = stoi(line);
                    j++;
                }

                total_fin += (fin * difference_data(day, month, year, to_day, to_month, to_year));
            }
            i++;
        }
        file.close();
        cout << "Your total fine is : " << total_fin;
    }
}

void borrow_book(int number_of_member)
{
    string s1, s2, s3, s4, line;
    vector<string> v = {};
    vector<int> a = {};
    int i = 1, m, j = 0, z = 0, f, x, l1, l2;
    bool is_borrowed = false;

    l1 = number_of_borrowed_book(number_of_member);
    s3 = get_last_line("number_of_members.txt");
    m = stoi(s3);

    for (int y = 1; y <= m; y++)
    {
        s1 = to_string(y);
        s2 = s1 + ".txt";

        ifstream file;
        file.open(s2);

        while (getline(file, line))
        {
            x = i - 25;
            if (x > 0)
                if (x % 4 == 1)
                {
                    v.push_back(line);
                    j++; // j is size of v
                }

            i++;
        }
        file.close();
    }
    // now v contain IDs of borrowed books
    ifstream file_2;
    i = 1;
    file_2.open("books.txt");
    while (getline(file_2, line))
    {
        if (i % 16 == 6)
        {
            is_borrowed = false;

            for (int k = 0; k < j; k++)
            {
                if (line == v[j])
                    is_borrowed = true;
            }

            if (is_borrowed == false)
            {
                a.push_back(((i / 16) + 1));
                z++; // z is size of a
            }
        }
        i++;
    }
    file_2.close();
    // now a contain number of books that are available
    cout << "Please enter number of book you want to borrow : \n";
    for (int h = 0; h < z; h++)
    {
        cout << h + 1 << ".\n";
        ifstream file_3;
        i = 1;
        file_3.open("books.txt");
        while (getline(file_3, line))
        {
            if (i > (16 * (a[h] - 1)) && i <= (16 * a[h]))
            {
                if (i%2==1)
                    cout << line << "\t\t";

                else
                    cout << line << endl;
            }
            i++;
        }
        file_3.close();
    }
    cin >> f;

    ifstream file_4;
    i = 1;
    file_4.open("books.txt");
    while (getline(file_4, line))
    {
        if (i == (16 * (f - 1) + 6))
        {
            string s5, s6;
            s5 = to_string(number_of_member);
            s6 = s5 + ".txt";
            l2 = 25 + 4 * l1;
            change_line(l2 + 1, line, s6);

            cout << "Enter data (day) :";
            cin >> s4;
            change_line(l2 + 2, s4, s6);

            cout << "Enter data (month) :";
            cin >> s4;
            change_line(l2 + 3, s4, s6);

            cout << "Enter data (year) :";
            cin >> s4;
            change_line(l2 + 4, s4, s6);

            break;
        }
        i++;
    }
    file_4.close();
}