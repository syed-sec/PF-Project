// ============================================================================
//  CPP_Project_V1_Complete.cpp
//  THE DEVELOPER'S TOOLKIT - complete program in ONE single file.
//
//  This file is a COPY of the multi-file project. The exact same program also
//  lives in "Main/main.cpp" + "Functions/<Name>/<Name>.cpp".
//
//  ⚠️  IMPORTANT: the same code now exists in TWO places. If you change
//      something here, make the SAME change in the Functions/ folder (and the
//      other way round), otherwise the two copies will slowly drift apart.
//
//  This single file exists so the whole program can be read top-to-bottom, or
//  compiled by itself without any folders:
//
//      g++ -std=c++17 -Wall "Complete Code/CPP_Project_V1_Complete.cpp" -o Toolkit.exe
//
//  NOTE: -std=c++17 is REQUIRED, because the program uses <filesystem>.
//
//  Layout of this file (same beginner style as the project):
//      1. Includes
//      2. Function prototypes (a one-line preview of every function)
//      3. The full code of every function
//      4. main() at the very end
//
//  👉 GROUP MEMBERS: the university details are already filled in. The ONLY
//     placeholders left are the team names and roll numbers, inside the
//     showTeamMembers() function. Replace those before you submit.
// ============================================================================

// ---------------------------------------------------------------
// 1. Includes
// ---------------------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem> // create folders (needs -std=c++17)
#include <vector>
#include <limits>
#include <cctype>
#include <ctime>   // time() - used for the account lock
#include <cstdlib> // system("cls")
#include <conio.h> // _getch() - hidden password input (Windows)
using namespace std;

// ---------------------------------------------------------------
// 2. Function prototypes
// ---------------------------------------------------------------

// Screen and input helpers
void clearScreen();
void waitForUser();
void clearInputLine();
void printHeader(string title);
void printLine();
int readMenuChoice();

// Accounts and security
bool usernameExists(string username);
bool isValidUsername(string username);
bool isStrongPassword(string password);
int getSecretKey();
string hashPassword(string username, string password);
string readPassword();
bool getUserRecord(string username, string &hashOut, long long &lockUntilOut);
void setUserLock(string username, long long lockUntil);

// Folders
void ensureDataFolder();
void createUserWorkspace(string username);

// Main features
void signUp();
bool logIn(string &loggedInUser);
string makeEncryptedFileName(string inputFileName);
string makeDecryptedFileName(string inputFileName);
void encryptTextFile(string currentUser);
void decryptTextFile(string currentUser);
void toolkitMenu(string currentUser);

// The About Project screen (and its small section helpers)
void aboutProject();
void showHeroSection();
void showProjectOverview();
void showProjectWorkflow();
void showFeatures();
void showFolderStructure();
void showTechnologies();
void showAdvantages();
void showFutureImprovements();
void showTeamMembers();
void showFeature(string icon, string name, string description, string benefit, string why);

// ---------------------------------------------------------------
// 3. Function definitions
// ---------------------------------------------------------------

// Clears the console screen on Windows.
void clearScreen()
{
    system("cls");
}

// Pauses the program so the user can read messages on screen.
// It waits until the user presses the Enter key.
void waitForUser()
{
    cout << "\n👉 Press Enter to continue...";

    // Wait for the user to press Enter by reading (and ignoring) one line.
    // The input buffer is kept clean elsewhere (every "cin >> ..." is
    // followed by clearInputLine()), so this reliably pauses until Enter.
    string dummyLine;
    getline(cin, dummyLine);
}

