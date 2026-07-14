// IsValidUsername.cpp
// This function checks whether a username is SAFE to use as a folder name.
//
// Why it exists: the program builds every save path from the username, like
//     "Data/" + username + "/Encrypted"
// So a dangerous username becomes a dangerous folder path. For example, a user
// called ".." would produce "Data/../Encrypted", which escapes the Data folder
// completely and creates files where they do not belong.
//
// The rule we use is simple and strict: a username may only contain letters,
// digits and underscores. That single rule blocks spaces, dots, slashes, and
// every other character that could break a path.

#include <string>
#include <cctype>
using namespace std;

bool isValidUsername(string username)
{
    // Rule 1: the length must be sensible.
    if (username.length() < 3 || username.length() > 20)
    {
        return false;
    }

    // Rule 2: only letters, digits and underscore are allowed.
    // This is what stops "..", "a/b", "my name" and similar dangerous names.
    for (size_t i = 0; i < username.length(); i++)
    {
        char c = username[i];

        bool isLetter = isalpha((unsigned char)c);
        bool isNumber = isdigit((unsigned char)c);
        bool isUnderscore = (c == '_');

        if (!isLetter && !isNumber && !isUnderscore)
        {
            return false;
        }
    }

    // Rule 3: Windows refuses to create a folder with these special names,
    // so an account using one of them could never get a workspace.
    // We compare in UPPERCASE so that "con", "Con" and "CON" are all caught.
    string upperName = "";

    for (size_t i = 0; i < username.length(); i++)
    {
        upperName += (char)toupper((unsigned char)username[i]);
    }

    string reservedNames[] = {
        "CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
        "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"};

    // Let the compiler count the list for us. If we wrote the number by hand
    // and got it wrong, the loop would read past the end of the array.
    int reservedCount = sizeof(reservedNames) / sizeof(reservedNames[0]);

    for (int i = 0; i < reservedCount; i++)
    {
        if (upperName == reservedNames[i])
        {
            return false;
        }
    }

    // The username passed every rule, so it is safe to use as a folder name.
    return true;
}
