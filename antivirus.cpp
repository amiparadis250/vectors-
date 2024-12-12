#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>

using namespace std;

string cleanPath(string path) {
   
    path.erase(remove(path.begin(), path.end(), '\"'), path.end());
    return path;
}

bool isValidPath(const string& path) {
  
    if (path.empty() || path.length() < 4) return false; 
    if (path.find_first_of("<>|?*") != string::npos) return false; 
    return true;
}

int main() {
    string filePath;
    cout << "Enter the complete file path to unhide (e.g., C:\\folder\\file.txt): ";
    getline(cin, filePath);

  
    filePath = cleanPath(filePath);

   
    if (!isValidPath(filePath)) {
        cout << "Error: Invalid file path format." << endl;
        return 1;
    }

    
    if (SetFileAttributes(filePath.c_str(), FILE_ATTRIBUTE_NORMAL) != 0) {
        cout << "File unhidden successfully: " << filePath << endl;
    } else {
        DWORD error = GetLastError();
        cout << "Failed to unhide the file. Error code: " << error << endl;

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