// Removes any leftover characters still waiting on the current input line,
// up to and including the Enter key.
//
// Why we need it: when we read a value with "cin >> something", the Enter key
// the user pressed stays behind in the input buffer. If we do not remove it,
// the next input step can misbehave (for example, a "Press Enter to continue"
// prompt might be skipped). Call this right AFTER every "cin >> ..." read.
void clearInputLine()
{
    // Discard everything up to and including the next newline character.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Prints the title bar shown at the top of every screen.
//
// Why it exists: before, every screen copy-pasted its own three lines of "=".
// Now all screens call this one function, so they all look exactly the same.
// If we ever want to change the design, we only change it HERE, in one place.
//
// This is a LOOKS-ONLY helper. It does not change any program logic.
void printHeader(string title)
{
    cout << "════════════════════════════════════════════════════════════\n";
    cout << "   " << title << "\n";
    cout << "════════════════════════════════════════════════════════════\n";
    cout << "\n";
}

// Prints a thin divider line, used just above the "Enter your choice" prompt
// on every menu. Like printHeader(), this is a LOOKS-ONLY helper.
void printLine()
{
    cout << "────────────────────────────────────────────────────────────\n";
}

// Safely reads a menu number from the user.
//
// Why it exists: if the user types a letter (or any non-number) at a menu, a
// plain "cin >> choice" fails and leaves the bad text stuck in the input
// buffer. That makes the menu loop repeat forever. This function detects that
// problem, cleans up the input, and returns -1 so the menu can simply show
// "Invalid choice" and continue safely.
int readMenuChoice()
{
    int choice;

    // Try to read a whole number from the user.
    if (!(cin >> choice))
    {
        // The user typed something that is not a number.
        cin.clear();      // remove the error flag so cin works again
        clearInputLine(); // throw away the bad text they typed
        return -1;        // -1 means "invalid choice"
    }

    // Reading worked. Remove the leftover Enter key from the buffer.
    clearInputLine();
    return choice;
}

// Checks if a username already exists in users.txt.
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

// Checks whether a username is SAFE to use as a folder name.
//
// Why it exists: the program builds every save path from the username, like
//     "Data/" + username + "/Encrypted"
// So a dangerous username becomes a dangerous folder path. For example, a user
// called ".." would produce "Data/../Encrypted", which escapes the Data folder
// completely and creates files where they do not belong.
//
// The rule is simple and strict: letters, digits and underscores only. That
// single rule blocks spaces, dots, slashes, and every other risky character.
bool isValidUsername(string username)
{
    // Rule 1: the length must be sensible.
    if (username.length() < 3 || username.length() > 20)
    {
        return false;
    }

    // Rule 2: only letters, digits and underscore are allowed.
    // This is what stops "..", "a/b", "my name" and similar dangerous names.
    for (size_t i = 0; i < username.length(); i++)
    {
        char c = username[i];

        bool isLetter = isalpha((unsigned char)c);
        bool isNumber = isdigit((unsigned char)c);
        bool isUnderscore = (c == '_');

        if (!isLetter && !isNumber && !isUnderscore)
        {
            return false;
        }
    }

    // Rule 3: Windows refuses to create a folder with these special names,
    // so an account using one of them could never get a workspace.
    // We compare in UPPERCASE so "con", "Con" and "CON" are all caught.
    string upperName = "";

    for (size_t i = 0; i < username.length(); i++)
    {
        upperName += (char)toupper((unsigned char)username[i]);
    }

    string reservedNames[] = {
        "CON", "PRN", "AUX", "NUL",
        "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
        "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"};

    // Let the compiler count the list for us. If we wrote the number by hand
    // and got it wrong, the loop would read past the end of the array.
    int reservedCount = sizeof(reservedNames) / sizeof(reservedNames[0]);

    for (int i = 0; i < reservedCount; i++)
    {
        if (upperName == reservedNames[i])
        {
            return false;
        }
    }

    // The username passed every rule, so it is safe to use as a folder name.
    return true;
}

// Returns the secret key used by the Caesar cipher.
//
// Why it exists: before, the number 5 was written separately inside the encrypt
// AND decrypt functions. If someone changed one and forgot the other,
// decryption would quietly produce garbage with NO error message at all.
// Now both ask this one function, so the two can never disagree.
// To change the key for the whole program, change it HERE only.
int getSecretKey()
{
    return 5;
}

// Checks whether a password is "strong enough".
// Rules: at least 8 characters, and at least one uppercase letter,
// one lowercase letter, one digit, and one special character.
bool isStrongPassword(string password)
{
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    if (password.length() < 8)
    {
        return false;
    }

    // size_t matches the type returned by password.length(), which avoids a
    // signed/unsigned comparison warning.
    for (size_t i = 0; i < password.length(); i++)
    {
        char c = password[i];

        if (isupper((unsigned char)c))
        {
            hasUpper = true;
        }
        else if (islower((unsigned char)c))
        {
            hasLower = true;
        }
        else if (isdigit((unsigned char)c))
        {
            hasDigit = true;
        }
        else if (!isspace((unsigned char)c))
        {
            // Anything that's not a letter, digit, or whitespace
            // counts as a special character (e.g. ! @ # $ %).
            hasSpecial = true;
        }
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// Turns a password into a scrambled "hash" so that the real password is NEVER
// saved in users.txt. When the user logs in, we hash what they type and compare
// it to the saved hash.
//
// We mix the username into the password before hashing (this extra text is
// called a "salt"). Salting means two users who happen to pick the same
// password still get different hashes.
//
// IMPORTANT: This is a simple hash meant for LEARNING. It is NOT strong enough
// for real banking or production apps. For real systems you would use a proven,
// well-tested library such as bcrypt or Argon2.
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
        hashValue = hashValue >> 4;                // move to the next 4 bits
    }

    return result;
}

// Reads a password from the keyboard WITHOUT showing the real characters.
// It prints a '*' for each typed character, supports Backspace, and finishes
// when the user presses Enter. The real password is returned to the caller so
// it can be hashed and checked.
//
// NOTE: This uses _getch() from <conio.h>, which is available on Windows.
string readPassword()
{
    string password = "";

    while (true)
    {
        int ch = _getch(); // read one key, but do NOT show it on the screen

        if (ch == 13) // 13 is the Enter key -> the user finished typing
        {
            break;
        }
        else if (ch == 8) // 8 is the Backspace key
        {
            // Only delete if there is at least one character to remove.
            if (!password.empty())
            {
                password.pop_back(); // remove the last real character
                cout << "\b \b";     // erase the last '*' shown on the screen
            }
        }
        else if (ch == 0 || ch == 224)
        {
            // Arrow keys and function keys send a special two-part code.
            // We read and ignore the second part so it does not become a '*'.
            _getch();
        }
        else
        {
            password += (char)ch; // keep the real character in memory
            cout << "*";          // show a star instead of the real character
        }
    }

    cout << "\n"; // move to the next line after the user presses Enter
    return password;
}

// Looks up ONE account in users.txt by its username. If the account is found,
// it fills in the saved password hash and the account's lock time, and returns
// true. If the account is not found, it returns false.
//
// Each line in users.txt has 3 parts:  username  passwordHash  lockUntil
//   - lockUntil is a time value in seconds. 0 means the account is NOT locked.
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
            hashOut = storedHash;      // give the saved hash back to the caller
            lockUntilOut = storedLock; // give the saved lock time back too
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Saves a new "lock time" for ONE account in users.txt. A text file cannot be
// edited in the middle easily, so we do it the simple beginner way: read ALL
// accounts into memory, change the one we need, then write them all back.
//
// lockUntil is a time value in seconds. The account stays locked until the
// computer's clock passes this time. 0 means the account is not locked.
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

// Creates Data/<username>/Encrypted and Data/<username>/Decrypted.
// If the workspace already exists, it is left exactly as it is.
//
// The structure it builds looks like this:
//
//   Data/
//       Ali/
//           Encrypted/
//           Decrypted/
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

// Creates a new user account and saves it in users.txt.
// A strong password is REQUIRED before the account can be created.
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

// Logs a user in. It includes three extra features:
//   1. Hidden password input (shown on screen as '*').
//   2. Up to 5 password attempts, WITHOUT leaving the Login screen.
//   3. A 30-minute account lock after 5 wrong attempts. The lock time is
//      saved in users.txt, so it still works even if the program restarts.
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

// Creates the encrypted file name from the original file name.
string makeEncryptedFileName(string inputFileName)
{
    string baseName = inputFileName;
    string extension = "";
    int dotPosition = -1;
    int inputLength = inputFileName.length();

    // Find the last dot so the extension can be kept.
    for (int i = inputLength - 1; i >= 0; i--)
    {
        if (inputFileName[i] == '.')
        {
            dotPosition = i;
            break;
        }
    }

    // Split the file name into name and extension.
    if (dotPosition != -1)
    {
        baseName = inputFileName.substr(0, dotPosition);
        extension = inputFileName.substr(dotPosition);
    }

    return baseName + "_encrypted" + extension;
}

// Creates the decrypted file name from the encrypted file name.
string makeDecryptedFileName(string inputFileName)
{
    string outputName = inputFileName;
    string searchText = "_encrypted";
    int foundPosition = -1;
    int inputLength = inputFileName.length();
    int searchLength = searchText.length();

    // Find the text "_encrypted" in the file name.
    if (inputLength >= searchLength)
    {
        for (int i = 0; i <= inputLength - searchLength; i++)
        {
            bool match = true;

            for (int j = 0; j < searchLength; j++)
            {
                if (inputFileName[i + j] != searchText[j])
                {
                    match = false;
                    break;
                }
            }

            if (match)
            {
                foundPosition = i;
                break;
            }
        }
    }

    // Replace "_encrypted" with "_decrypted" if it exists.
    if (foundPosition != -1)
    {
        outputName = inputFileName.substr(0, foundPosition) + "_decrypted";

        // Keep the extension after "_encrypted".
        outputName = outputName + inputFileName.substr(foundPosition + searchText.length());
    }
    else
    {
        // If "_encrypted" is not found, just add "_decrypted" at the end.
        outputName = inputFileName + "_decrypted";
    }

    return outputName;
}

// Encrypts a text file using a simple Caesar cipher shift.
// Every character (including spaces and newlines) is shifted by a secret key.
//
// currentUser is the person who is logged in right now. It is used to save the
// encrypted file inside that user's own folder, so two users never mix files.
void encryptTextFile(string currentUser)
{
    string inputFileName;
    string outputFileName;
    // Ask for the one shared key, so encryption and decryption can never
    // use different numbers by mistake.
    int secretKey = getSecretKey();

    printHeader("🔒  ENCRYPT TEXT FILE");

    cout << "   The locked file will be saved in: Data/" << currentUser << "/Encrypted/\n";
    cout << "\n";
    cout << "📂 Enter the input text file name: ";
    cin >> inputFileName;
    clearInputLine(); // remove the leftover Enter key from the buffer

    // This is where the encrypted file will be saved.
    string outputFolder = "Data/" + currentUser + "/Encrypted";

    // Make the folder if it is missing. Nothing happens if it already exists.
    filesystem::create_directories(outputFolder);

    // Keep only the file name itself, without any folder the user may have
    // typed. So "C:\notes\diary.txt" is saved as "diary_encrypted.txt" here.
    string justTheFileName = filesystem::path(inputFileName).filename().string();

    // Create the output file name, then place it inside the user's folder.
    outputFileName = outputFolder + "/" + makeEncryptedFileName(justTheFileName);

    // Open the input file FIRST and make sure it exists. We do not open the
    // output file yet, because creating an ofstream immediately makes an empty
    // file on disk, and we do not want a stray file if the input is invalid.
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        cout << "\n❌ Input file could not be opened.\n";
        waitForUser();
        return;
    }

    // The input is valid, so now it is safe to create the output file.
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        cout << "\n❌ Output file could not be created.\n";
        waitForUser();
        return;
    }

    char currentChar;
    bool hasData = false;

    // Read the file character by character, including spaces and newlines.
    while (inputFile.get(currentChar))
    {
        hasData = true;

        // Work with the byte value (0-255) so the shift is always safe and
        // can be reversed exactly during decryption. The % 256 keeps the
        // result inside a single byte.
        unsigned char originalByte = (unsigned char)currentChar;
        unsigned char shiftedByte = (unsigned char)((originalByte + secretKey) % 256);

        outputFile.put((char)shiftedByte);
    }

    inputFile.close();
    outputFile.close();

    if (hasData)
    {
        cout << "\n✅ File encrypted successfully.\n";
        cout << "💾 Encrypted output saved in: " << outputFileName << endl;
    }
    else
    {
        cout << "\n⚠️  The input file could not be read or it was empty.\n";
    }

    waitForUser();
}

