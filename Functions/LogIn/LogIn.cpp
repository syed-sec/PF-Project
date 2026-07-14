// LogIn.cpp
// This function logs a user in. It now includes three new features:
//   1. Hidden password input (shown on screen as '*').
//   2. Up to 5 password attempts, WITHOUT leaving the Login screen.
//   3. A 30-minute account lock after 5 wrong attempts. The lock time is
//      saved in users.txt, so it still works even if the program restarts.

#include <iostream>
#include <string>
#include <ctime> // gives us time() to read the current time in seconds
using namespace std;

// These functions are defined in other folders.
string hashPassword(string username, string password);
string readPassword();
void clearInputLine();
void printHeader(string title);
bool getUserRecord(string username, string &hashOut, long long &lockUntilOut);
void setUserLock(string username, long long lockUntil);

bool logIn(string &loggedInUser)
{
    string username;
    string storedHash;
    long long lockUntil = 0;

    printHeader("🔐  LOG IN  -  Access Your Workspace");

    cout << "👤 Enter your username: ";
    cin >> username;
    clearInputLine(); // remove the leftover Enter key from the buffer

    // Look up the account. If the username is not found, show a general error.
    // (We keep the message general so we do not reveal which part was wrong.)
    if (!getUserRecord(username, storedHash, lockUntil))
    {
        cout << "\n❌ Incorrect username or password.\n";
        return false;
    }

    // Read the current time (in seconds).
    long long now = (long long)time(nullptr);

    // If the account is still locked, do not allow login at all,
    // even if the correct password is entered.
    if (lockUntil > now)
    {
        long long minutesLeft = (lockUntil - now + 59) / 60; // round up to whole minutes
        cout << "\n🔒 Your account is temporarily locked.\n";
        cout << "   Please try again after about " << minutesLeft << " minute(s).\n";
        return false;
    }

    // Allow up to 5 password attempts before locking the account.
    int maxAttempts = 5;
    int attempts = 0;

    while (attempts < maxAttempts)
    {
        cout << "🔑 Enter your password: ";
        string password = readPassword(); // hidden input, shown as '*'

        // Hash the typed password and compare it with the saved hash.
        string enteredHash = hashPassword(username, password);

        if (enteredHash == storedHash)
        {
            loggedInUser = username;
            return true; // correct password -> login succeeds
        }

        // Wrong password: count this attempt and show how many are left.
        attempts++;
        int remaining = maxAttempts - attempts;

        if (remaining > 0)
        {
            cout << "\n❌ Incorrect password.\n";
            cout << "   Remaining attempts: " << remaining << "/" << maxAttempts << "\n\n";
        }
    }

    // Too many wrong attempts: lock the account for 30 minutes and save it,
    // so the lock still works even if the program is restarted.
    long long lockTime = now + (30 * 60); // 30 minutes = 30 * 60 seconds
    setUserLock(username, lockTime);

    cout << "\n🔒 Your account has been temporarily locked.\n";
    cout << "   Please try again after 30 minutes.\n";
    return false;
}
