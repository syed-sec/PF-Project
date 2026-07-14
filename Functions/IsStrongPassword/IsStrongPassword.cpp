// IsStrongPassword.cpp
// This function checks whether a password is "strong enough".
// Rules: at least 8 characters, and at least one uppercase letter,
// one lowercase letter, one digit, and one special character.

#include <string>
#include <cctype>
using namespace std;

bool isStrongPassword(string password)
{
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    if (password.length() < 8)
    {
        return false;
    }

    // size_t matches the type returned by password.length(), which avoids a
    // signed/unsigned comparison warning.
    for (size_t i = 0; i < password.length(); i++)
    {
        char c = password[i];

        if (isupper((unsigned char)c))
        {
            hasUpper = true;
        }
        else if (islower((unsigned char)c))
        {
            hasLower = true;
        }
        else if (isdigit((unsigned char)c))
        {
            hasDigit = true;
        }
        else if (!isspace((unsigned char)c))
        {
            // Anything that's not a letter, digit, or whitespace
            // counts as a special character (e.g. ! @ # $ %).
            hasSpecial = true;
        }
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}
