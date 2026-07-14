// GetUserRecord.cpp
// This function looks up ONE account in users.txt by its username.
// If the account is found, it fills in the saved password hash and the
// account's lock time, and returns true. If the account is not found, it
// returns false.
//
// Each line in users.txt has 3 parts:  username  passwordHash  lockUntil
//   - lockUntil is a time value in seconds. 0 means the account is NOT locked.

#include <fstream>
#include <string>
using namespace std;

bool getUserRecord(string username, string &hashOut, long long &lockUntilOut)
{
    ifstream file("users.txt");

    string storedUsername;
    string storedHash;
    long long storedLock;

    // Read every account until we find the matching username.
    while (file >> storedUsername >> storedHash >> storedLock)
    {
        if (storedUsername == username)
        {
            hashOut = storedHash;         // give the saved hash back to the caller
            lockUntilOut = storedLock;    // give the saved lock time back too
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
