// MakeDecryptedFileName.cpp
// This function creates the decrypted file name from the encrypted file name.

#include <string>
using namespace std;

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
