// EncryptTextFile.cpp
// This function encrypts a text file using a simple Caesar cipher shift.
// Every character (including spaces and newlines) is shifted by a secret key.

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

// These functions are defined in other folders.
string makeEncryptedFileName(string inputFileName);
int getSecretKey();
void clearInputLine();
void waitForUser();
void printHeader(string title);

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
