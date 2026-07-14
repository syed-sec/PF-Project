// UsernameExists.cpp
// This function checks if a username already exists in users.txt.

#include <fstream>
#include <string>
using namespace std;

bool usernameExists(string username)
{
    ifstream file("users.txt");

    string storedUsername;
    string storedPassword;
    long long storedLock; // 3rd part of each line (the lock time)

    // Read username, password hash, and lock time from the file until the end.
    while (file >> storedUsername >> storedPassword >> storedLock)
    {
        // If the username matches, the username already exists.
        if (storedUsername == username)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
