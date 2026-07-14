// PrintHeader.cpp
// This function prints the title bar shown at the top of every screen.
//
// Why it exists: before, every screen copy-pasted its own three lines of "=".
// Now all screens call this one function, so they all look exactly the same.
// If we ever want to change the design, we only change it HERE, in one place.
//
// This is a LOOKS-ONLY helper. It does not change any program logic.

#include <iostream>
#include <string>
using namespace std;

void printHeader(string title)
{
    // A line made of the "═" box character. It looks cleaner than plain "=".
    cout << "════════════════════════════════════════════════════════════\n";
    cout << "   " << title << "\n";
    cout << "════════════════════════════════════════════════════════════\n";
    cout << "\n";
}