// Decrypts a text file that was encrypted with encryptTextFile().
//
// currentUser is the person who is logged in right now. It is used to save the
// decrypted file inside that user's own folder, so two users never mix files.
void decryptTextFile(string currentUser)
{
    string inputFileName;
    string outputFileName;
    // The SAME shared key that encryption used. Because both functions call
    // this one function, the two keys can never drift apart.
    int secretKey = getSecretKey();

    printHeader("🔓  DECRYPT TEXT FILE");

    cout << "   Looking in    : Data/" << currentUser << "/Encrypted/\n";
    cout << "   Will save into: Data/" << currentUser << "/Decrypted/\n";
    cout << "\n";
    cout << "📂 Enter the encrypted file name: ";
    cin >> inputFileName;
    clearInputLine(); // remove the leftover Enter key from the buffer

    // Encrypted files live in the user's own Encrypted folder. If the name the
    // user typed is not found as it is, look inside that folder before giving
    // up. This way the user can simply type "diary_encrypted.txt".
    if (!filesystem::exists(inputFileName))
    {
        string fileInWorkspace = "Data/" + currentUser + "/Encrypted/" + inputFileName;

        if (filesystem::exists(fileInWorkspace))
        {
            inputFileName = fileInWorkspace;
        }
    }

    // This is where the decrypted file will be saved.
    string outputFolder = "Data/" + currentUser + "/Decrypted";

    // Make the folder if it is missing. Nothing happens if it already exists.
    filesystem::create_directories(outputFolder);

    // Keep only the file name itself, without any folder in front of it.
    string justTheFileName = filesystem::path(inputFileName).filename().string();

    // Create the output file name, then place it inside the user's folder.
    outputFileName = outputFolder + "/" + makeDecryptedFileName(justTheFileName);

    // Open the encrypted input file FIRST and make sure it exists. We do not
    // open the output file yet, because creating an ofstream immediately makes
    // an empty file on disk, and we do not want a stray file if the input is
    // invalid.
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        cout << "\n❌ Encrypted file could not be opened.\n";
        waitForUser();
        return;
    }

    // The input is valid, so now it is safe to create the output file.
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        cout << "\n❌ Output file could not be created.\n";
        waitForUser();
        return;
    }

    char currentChar;
    bool hasData = false;

    // Read the encrypted file character by character.
    while (inputFile.get(currentChar))
    {
        hasData = true;

        // Work with the byte value (0-255). Adding 256 before the % keeps the
        // result positive, so subtracting the key exactly reverses encryption.
        unsigned char encryptedByte = (unsigned char)currentChar;
        unsigned char originalByte = (unsigned char)((encryptedByte - secretKey + 256) % 256);

        outputFile.put((char)originalByte);
    }

    inputFile.close();
    outputFile.close();

    if (hasData)
    {
        cout << "\n✅ File decrypted successfully.\n";
        cout << "💾 Decrypted output saved in: " << outputFileName << endl;
    }
    else
    {
        cout << "\n⚠️  The encrypted file could not be read or it was empty.\n";
    }

    waitForUser();
}

