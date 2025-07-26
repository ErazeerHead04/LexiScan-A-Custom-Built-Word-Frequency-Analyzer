#include <iostream>
#include <sstream>
#include "hashtable.h"

using namespace std;

void listCommands() {
    cout << "=================================================" << endl;
    cout << "Welcome to the Word Count Wizard!" << endl;
    cout << "List of available Commands:" << endl;
    cout << "import <path>       :Import a TXT file" << endl;
    cout << "count_collisions    :Print the number of collisions" << endl;
    cout << "count_unique_words  :Print the number of unique words" << endl;
    cout << "count_words         :Print the total number of words" << endl;
    cout << "find_freq <word>    :Search for a word and return its frequency" << endl;
    cout << "find_max            :Print the word with the highest frequency" << endl;
    cout << "exit                :Exit the program" << endl;
    cout << "=================================================" << endl << endl;
    cout << "Please provide the path to the TXT file you wish to analyze:" << endl;
}

int main() {
    HashTable myHashTable(438259); // A prime number that is bigger than (306,578 + 30%)
    listCommands();

    do {
        string user_input = "";
        string command = "";
        string parameter = "";
        try {
            cout << "> ";
            getline(cin, user_input);

            // Parse user-input into command and parameter(s)
            stringstream sstr(user_input);
            getline(sstr, command, ' ');
            getline(sstr, parameter);

            // Handle commands
            if (command == "import") {
                if (parameter.empty()) {
                    cout << "Error: No file path provided. Usage: import <path>" << endl;
                } else {
                    myHashTable.import(parameter);
                    
                }
            } else if (command == "count_collisions") {
                cout << "The number of collisions is: " << myHashTable.getCollisions() << endl;
            } else if (command == "count_unique_words") {
                cout << "The number of unique words is: " << myHashTable.getUniqueWords() << endl;
            } else if (command == "count_words") {
                cout << "The total number words is: " << myHashTable.getTotalWords() << endl;
            } else if (command == "find_freq") {
                if (parameter.empty()) {
                    cout << "Error: Please provide a word to search for. Usage: find_freq <word>" << endl;
                } else {
                    cout << "The frequency of the word \"" << parameter << "\" is: " << myHashTable.find_freq(parameter) << endl;
                }
            } else if (command == "find_max") {
                cout << "The word with the highest frequency is: " << myHashTable.findMax() << endl;
            } else if (command == "help") {
                listCommands();
            } else if (command == "exit") {
                break;
            } else {
                cout << "Invalid Command!" << endl;
            }
        } catch (exception &ex) {
            cout << "Error: " << ex.what() << endl;
        }
    } while (true);

    
    return EXIT_SUCCESS;
}
