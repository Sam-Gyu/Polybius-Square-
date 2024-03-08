#include <string>
#include <sstream>
#include <iostream>
#include <cctype>

using namespace std;

const int rows= 5;
const int columns = 5;
char polybiusSquare[rows][columns];

void Polybius_Square(const int key[]) {
    int cell = 0;
    for (int i = 0; i < rows; ++i) {       // These loops iterate through each cell of the Polybius Square.
        for (int j = 0; j < columns; ++j) {
            polybiusSquare[i][j] = 'A' + cell;   // This line assigns a character to the current cell based on the value of
            if (polybiusSquare[i][j] == 'J') {
                polybiusSquare[i][j] = 'K';
                cell +=1;
            }
            ++cell;   // This increments the cell for the next iteration.
        }
    }
}

string Encryption (const string& text, const int key[]) {
    string encrypt_message = "";
    for (char ch : text) {
        ch = toupper(ch);
        if (ch == 'J') {        // If the character is 'J', replace it with 'I'
            ch = 'I';
        }
        if (isalpha(ch)) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    if (polybiusSquare[i][j] == ch) {  // If the current cell in the Polybius Square is equal to the character that the user input
                        string NumOfRow = to_string(key[i]);  // This will convert the values of key[i] into a string, key[i] represents the row index in the Polybius Square.
                        string NumOfColumn = to_string(key[j]);  // This will convert the values of key[j] into a string, key[j] represents the column index in the Polybius Square.
                        encrypt_message += NumOfRow + NumOfColumn ;  // Add the relevant key values to the message that is encrypted.
                    }
                }
            }
        } else {
            encrypt_message += " ";
        }
    }
    return encrypt_message;
}

string Decryption(const string& text, const int key[]) {
    string decrypt_message = "";

    for (size_t i = 0; i < text.length(); ++i) {
        if (isdigit(text[i])) {
            int row = static_cast<int>(text[i]) - static_cast<int>('0');    
            int column = static_cast<int>(text[i + 1]) - static_cast<int>('0');

            for (int i = 0; i < rows; ++i) {
                if (key[i] == row) {
                    for (int j = 0; j < columns; ++j) {
                        if (key[j] == column) {
                            char decrypted_char = polybiusSquare[i][j];
                            decrypt_message += decrypted_char;
                            break;
                        }
                    }
                    break;
                }
            }
            ++i; // Increment i by 1 to move to the next pair of digits
        } else {
            decrypt_message += ' ';
        }
    }


    return decrypt_message;
}


int main() {
    int key[5];
    cout << "Enter five numbers for the key from 1 to 5:" << '\n';
    for (int i = 0; i < 5; ++i) {
        cin >> key[i];
    }

    Polybius_Square(key);
    cin.ignore(); // To read all matrix
    string text;
    cout << "Enter the message: ";
    getline(cin, text);

    char choice;
    cout << "A) Encryption \nB) Decryption\n";
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 'A'){
        string encrypt_message = Encryption (text, key);
        cout << "Encrypted Message is: " << encrypt_message;
    }else{
        string decrypt_message = Decryption(text, key);
        cout << "Decrypted Message is: " << decrypt_message;
    }

    return 0;
}


















