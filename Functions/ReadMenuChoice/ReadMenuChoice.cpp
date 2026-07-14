// ReadMenuChoice.cpp
// This function safely reads a menu number from the user.
//
// Why it exists: if the user types a letter (or any non-number) at a menu,
// a plain "cin >> choice" fails and leaves the bad text stuck in the input
// buffer. That makes the menu loop repeat forever. This function detects
// that problem, cleans up the input, and returns -1 so the menu can simply
// show "Invalid choice" and continue safely.

#include <iostream>
using namespace std;

// Defined in Functions/ClearInputLine/ClearInputLine.cpp
void clearInputLine();

int readMenuChoice()
{
    int choice;

    // Try to read a whole number from the user.
    if (!(cin >> choice))
    {
        // The user typed something that is not a number.
        cin.clear();      // remove the error flag so cin works again
        clearInputLine(); // throw away the bad text they typed
        return -1;        // -1 means "invalid choice"
    }

    // Reading worked. Remove the leftover Enter key from the buffer.
    clearInputLine();
    return choice;
}
