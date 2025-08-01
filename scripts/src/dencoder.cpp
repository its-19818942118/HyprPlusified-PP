#include <iostream>
#include <sstream>
#include <string>
#include <cctype>

using namespace std;

// Function to encode string to ASCII values
void encodeToASCII(const string& text) {
    cout << "Encoded ASCII: ";
    for (size_t i = 0; i < text.length(); ++i) {
        cout << int(text[i]);
        if (i != text.length() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

// Function to decode ASCII values to string
void decodeFromASCII(const string& asciiInput) {
    string cleanedInput;
    
    // Remove all commas and keep only digits and spaces
    for (char ch : asciiInput) {
        if (isdigit(ch) || isspace(ch)) {
            cleanedInput += ch;
        }
    }

    stringstream ss(cleanedInput);
    int code;
    cout << "Decoded Text: ";
    while (ss >> code) {
        cout << char(code);
    }
    cout << endl;
}

int main() {
    int choice;
    cout << "ASCII Encoder/Decoder\n";
    cout << "1. Encode Text to ASCII\n";
    cout << "2. Decode ASCII to Text\n";
    cout << "Choose an option (1 or 2): ";
    cin >> choice;
    cin.ignore(); // clear newline from input buffer

    if (choice == 1) {
        string text;
        cout << "Enter text to encode: ";
        getline(cin, text);
        encodeToASCII(text);
    } else if (choice == 2) {
        string asciiInput;
        cout << "Enter ASCII codes (separated by spaces and/or commas): ";
        getline(cin, asciiInput);
        decodeFromASCII(asciiInput);
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

// #include <iostream>

// int
//     main
//     ( )
// {
    
//     std::cout
//         <<  "What is your women Thinking???\n>>"
//     ;
    
//     std::string text;
//     std::cin >> text;
    
//     std::cout
//         <<  "Sounds like she is on her period"
//     ;
    
// }
