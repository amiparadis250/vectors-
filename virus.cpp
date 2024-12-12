#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <algorithm>

using namespace std;

const string HIDDEN_PATHS_FILE = "hiddenpaths.txt";

string cleanPath(string path) {
    // Remove quotes from the beginning and end if they exist
    path.erase(remove(path.begin(), path.end(), '\"'), path.end());
    return path;
}

bool isValidPath(const string& path) {
    // Basic path validation
    if (path.empty() || path.length() < 4) return false; // Path too short
    if (path.find_first_of("<>|?*") != string::npos) return false; // Invalid characters
    return true;
}

int main() {
    string filePath;
    cout << "Enter the complete file path (e.g., C:\\folder\\file.txt): ";
    getline(cin, filePath);

    filePath = cleanPath(filePath);

    // Validate the path
    if (!isValidPath(filePath)) {
        cout << "Error: Invalid file path format." << endl;
        return 1;
    }

    // Try to hide the file
    if (SetFileAttributes(filePath.c_str(), FILE_ATTRIBUTE_HIDDEN) != 0) {
        cout << "File hidden successfully: " << filePath << endl;
        
        // Prompt to save path
        char choice;
        cout << "Do you want to save this path to hidden paths file? (y/n): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        if (choice == 'y' || choice == 'Y') {
            // Append path to hidden paths file
            ofstream file(HIDDEN_PATHS_FILE, ios::app);
            if (file.is_open()) {
                file << filePath << endl;
                cout << "Path saved to hidden paths file." << endl;
                file.close();
            } else {
                cout << "Error: Could not save path to file." << endl;
            }
        }
    } else {
        DWORD error = GetLastError();
        cout << "Failed to hide the file. Error code: " << error << endl;

        switch(error) {
            case ERROR_FILE_NOT_FOUND:
                cout << "Error: The file was not found. Check the file path." << endl;
                break;
            case ERROR_ACCESS_DENIED:
                cout << "Error: Access denied. Try running the program as administrator." << endl;
                break;
            case ERROR_PATH_NOT_FOUND:
                cout << "Error: The specified path was not found." << endl;
                break;
            case ERROR_INVALID_NAME:
                cout << "Error: The specified file name is invalid." << endl;
                break;
            default:
                cout << "Error: An unknown error occurred." << endl;
        }
    }

    cout << "\nPress Enter to exit...";
    cin.get();
    return 0;
}