// DecryptTextFile.cpp
// This function decrypts a text file that was encrypted with encryptTextFile().

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

// These functions are defined in other folders.
string makeDecryptedFileName(string inputFileName);
int getSecretKey();
void clearInputLine();
void waitForUser();
void printHeader(string title);

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
