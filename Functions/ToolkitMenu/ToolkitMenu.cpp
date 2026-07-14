// ToolkitMenu.cpp
// This function shows the main toolkit menu after the user logs in.
// Only 2 tools are available: Encrypt Text File and Decrypt Text File.

#include <iostream>
#include <string>
using namespace std;

// These functions are defined in other folders.
void clearScreen();
void encryptTextFile(string currentUser);
void decryptTextFile(string currentUser);
void waitForUser();
void printHeader(string title);
void printLine();
int readMenuChoice();

void toolkitMenu(string currentUser)
{
    int choice;

    while (true)
    {
        clearScreen();
        printHeader("🧰  DEVELOPER TOOLKIT MENU");
        cout << "   👤 Logged in as : " << currentUser << "\n";
        cout << "   📂 Your folder  : Data/" << currentUser << "/\n";
        cout << "\n";
        cout << "📌 Please select a tool\n";
        cout << "\n";
        cout << "   1️⃣   🔒 Encrypt Text File\n";
        cout << "   2️⃣   🔓 Decrypt Text File\n";
        cout << "   3️⃣   🚪 Log Out\n";
        cout << "\n";
        printLine();
        cout << "👉 Enter your choice: ";
        choice = readMenuChoice();

        if (choice == 1)
        {
            clearScreen();
            // Pass the logged-in user so the file is saved in their own folder.
            encryptTextFile(currentUser);
        }
        else if (choice == 2)
        {
            clearScreen();
            // Pass the logged-in user so the file is saved in their own folder.
            decryptTextFile(currentUser);
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "\n❌ Invalid option. Please enter a number from the menu.\n";
            waitForUser();
        }
    }
}
