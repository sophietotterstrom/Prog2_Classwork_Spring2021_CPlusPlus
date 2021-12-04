//
//  main.cpp
//  2.6.1 text encryption
//
//  Created by Sophie Tötterström on 27.1.2021.
//

#include <iostream>
#include <string>
#include <cctype>
#include <bitset>
using namespace std;


int is_it_lower(string text) {

    char letter;
    int lenght = text.length();

    for (int i=0; i<lenght;i++) {
        letter = text[i];

        if (islower(letter) == 0) {
            cout << "Error! The encryption key must contain only lower case characters." << endl;
            return EXIT_FAILURE;
        }
    } return 0;
}


int is_it_letter(string key) {

    char letter;
    int length = key.length();

    for (int i=0; i<length; i++) {

        letter = key[i];

        if (isalpha(letter) == 0) {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            return EXIT_FAILURE;
        }
    } return 0;

}


int is_the_lenght_good(string key) {

    string::size_type lenght = 0;
    lenght = key.length();

    if (lenght != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    } else {
        return 0;
        }
}


bool does_it_have_all_alphabet_helper(string const &string) {

    std::bitset<26> alphabet;

    for (char character : string) {

        if (character >= 'A' && character <= 'Z')
            alphabet.set(character - 'A');

        else if (character >= 'a' && character <= 'z')
            alphabet.set(character - 'a');
    }
    return 26 == alphabet.count();
}


int does_it_have_all_aphabet(string key) {

    int number;
    number = does_it_have_all_alphabet_helper(key);

    if (number != 1) {
        cout << "Error! The encryption key must contain all alphabets a-z." << endl;
        return EXIT_FAILURE;
    } return 0;
}


int is_everything_good(string encryption_key) {

    if ((is_the_lenght_good(encryption_key) == 0) and (is_it_lower(encryption_key) == 0) and (is_it_letter(encryption_key) == 0) and (does_it_have_all_aphabet(encryption_key) == 0)) {
        return 0;
    } return EXIT_FAILURE;
}

string do_the_ecryption(string key, string old_word) {

    string alphabet;
    alphabet = "abcdefghijklmnopqrstuvwxyz";

    string new_word;

    for (char letter: old_word) {

        size_t found_index = alphabet.find(letter);

        string new_letter;
        new_letter = key[found_index];

        new_word.append(new_letter);
    }

    return new_word;
}

int main() {

    string encryption_key;
    cout << "Enter the encryption key: ";
    cin >> encryption_key;

    if (is_everything_good(encryption_key) == 0)  {
        string text_to_be_encrypted;
        cout << "Enter the text to be encrypted: ";
        cin >> text_to_be_encrypted;

        if (is_it_lower(text_to_be_encrypted) == 0) {
            string new_text;
            new_text = do_the_ecryption(encryption_key, text_to_be_encrypted);
            cout << "Encrypted text: " << new_text << endl;
        } else {
            return EXIT_FAILURE;
        }
    } else {
        return EXIT_FAILURE;
    }

}