// Shows the main toolkit menu after the user logs in.
// Only 2 tools are available: Encrypt Text File and Decrypt Text File.
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

// ===========================================================================
//  THE "ABOUT PROJECT" SCREEN
//
//  This part only prints text. It never reads, writes, encrypts or deletes
//  any file, so it cannot break the rest of the program.
//
//  👉 GROUP MEMBERS: the placeholders below (written like [Like This]) are the
//     ONLY things you need to change before you submit.
// ===========================================================================

// Prints the top "hero" section: the project's name card.
void showHeroSection()
{
    printHeader("🔐  THE DEVELOPER'S TOOLKIT");

    cout << "   A secure, menu-based file encryption tool that gives every user\n";
    cout << "   their own private, password-protected workspace.\n";
    cout << "\n";
    cout << "   📚 Subject           : Programming Fundamentals Theory\n";
    cout << "   🎓 Program           : BS Cyber Security\n";
    cout << "   🏛️  University        : The Superior University, Lahore\n";
    cout << "   👨‍🏫 Instructor        : Prof. Zeeshan Mubeen\n";
    cout << "   📅 Academic Session  : 2025-2029\n";
    cout << "   👥 Project Type      : Group Project\n";
    cout << "\n";
}

// Explains why the project exists and what it does.
void showProjectOverview()
{
    clearScreen();
    printHeader("📖  PROJECT OVERVIEW");

    cout << "   WHY WE BUILT IT\n";
    cout << "   ---------------\n";
    cout << "   Text files on a shared computer are open for anyone to read. In a\n";
    cout << "   computer lab, a hostel room, or a family PC, a private file is only\n";
    cout << "   one double-click away from being seen by someone else.\n";
    cout << "\n";
    cout << "   THE PROBLEM IT SOLVES\n";
    cout << "   ---------------------\n";
    cout << "   1. Plain text files can be read by anybody.\n";
    cout << "   2. Files belonging to different people get mixed into one folder.\n";
    cout << "   3. There is no login, so there is no idea of \"my files\".\n";
    cout << "\n";
    cout << "   OUR SOLUTION\n";
    cout << "   ------------\n";
    cout << "   The Toolkit puts a login in front of the files, scrambles the text\n";
    cout << "   so it cannot be read, and gives every single user a private folder\n";
    cout << "   of their own. Two users can even encrypt files with the SAME name\n";
    cout << "   and they will never overwrite or see each other's work.\n";
    cout << "\n";
    cout << "   WHO CAN USE IT\n";
    cout << "   --------------\n";
    cout << "   Students, teachers, or anyone who shares a computer and wants to\n";
    cout << "   keep notes, answers, or personal text private.\n";
    cout << "\n";

    waitForUser();
    clearScreen();
    printHeader("📖  PROJECT OVERVIEW  (continued)");

    cout << "   OUR OBJECTIVES\n";
    cout << "   --------------\n";
    cout << "   1. Practise C++ file handling, functions, loops and conditions.\n";
    cout << "   2. Build a real login system with hashed (scrambled) passwords.\n";
    cout << "   3. Keep every user's data completely separate.\n";
    cout << "   4. Write code that a first-year student can actually read.\n";
    cout << "\n";
    cout << "   WHAT HAPPENS FROM LOGIN UNTIL LOGOUT\n";
    cout << "   ------------------------------------\n";
    cout << "   1. You start the program. It makes the \"Data\" folder if missing.\n";
    cout << "   2. You sign up. Your username must be new, and your password must\n";
    cout << "      be strong. Your password is scrambled before it is saved.\n";
    cout << "   3. Signing up creates your private workspace:\n";
    cout << "         Data/<YourName>/Encrypted/  and  Data/<YourName>/Decrypted/\n";
    cout << "   4. You log in. You get 5 tries. After 5 wrong passwords the\n";
    cout << "      account locks itself for 30 minutes.\n";
    cout << "   5. The Toolkit Menu opens and shows your name at the top.\n";
    cout << "   6. You choose Encrypt or Decrypt, and type a file name.\n";
    cout << "   7. The result is saved inside YOUR folder. Never anyone else's.\n";
    cout << "   8. You log out and return to the Main Menu. Your files stay safe\n";
    cout << "      on the disk, waiting for your next login.\n";
    cout << "\n";

    waitForUser();
}

