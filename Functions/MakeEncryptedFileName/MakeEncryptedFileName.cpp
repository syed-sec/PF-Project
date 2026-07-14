// MakeEncryptedFileName.cpp
// This function creates the encrypted file name from the original file name.

#include <string>
using namespace std;

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
