#include "fkstHashString.h"
#include "fkstHashFile.h"
#include "fkstHashConsole.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;

void fkst_hash_string_procedure();
void fkst_hash_file_procedure();
void fkst_hash_console_procedure();
void menu_choice(int& choice);
void clear_buffer_cin();
bool get_user_input(int& outVal);
bool get_user_input(string& outVal);

int main()
{
    while (true)
    {
        int choice{ 0 };
        menu_choice(choice);

        switch (choice)
        {
        case 1: fkst_hash_string_procedure(); break;
        case 2: fkst_hash_file_procedure(); break;
        case 3: fkst_hash_console_procedure(); break;
        case 4:
        default: break;
        }

        system("pause");
    }
}

void fkst_hash_string_procedure()
{
    // 23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7
    const string testStr1{ "abc" };
    cout << "sha224('" << testStr1 << "'):" << FkstHashString::sha224(testStr1) << std::endl;

    // d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f
    const string testStr2{ "" };
    cout << "sha224('" << testStr2 << "'):" << FkstHashString::sha224(testStr2) << std::endl;

    // 75388B16512776CC5DBA5DA1FD890150B0C6455CB4F58B1952522525
    const string testStr3{ "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq" };
    cout << "sha224('" << testStr3 << "'):" << FkstHashString::sha224(testStr3) << std::endl;
}

void fkst_hash_file_procedure()
{
    string filePath{};

    cout << "Enter file path, (test: \"test_abc.txt\"): ";
    cin >> filePath;

    try
    {
        cout << "sha224('" << filePath << "'):" << FkstHashFile::sha224(filePath) << std::endl;
    }
    catch (const std::exception & e)
    {
        std::cerr << "Failed hashing file: " << e.what() << '\n';
    }
}

void fkst_hash_console_procedure()
{
    cout << "Enter string for hashing: ";

    string str;
    if (!get_user_input(str))
    {
        cout << "Failed retrieving string from console!\n";
        return;
    }

    cout << "sha224('" << str << "'):" << FkstHashConsole::sha224(str) << std::endl;
}

void menu_choice(int& choice)
{
    system("cls");
    cout << "Choose an option:\n"
        "1. FkstHashString\n"
        "2. FkstHashFile\n"
        "3. FkstHashConsole\n"
        "4. Exit\n"
        "Enter choice: ";

    if (!get_user_input(choice))
    {
        cout << "Invalid choice!\n\n";
    }
    else if (choice < 1 || choice > 4)
    {
        cout << "Non-existent option!\n\n";
    }
}

void clear_buffer_cin()
{
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool get_user_input(int& outVal)
{
    cin >> outVal;
    if (cin.fail())
    {
        clear_buffer_cin();
        return false;
    }

    return true;
}

bool get_user_input(string& outVal)
{
    cin >> outVal;
    if (cin.fail())
    {
        clear_buffer_cin();
        return false;
    }

    return true;
}