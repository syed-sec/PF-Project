// HashPassword.cpp
// This function turns a password into a scrambled "hash" so that the real
// password is NEVER saved in users.txt. When the user logs in, we hash what
// they type and compare it to the saved hash.
//
// We mix the username into the password before hashing (this extra text is
// called a "salt"). Salting means two users who happen to pick the same
// password still get different hashes.
//
// IMPORTANT: This is a simple hash meant for LEARNING. It is NOT strong
// enough for real banking or production apps. For real systems you would use
// a proven, well-tested library such as bcrypt or Argon2.

#include <string>
using namespace std;

string hashPassword(string username, string password)
{
    // Combine the username (salt) and the password into one piece of text.
    string saltedText = username + "$" + password;

    // FNV-1a hashing: a simple, well-known way to turn text into a number.
    unsigned long long hashValue = 1469598103934665603ULL; // starting value
    const unsigned long long fnvPrime = 1099511628211ULL;  // mixing number

    for (size_t i = 0; i < saltedText.length(); i++)
    {
        hashValue = hashValue ^ (unsigned char)saltedText[i];
        hashValue = hashValue * fnvPrime;
    }

    // Turn the number into readable hex text (16 characters) so it can be
    // saved neatly in the file.
    string hexDigits = "0123456789abcdef";
    string result = "";

    for (int i = 0; i < 16; i++)
    {
        int lastFourBits = (int)(hashValue & 0xF);
        result = hexDigits[lastFourBits] + result; // build from right to left
        hashValue = hashValue >> 4;                 // move to the next 4 bits
    }

    return result;
}
