// EnsureDataFolder.cpp
// This function makes sure the "Data" folder exists when the program starts.
// All user workspaces are kept inside this one folder.

#include <iostream>
#include <filesystem>
using namespace std;

// This function is defined in another folder.
void waitForUser();

// Creates the "Data" folder if it is missing.
// If the folder is already there, nothing happens and nothing is printed,
// so the user is not bothered every time the program starts.
void ensureDataFolder()
{
    if (!filesystem::exists("Data"))
    {
        cout << "📁 Creating Data folder...\n";

        filesystem::create_directory("Data");

        cout << "✅ Data folder ready.\n";
        waitForUser(); // pause so the message can be read before the menu
    }
}