// Draws the step-by-step workflow of the program.
void showProjectWorkflow()
{
    clearScreen();
    printHeader("🔄  PROJECT WORKFLOW");

    cout << "            ┌──────────────────────────┐\n";
    cout << "            │    Open Application      │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │  \"Data\" folder is ready  │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │      Create Account      │\n";
    cout << "            │  (private folders made)  │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │          Login           │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │     Choose Operation     │\n";
    cout << "            │   (Encrypt or Decrypt)   │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │       Select File        │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │    Encrypt / Decrypt     │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │  Save Output in YOUR     │\n";
    cout << "            │      own folder          │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "                         ↓\n";
    cout << "            ┌──────────────────────────┐\n";
    cout << "            │          Logout          │\n";
    cout << "            └──────────────────────────┘\n";
    cout << "\n";

    waitForUser();
}

// Prints ONE feature in a neat, repeated shape.
// Using this small helper keeps the big features list short and tidy.
void showFeature(string icon, string name, string description, string benefit, string why)
{
    cout << "   " << icon << "  " << name << "\n";
    cout << "      What    : " << description << "\n";
    cout << "      Benefit : " << benefit << "\n";
    cout << "      Why     : " << why << "\n";
    cout << "\n";
}

// Shows every feature in the project.
// The list is long, so it is shown a few features at a time.
void showFeatures()
{
    // ---------------- Page 1: Accounts and security ----------------
    clearScreen();
    printHeader("⭐  FEATURES  (1 of 4)  -  Accounts & Security");

    showFeature("👤", "User Registration",
                "Creates a brand new account with a username and a password.",
                "Every person gets their own identity inside the program.",
                "Without accounts, all files would belong to everybody.");

    showFeature("🔐", "Secure Login",
                "Checks your username and password before letting you in.",
                "Nobody can open your files by simply starting the program.",
                "A lock is useless if there is no door in front of it.");

    showFeature("✏️", "Username Validation",
                "Makes sure the username you choose is not already taken.",
                "Two people can never share one identity or one folder.",
                "Duplicate names would mix two users' files together.");

    showFeature("🛡️", "Password Validation",
                "Requires 8+ characters with upper, lower, digit and symbol.",
                "Weak passwords like \"12345\" are refused straight away.",
                "A short password can be guessed in seconds.");

    showFeature("🔑", "Password Hashing",
                "Scrambles the password before saving it (FNV-1a + salt).",
                "Even if someone opens users.txt, they see nonsense, not your password.",
                "Real passwords must NEVER be stored as plain readable text.");

    waitForUser();

    // ---------------- Page 2: Protection ----------------
    clearScreen();
    printHeader("⭐  FEATURES  (2 of 4)  -  Protection");

    showFeature("🚫", "Duplicate Username Detection",
                "Spots a taken username and asks you for a different one.",
                "You stay on the Sign Up screen instead of starting over.",
                "Being thrown back to the Main Menu would be annoying.");

    showFeature("❌", "Incorrect Password Handling",
                "Counts your wrong tries and shows how many are left (out of 5).",
                "You know exactly where you stand before the lock happens.",
                "Silent failure is confusing and feels broken.");

    showFeature("⏰", "Account Lock (30 minutes)",
                "Locks the account for 30 minutes after 5 wrong passwords.",
                "Stops someone guessing your password again and again.",
                "Unlimited guesses would eventually break any password.");

    showFeature("💾", "Lock Survives Restart",
                "The lock time is saved inside users.txt, not just in memory.",
                "Closing and reopening the program does NOT clear the lock.",
                "Otherwise a guesser could just restart the program to reset it.");

    showFeature("👁️", "Hidden Password Input",
                "Shows a '*' for each key you type instead of the real letter.",
                "Someone standing behind you cannot read your password.",
                "Passwords should never be shown openly on the screen.");

    showFeature("🔒", "Individual User Accounts",
                "Every account is a separate record inside users.txt.",
                "Your account is fully independent from everyone else's.",
                "Shared accounts mean no real privacy at all.");

    waitForUser();

    // ---------------- Page 3: Files and folders ----------------
    clearScreen();
    printHeader("⭐  FEATURES  (3 of 4)  -  Files & Folders");

    showFeature("📁", "Automatic Data Directory",
                "Creates the \"Data\" folder by itself when the program starts.",
                "You never have to make any folder by hand.",
                "A missing folder would make every file operation fail.");

    showFeature("📂", "Separate Folder for Every User",
                "Builds Data/<Username>/ the moment you register.",
                "Your files live in your own private space.",
                "One shared folder would mix everybody's work together.");

    showFeature("🔒", "Encrypted Files Folder",
                "All your encrypted files go into Data/<You>/Encrypted/.",
                "Locked files are always in one predictable place.",
                "Scattered files are easy to lose and hard to find.");

    showFeature("🔓", "Decrypted Files Folder",
                "All your decrypted files go into Data/<You>/Decrypted/.",
                "Readable files never sit next to the locked ones.",
                "Mixing them up risks encrypting an already-encrypted file.");

    showFeature("🚧", "No Mixing Between Users",
                "The logged-in name is used to build every save path.",
                "Two users may encrypt \"notes.txt\" and never clash.",
                "This is the single most important privacy rule of the project.");

    showFeature("🗂️", "Organized Storage",
                "Every file has exactly one correct home folder.",
                "The project stays tidy even after months of use.",
                "Messy storage is the fastest way to lose real work.");

    waitForUser();

    // ---------------- Page 4: Files, input and interface ----------------
    clearScreen();
    printHeader("⭐  FEATURES  (4 of 4)  -  Files, Input & Interface");

    showFeature("🔒", "File Encryption",
                "Shifts every byte of the file by a secret key (Caesar cipher).",
                "The text becomes unreadable to anyone who opens it.",
                "This is the core purpose of the whole project.");

    showFeature("🔓", "File Decryption",
                "Shifts every byte back by the same key to restore the text.",
                "You get your original file back, exactly as it was.",
                "Encryption is worthless if you cannot reverse it.");

    showFeature("📄", "Smart File Selection",
                "If the name is not found, it also looks in YOUR Encrypted folder.",
                "You can type \"notes_encrypted.txt\" instead of a long path.",
                "Typing a full folder path every time is slow and error-prone.");

    showFeature("🏷️", "Automatic File Naming",
                "Adds \"_encrypted\" or \"_decrypted\" and keeps the extension.",
                "Your original file is never overwritten or destroyed.",
                "Overwriting the input would lose the user's real data.");

    showFeature("📥", "Safe File Reading & Writing",
                "Reads and writes the file one character at a time, spaces included.",
                "Nothing in the file is skipped, changed or lost.",
                "A cipher must handle EVERY byte or it cannot be reversed.");

    showFeature("⚠️", "Error Messages",
                "Reports a missing file, an unwritable folder, or an empty file.",
                "You always know exactly what went wrong and why.",
                "Silent failure makes a program impossible to trust.");

    showFeature("✅", "Success Messages",
                "Confirms the action and prints the full path of the saved file.",
                "You know precisely where your new file was placed.",
                "\"It worked\" is useless if you cannot find the result.");

    showFeature("⌨️", "Menu Input Validation",
                "Catches letters typed at a number menu and cleans the buffer.",
                "A typo shows \"Invalid option\" instead of freezing the program.",
                "Without this, one wrong key causes an endless menu loop.");

    showFeature("🖥️", "Console & Screen Management",
                "Clears the screen and pauses so you can read each message.",
                "Every screen stays clean and readable.",
                "Text piling up endlessly looks unprofessional and confusing.");

    showFeature("🧭", "Simple Navigation",
                "Numbered menus with a clear way back at every step.",
                "You can never get stuck or trapped inside a screen.",
                "A user should always be able to go back or leave.");

    showFeature("🌱", "Beginner-Friendly Design",
                "Small functions, plain names, and a comment on every function.",
                "A new group member can understand the code quickly.",
                "Code is read far more often than it is written.");

    waitForUser();
}

