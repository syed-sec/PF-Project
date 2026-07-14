// SignUp.cpp
// This function creates a new user account and saves it in users.txt.
// A strong password is REQUIRED before the account can be created.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// These functions are defined in other folders.
// We just tell the compiler they exist so we can call them here.
bool usernameExists(string username);
bool isValidUsername(string username);
bool isStrongPassword(string password);
string hashPassword(string username, string password);
string readPassword();
void createUserWorkspace(string username);
void clearInputLine();
void waitForUser();
void printHeader(string title);

void signUp()
{
    string username;
    string password;

    printHeader("📝  SIGN UP  -  Create Your Account");

    // Keep asking for a username until it is unique, or the user cancels.
    // This keeps the user INSIDE registration instead of sending them back
    // to the Main Menu after a taken username.
    cout << "   Username rules: 3-20 characters, letters, numbers and _ only.\n";
    cout << "\n";

    while (true)
    {
        cout << "👤 Enter a username (or type 'cancel' to go back): ";
        cin >> username;
        clearInputLine(); // remove the leftover Enter key from the buffer

        // Let the user leave registration without creating an account.
        if (username == "cancel")
        {
            cout << "\nℹ️  Registration cancelled.\n";
            waitForUser();
            return;
        }

        // The username becomes a folder name, so check it is safe FIRST.
        // A name like ".." or "a/b" would build a broken or dangerous path.
        if (!isValidUsername(username))
        {
            cout << "\n❌ That username cannot be used.\n";
            cout << "   It must be 3-20 characters long and may only contain\n";
            cout << "   letters (a-z), numbers (0-9) and underscores (_).\n\n";
            continue; // ask again, stay on the Sign Up screen
        }

        // If the username is free, stop asking and continue.
        if (!usernameExists(username))
        {
            break;
        }

        // Username is taken: show a message and ask again (stay here).
        cout << "\n❌ Username already exists.\n";
        cout << "   Please choose a different username.\n\n";
    }

    bool strongEnough = false;

    // Keep asking for a password until it meets the strength rules.
    while (!strongEnough)
    {
        cout << "🔑 Enter a password: ";
        password = readPassword(); // typed characters are hidden with '*'

        strongEnough = isStrongPassword(password);

        if (!strongEnough)
        {
            cout << "\n⚠️  Password is too weak. It must have:\n";
            cout << "     - At least 8 characters\n";
            cout << "     - At least 1 uppercase letter (A-Z)\n";
            cout << "     - At least 1 lowercase letter (a-z)\n";
            cout << "     - At least 1 number (0-9)\n";
            cout << "     - At least 1 special character (e.g. ! @ # $ %)\n";
            cout << "\n👉 Please try again.\n\n";
        }
    }

    // Open the file to add the new account. ios::app adds to the end
    // without erasing the accounts that are already saved.
    ofstream file("users.txt", ios::app);

    // Make sure the file actually opened before we claim success.
    if (!file.is_open())
    {
        cout << "\n❌ Could not save the account.\n";
        cout << "   Please make sure the program is allowed to write files in this folder.\n";
        waitForUser();
        return;
    }

    // Never save the real password. Save its scrambled hash instead.
    // We save 3 parts: username, password hash, and lock time.
    // The lock time starts at 0, which means the account is NOT locked.
    string hashedPassword = hashPassword(username, password);
    file << username << " " << hashedPassword << " " << 0 << endl;

    file.close();

    cout << "\n✅ Account created successfully.\n";

    // The account was saved, so now give this user their own private folders:
    // Data/<username>/Encrypted and Data/<username>/Decrypted
    createUserWorkspace(username);

    waitForUser();
}
