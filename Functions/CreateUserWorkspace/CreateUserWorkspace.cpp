// CreateUserWorkspace.cpp
// This function gives a user their own private folders inside "Data".
//
// The structure it builds looks like this:
//
//   Data/
//       Ali/
//           Encrypted/
//           Decrypted/

#include <iostream>
#include <string>
#include <filesystem>
using namespace std;

// Creates Data/<username>/Encrypted and Data/<username>/Decrypted.
// If the workspace already exists, it is left exactly as it is.
void createUserWorkspace(string username)
{
    string userFolder = "Data/" + username;

    // Never touch a workspace that is already there (it may hold files).
    if (filesystem::exists(userFolder))
    {
        cout << "\nℹ️  Existing workspace found.\n";
        return;
    }

    cout << "\n📂 Creating user workspace...\n";

    // create_directories() builds every missing folder in the path at once,
    // so "Data", the username folder, and the last folder are all made here.
    filesystem::create_directories(userFolder + "/Encrypted");
    filesystem::create_directories(userFolder + "/Decrypted");

    cout << "✅ Workspace created successfully.\n";
}