// Shows the folder layout and explains what each folder is for.
void showFolderStructure()
{
    clearScreen();
    printHeader("🗂️  FOLDER STRUCTURE");

    cout << "   C++ Project V1/\n";
    cout << "   │\n";
    cout << "   ├── Main/                  → holds main(), the program's entry point\n";
    cout << "   │   └── main.cpp           → the Main Menu and the prototype list\n";
    cout << "   │\n";
    cout << "   ├── Functions/             → one folder per function (no .h files)\n";
    cout << "   │   ├── SignUp/            → creating a new account\n";
    cout << "   │   ├── LogIn/             → checking password, attempts, lock\n";
    cout << "   │   ├── EncryptTextFile/   → locking a file\n";
    cout << "   │   ├── DecryptTextFile/   → unlocking a file\n";
    cout << "   │   ├── AboutProject/      → this About screen\n";
    cout << "   │   └── ... and more       → one small job each\n";
    cout << "   │\n";
    cout << "   ├── Complete Code/         → the SAME program in one single file,\n";
    cout << "   │                            for easy reading and submission\n";
    cout << "   │\n";
    cout << "   ├── docs/                  → written documentation\n";
    cout << "   │   ├── Developer_Guide.md → deep guide for us, the group members\n";
    cout << "   │   └── Project_Overview.md→ short summary for the teacher\n";
    cout << "   │\n";
    cout << "   ├── Data/                  → made automatically at startup\n";
    cout << "   │   ├── Ali/               → one folder per registered user\n";
    cout << "   │   │   ├── Encrypted/     → Ali's locked files\n";
    cout << "   │   │   └── Decrypted/     → Ali's unlocked files\n";
    cout << "   │   └── Ahmed/             → completely separate from Ali\n";
    cout << "   │       ├── Encrypted/\n";
    cout << "   │       └── Decrypted/\n";
    cout << "   │\n";
    cout << "   ├── users.txt              → all accounts: name, hash, lock time\n";
    cout << "   └── build.bat              → compiles and runs the program\n";
    cout << "\n";
    cout << "   💡 The golden rule: a user's files NEVER leave their own folder.\n";
    cout << "\n";

    waitForUser();
}

