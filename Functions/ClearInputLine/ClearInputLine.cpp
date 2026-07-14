// ClearInputLine.cpp
// This small helper removes any leftover characters that are still waiting
// on the current input line, up to and including the Enter key.
//
// Why we need it: when we read a value with "cin >> something", the Enter
// key the user pressed stays behind in the input buffer. If we do not remove
// it, the next input step can misbehave (for example, a "Press Enter to
// continue" prompt might be skipped). Call this right AFTER every
// "cin >> ..." read to keep the input buffer clean.

#include <iostream>
#include <limits>
using namespace std;

void clearInputLine()
{
    // Discard everything up to and including the next newline character.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
