// WaitForUser.cpp
// This function pauses the program so the user can read messages on screen.
// It waits until the user presses the Enter key.

#include <iostream>
#include <string>
using namespace std;

void waitForUser()
{
    cout << "\n👉 Press Enter to continue...";

    // Wait for the user to press Enter by reading (and ignoring) one line.
    // The input buffer is kept clean elsewhere (every "cin >> ..." is
    // followed by clearInputLine()), so this reliably pauses until Enter.
    string dummyLine;
    getline(cin, dummyLine);
}
