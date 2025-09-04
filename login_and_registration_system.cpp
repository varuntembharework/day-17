#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Function Prototypes
void registerUser();
void loginUser();
bool userExists(const string &username);
bool validateUser(const string &username, const string &password);
void clearScreen();

int main() {
    int choice;

    while (true) {
        cout << "\n=====================================\n";
        cout << "      LOGIN & REGISTRATION SYSTEM     \n";
        cout << "=====================================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        // Handle wrong input type (non-numeric)
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            clearScreen();
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                clearScreen();
                registerUser();
                break;
            case 2:
                clearScreen();
                loginUser();
                break;
            case 3:
                cout << "Exiting... Goodbye!\n";
                return 0;
            default:
                clearScreen();
                cout << "Invalid option! Please try again.\n";
        }
    }
    return 0;
}

// Function to clear screen (works for Windows & Linux)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Check if a username already exists in users.txt
bool userExists(const string &username) {
    ifstream infile("users.txt");
    string u, p;

    while (infile >> u >> p) {
        if (u == username) {
            return true;
        }
    }
    return false;
}

// Validate username & password
bool validateUser(const string &username, const string &password) {
    ifstream infile("users.txt");  // fixed filename
    string u, p;
    
    while (infile >> u >> p) {
        if (u == username && p == password) {
            return true;
        }
    }
    return false;
}

// Register new user
void registerUser() {
    string username, password;

    cout << "\n--- User Registration ---\n";
    cout << "Enter a username: ";
    cin >> username;

    if (userExists(username)) {
        cout << "Username already exists! Try a different one.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    ofstream outfile("users.txt", ios::app);
    outfile << username << " " << password << endl;

    cout << "Registration successful! You can now login.\n";
}

// Login user
void loginUser() {
    string username, password;

    cout << "\n--- User Login ---\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (validateUser(username, password)) {
        cout << "Login successful! Welcome, " << username << ".\n";
    } else {
        cout << "Invalid credentials! Please try again.\n";
    }
}