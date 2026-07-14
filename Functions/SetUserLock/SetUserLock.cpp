// SetUserLock.cpp
// This function saves a new "lock time" for ONE account in users.txt.
// A text file cannot be edited in the middle easily, so we do it the simple
// beginner way: read ALL accounts into memory, change the one we need, then
// write them all back to the file.
//
// lockUntil is a time value in seconds. The account stays locked until the
// computer's clock passes this time. 0 means the account is not locked.

#include <fstream>
#include <string>
#include <vector>
#include <filesystem> // rename() - used to swap the temp file into place
using namespace std;

void setUserLock(string username, long long lockUntil)
{
    // Step 1: read all accounts into memory.
    ifstream inFile("users.txt");

    vector<string> usernames;
    vector<string> hashes;
    vector<long long> locks;

    string storedUsername;
    string storedHash;
    long long storedLock;

    while (inFile >> storedUsername >> storedHash >> storedLock)
    {
        usernames.push_back(storedUsername);
        hashes.push_back(storedHash);

        // If this is the account we want to change, use the NEW lock time.
        // Otherwise keep the lock time that was already saved.
        if (storedUsername == username)
        {
            locks.push_back(lockUntil);
        }
        else
        {
            locks.push_back(storedLock);
        }
    }

    inFile.close();

    // Step 2: write all accounts to a TEMPORARY file first.
    //
    // Why not write straight into users.txt? Because opening users.txt for
    // writing empties it instantly. If the program crashed at that moment,
    // EVERY account would be gone forever. By building a complete temp file
    // first, users.txt stays safe and untouched until the new data is ready.
    ofstream outFile("users_temp.txt");

    // If the temp file cannot be created, stop now and leave users.txt alone.
    if (!outFile.is_open())
    {
        return;
    }

    for (size_t i = 0; i < usernames.size(); i++)
    {
        outFile << usernames[i] << " " << hashes[i] << " " << locks[i] << endl;
    }

    outFile.close();

    // Step 3: the temp file is complete, so swap it into place.
    // rename() replaces users.txt in one quick step.
    filesystem::rename("users_temp.txt", "users.txt");
}