// Explains every technology and C++ topic used in the project.
void showTechnologies()
{
    clearScreen();
    printHeader("🛠️  TECHNOLOGIES USED  (1 of 2)");

    cout << "   ⚙️  C++ (standard C++17)\n";
    cout << "      What  : A fast, compiled programming language.\n";
    cout << "      Why   : It is our course language and it is close to the machine.\n";
    cout << "      Where : Every single file in the project.\n";
    cout << "\n";
    cout << "   📁  File Handling  (<fstream>)\n";
    cout << "      What  : ifstream reads files, ofstream writes files.\n";
    cout << "      Why   : Accounts and encrypted files must survive a restart.\n";
    cout << "      Where : users.txt, and every encrypt/decrypt operation.\n";
    cout << "\n";
    cout << "   🗄️  Filesystem  (<filesystem>)\n";
    cout << "      What  : Creates folders and checks whether a path exists.\n";
    cout << "      Why   : The Data and per-user folders must be made automatically.\n";
    cout << "      Where : ensureDataFolder(), createUserWorkspace(), encrypt, decrypt.\n";
    cout << "\n";
    cout << "   🧩  Functions\n";
    cout << "      What  : Small named blocks of code that do ONE job.\n";
    cout << "      Why   : Small pieces are easy to read, test and fix.\n";
    cout << "      Where : Each one lives in its own folder under Functions/.\n";
    cout << "\n";
    cout << "   🔤  Strings  (<string>)\n";
    cout << "      What  : Text that can grow and shrink.\n";
    cout << "      Why   : Usernames, passwords, file names and paths are all text.\n";
    cout << "      Where : Everywhere. Paths are built by joining strings together.\n";
    cout << "\n";

    waitForUser();

    clearScreen();
    printHeader("🛠️  TECHNOLOGIES USED  (2 of 2)");

    cout << "   🔁  Loops  (while / for)\n";
    cout << "      What  : Repeat a block of code.\n";
    cout << "      Why   : Menus repeat until you exit; files are read byte by byte.\n";
    cout << "      Where : Every menu, the password retry loop, the cipher loop.\n";
    cout << "\n";
    cout << "   ❓  Conditions  (if / else)\n";
    cout << "      What  : Choose between two paths.\n";
    cout << "      Why   : \"Is the password right?\" \"Does this folder exist?\"\n";
    cout << "      Where : Login checks, menu choices, every error check.\n";
    cout << "\n";
    cout << "   📚  Arrays & Vectors  (<vector>)\n";
    cout << "      What  : A list that holds many values of the same type.\n";
    cout << "      Why   : To hold every account in memory while updating one lock.\n";
    cout << "      Where : setUserLock(), which rewrites users.txt safely.\n";
    cout << "\n";
    cout << "   🧮  The Standard Library\n";
    cout << "      What  : Ready-made tools that ship with C++.\n";
    cout << "      Why   : We should not rebuild what already exists and works.\n";
    cout << "      Where : <iostream> screen, <ctime> lock timing, <cctype> letter\n";
    cout << "              checks, <conio.h> hidden password input.\n";
    cout << "\n";
    cout << "   🔐  Caesar Cipher + FNV-1a Hash\n";
    cout << "      What  : A byte-shift cipher, and a one-way password scrambler.\n";
    cout << "      Why   : Simple enough to fully understand, real enough to work.\n";
    cout << "      Where : encryptTextFile(), decryptTextFile(), hashPassword().\n";
    cout << "\n";

    waitForUser();
}

// Lists the advantages of the project.
void showAdvantages()
{
    clearScreen();
    printHeader("✨  ADVANTAGES  (1 of 2)");

    cout << "   🎓 Easy to Learn\n";
    cout << "      No classes, no pointers, no templates. Only the C++ topics from\n";
    cout << "      first year, used the way they are actually taught.\n";
    cout << "\n";
    cout << "   😊 Simple User Experience\n";
    cout << "      Numbered menus only. If you can count to four, you can use it.\n";
    cout << "\n";
    cout << "   🗂️ Organized Data\n";
    cout << "      Every file has exactly one correct home. Nothing is ever loose.\n";
    cout << "\n";
    cout << "   🔐 Secure File Management\n";
    cout << "      Files are unreadable once locked, and passwords are never saved\n";
    cout << "      as plain text anywhere on the disk.\n";
    cout << "\n";
    cout << "   🙋 Individual User Privacy\n";
    cout << "      Your folder is yours. Another user simply cannot reach it through\n";
    cout << "      the program, no matter what they type.\n";
    cout << "\n";
    cout << "   🛠️ Easy Maintenance\n";
    cout << "      One function, one folder, one job. To fix login, you open exactly\n";
    cout << "      one file: LogIn.cpp.\n";
    cout << "\n";

    waitForUser();

    clearScreen();
    printHeader("✨  ADVANTAGES  (2 of 2)");

    cout << "   ♻️ Reusable Code\n";
    cout << "      printHeader(), waitForUser() and readMenuChoice() are written once\n";
    cout << "      and reused by every screen in the program.\n";
    cout << "\n";
    cout << "   🪶 Lightweight\n";
    cout << "      One small .exe. No database, no internet, no installer, no setup.\n";
    cout << "\n";
    cout << "   ⚡ Fast Performance\n";
    cout << "      The cipher is one addition per byte, so files process instantly.\n";
    cout << "\n";
    cout << "   🧱 Clean Structure\n";
    cout << "      You can guess where any piece of code lives just from its name.\n";
    cout << "\n";
    cout << "   🌱 Expandable Design\n";
    cout << "      To add a tool, write one new folder and add one menu line. No\n";
    cout << "      existing code has to be rewritten.\n";
    cout << "\n";
    cout << "   🛡️ Safe by Default\n";
    cout << "      The original file is never overwritten, a bad file name is caught\n";
    cout << "      before anything is written, and a wrong key press cannot crash it.\n";
    cout << "\n";
    cout << "   📖 Fully Documented\n";
    cout << "      Every function has a comment, and the docs/ folder explains the\n";
    cout << "      whole project for both group members and teachers.\n";
    cout << "\n";

    waitForUser();
}

