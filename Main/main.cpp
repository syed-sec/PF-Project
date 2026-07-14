// main.cpp
// This is the entry point of the program.
//
// Notice: we are NOT using any .h (header) files here.
// Instead, we simply write a "prototype" (a one-line preview) of every
// function before main(), so the compiler knows they exist. The actual
// code for each function lives in its own folder inside "Functions/".
// This is a simple and beginner-friendly way to split code into files.

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------
// Function prototypes
// (Each of these is fully defined in Functions/<FunctionName>/)
// ---------------------------------------------------------------
void clearScreen();
void waitForUser();
void clearInputLine();
void printHeader(string title);
void printLine();
int readMenuChoice();
bool usernameExists(string username);
bool isValidUsername(string username);
bool isStrongPassword(string password);
int getSecretKey();
string hashPassword(string username, string password);
string readPassword();
bool getUserRecord(string username, string &hashOut, long long &lockUntilOut);
void setUserLock(string username, long long lockUntil);
void ensureDataFolder();
void createUserWorkspace(string username);
void signUp();
bool logIn(string &loggedInUser);
string makeEncryptedFileName(string inputFileName);
string makeDecryptedFileName(string inputFileName);
void encryptTextFile(string currentUser);
void decryptTextFile(string currentUser);
void toolkitMenu(string currentUser);
void aboutProject();

// ---------------------------------------------------------------
// main()
// ---------------------------------------------------------------
int main()
{
    int choice;
    string loggedInUser;
    bool loginSuccess;

    // Make sure the "Data" folder exists before anything else runs.
    // Every user workspace is stored inside it.
    ensureDataFolder();

    while (true)
    {
        clearScreen();
        printHeader("🔐  THE DEVELOPER'S TOOLKIT");
        cout << "   Secure file encryption with a private workspace for every user.\n";
        cout << "\n";
        cout << "📌 Main Menu - Please select an option\n";
        cout << "\n";
        cout << "   1️⃣   📝 Sign Up\n";
        cout << "   2️⃣   🔐 Log In\n";
        cout << "   3️⃣   ℹ️  About Project\n";
        cout << "   4️⃣   🚪 Exit\n";
        cout << "\n";
        printLine();
        cout << "👉 Enter your choice: ";
        choice = readMenuChoice();

        if (choice == 1)
        {
            clearScreen();
            signUp();
        }
        else if (choice == 2)
        {
            clearScreen();
            loginSuccess = logIn(loggedInUser);

            if (loginSuccess)
            {
                cout << "\n✅ Login successful.\n";
                waitForUser();
                toolkitMenu(loggedInUser);
            }
            else
            {
                // logIn() has already shown the exact reason
                // (wrong password, remaining attempts, or account locked),
                // so here we only pause so the user can read that message.
                waitForUser();
            }
        }
        else if (choice == 3)
        {
            // The About screen only prints text, so it cannot change any data.
            aboutProject();
        }
        else if (choice == 4)
        {
            cout << "\n👋 Thank you for using The Developer's Toolkit.\n";
            cout << "   Have a wonderful day!\n";
            break;
        }
        else
        {
            cout << "\n❌ Invalid option. Please enter a number from the menu.\n";
            waitForUser();
        }
    }

    return 0;
}
