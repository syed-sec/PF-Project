// ReadPassword.cpp
// This function reads a password from the keyboard WITHOUT showing the real
// characters. It prints a '*' for each typed character, supports Backspace,
// and finishes when the user presses Enter. The real password is returned to
// the caller so it can be hashed and checked.
//
// NOTE: This uses _getch() from <conio.h>, which is available on Windows.
// (This project is already Windows-based, for example it uses system("cls").)

#include <iostream>
#include <string>
#include <conio.h> // gives us _getch() to read one key at a time
using namespace std;

string readPassword()
{
    string password = "";

    while (true)
    {
        int ch = _getch(); // read one key, but do NOT show it on the screen

        if (ch == 13) // 13 is the Enter key -> the user finished typing
        {
            break;
        }
        else if (ch == 8) // 8 is the Backspace key
        {
            // Only delete if there is at least one character to remove.
            if (!password.empty())
            {
                password.pop_back(); // remove the last real character
                cout << "\b \b";     // erase the last '*' shown on the screen
            }
        }
        else if (ch == 0 || ch == 224)
        {
            // Arrow keys and function keys send a special two-part code.
            // We read and ignore the second part so it does not become a '*'.
            _getch();
        }
        else
        {
            password += (char)ch; // keep the real character in memory
            cout << "*";          // show a star instead of the real character
        }
    }

    cout << "\n"; // move to the next line after the user presses Enter
    return password;
}