// Lists honest, realistic future improvements.
void showFutureImprovements()
{
    clearScreen();
    printHeader("🚀  FUTURE IMPROVEMENTS");

    cout << "   These are the next steps we would take if the project continued.\n";
    cout << "\n";
    cout << "   🔐 AES Encryption        Replace the Caesar cipher with a real,\n";
    cout << "                            industry-standard algorithm.\n";
    cout << "\n";
    cout << "   🗄️ Database Integration  Store accounts in SQLite instead of a\n";
    cout << "                            plain users.txt file.\n";
    cout << "\n";
    cout << "   ☁️ Cloud Storage         Sync each user's folder online so files\n";
    cout << "                            are safe if the computer is lost.\n";
    cout << "\n";
    cout << "   🔁 Password Recovery     A safe way back in for a user who has\n";
    cout << "                            forgotten their password.\n";
    cout << "\n";
    cout << "   👤 User Profiles         A real name, an email, and a photo for\n";
    cout << "                            each account.\n";
    cout << "\n";
    cout << "   🔍 File Search           Search inside your own folder by file\n";
    cout << "                            name or by date.\n";
    cout << "\n";
    cout << "   👮 Admin Panel           An admin who can unlock a locked account\n";
    cout << "                            or remove an old user.\n";
    cout << "\n";
    cout << "   📝 Activity Logs         Record every login, encryption and error\n";
    cout << "                            with the time it happened.\n";
    cout << "\n";
    cout << "   💾 Backup & Restore      Save and restore a whole workspace as a\n";
    cout << "                            single compressed file.\n";
    cout << "\n";
    cout << "   🌍 Multi-language        Show the menus in Urdu as well as English.\n";
    cout << "\n";
    cout << "   🌙 Dark / Light Themes   Let the user pick the console colours.\n";
    cout << "\n";
    cout << "   💻 Multi-device Support  Build for Linux and macOS too, by replacing\n";
    cout << "                            the Windows-only \"cls\" and _getch().\n";
    cout << "\n";

    waitForUser();
}

// Shows the team.
// 👉 GROUP MEMBERS: replace the placeholders below with your real details.
void showTeamMembers()
{
    clearScreen();
    printHeader("👥  TEAM MEMBERS");

    cout << "   👑 Group Leader\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   🧑 Member 2\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   🧑 Member 3\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   🧑 Member 4\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   🧑 Member 5\n";
    cout << "      Name        : Syed Muhammad Shah\n";
    cout << "      Roll Number : SU92-BSCBM-F25\n";
    cout << "\n";
    cout << "   ℹ️  Members 2-5 currently repeat the leader's details.\n";
    cout << "       Replace them with each member's real name and roll number\n";
    cout << "       before submitting.\n";
    cout << "\n";

    waitForUser();
}

// The About Project menu. It shows the hero card, then lets the user pick a
// section to read. It only prints text, so it can never damage any data.
void aboutProject()
{
    int choice;

    while (true)
    {
        clearScreen();
        showHeroSection();

        cout << "   📌 Select a section to read\n";
        cout << "\n";
        cout << "      1️⃣   📖 Project Overview\n";
        cout << "      2️⃣   🔄 Project Workflow\n";
        cout << "      3️⃣   ⭐ Complete Features\n";
        cout << "      4️⃣   🗂️  Folder Structure\n";
        cout << "      5️⃣   🛠️  Technologies Used\n";
        cout << "      6️⃣   ✨ Advantages\n";
        cout << "      7️⃣   🚀 Future Improvements\n";
        cout << "      8️⃣   👥 Team Members\n";
        cout << "      9️⃣   🔙 Back to Main Menu\n";
        cout << "\n";
        printLine();
        cout << "👉 Enter your choice: ";
        choice = readMenuChoice();

        if (choice == 1)
        {
            showProjectOverview();
        }
        else if (choice == 2)
        {
            showProjectWorkflow();
        }
        else if (choice == 3)
        {
            showFeatures();
        }
        else if (choice == 4)
        {
            showFolderStructure();
        }
        else if (choice == 5)
        {
            showTechnologies();
        }
        else if (choice == 6)
        {
            showAdvantages();
        }
        else if (choice == 7)
        {
            showFutureImprovements();
        }
        else if (choice == 8)
        {
            showTeamMembers();
        }
        else if (choice == 9)
        {
            break; // leave the About screen and go back to the Main Menu
        }
        else
        {
            cout << "\n❌ Invalid option. Please enter a number from the menu.\n";
            waitForUser();
        }
    }
}

// ---------------------------------------------------------------
// 4. main() - the entry point of the program
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
