#include "hashtable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "maxheap.h"

using namespace std;

// constructor: Initialize the hash table with the given capacity.
HashTable::HashTable(int capacity)
    : capacity(capacity), collisions(0), unique_words(0), total_words(0), selected_hash_function(2)  {
    buckets = new LinkedList[capacity];
}


// destructor: Free the dynamically allocated memory for buckets.
HashTable::~HashTable() {
    delete[] buckets;      //delete the array of LinkedList.
}



//hash function: Generate hash code using the default hash functions
unsigned long HashTable::hashCode(string key) {
    unsigned long hash = 0;    //to store the hash value

    // switch between hash functions based on the value of selected_hash_function
    if (selected_hash_function == 1) {

        // 1. Summation Hash Code
        for (char c : key) {
            hash += c; // add ASCII value of each character
        }
    } else if (selected_hash_function == 2) {
        // 2. Polynomial Hash Code
        unsigned long prime = 31; // a small prime number
        
        for (char c : key) {
            hash = (hash * prime) + c; // polynomial accumulation
        }

    } else if (selected_hash_function == 3) {
        // 3. DJB2 Hash Code
        hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }


    } else if (selected_hash_function == 4) {

        // 4. SDBM Hash Code
        for (char c : key) {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }

    } else if (selected_hash_function == 5) {

        // 5. Cycle Shift Hash Code
        for (char c : key) {
            hash = (hash << 4) | (hash >> 28); // Rotate left by 4 bits
            hash += c;
        }
    } else if (selected_hash_function == 6) {

        // 6. Length-Based Hash Code
        hash = key.length();
        for (char c : key) {
            hash += c;           // Add ASCII values
        }
    }

    return hash % capacity; // modulo operation to ensure it fits within the hash table
}

// returns the number of collisions in the hash table

unsigned int HashTable::getCollisions() {
    return collisions;
}

//returns the number of unique words stored in the hash table
unsigned int HashTable::getUniqueWords() {
    return unique_words;
}

// returns the total number of words inserted into the hash table
unsigned int HashTable::getTotalWords() {
    return total_words;
}


//Select the hash function 
void HashTable::setHashFunction(int hashFunctionID) {
    if (hashFunctionID >= 1 && hashFunctionID <= 6) {
        selected_hash_function = hashFunctionID;
    } else {
        cerr << "Invalid hash function ID. Please select a value between 1 and 6." << endl;
    }
}


// imports words from a file and populates the hash table
void HashTable::import(string path) {
    ifstream file(path); // ppen the file
    if (!file.is_open()) {
        cerr << "Error: File not found or could not be opened." << endl;
        return;
    }

    string line, token;
    while (getline(file, line)) { // read the file line by line
        stringstream ss(line);   // tokenize the line by whitespace

        while (ss >> token) {    //extract each token
            string cleaned_word = token;


            // check if the token contains alphanumeric or special characters
            bool contains_alnum_or_special = false;
            for (char c : token) {
                if (isalnum(c) || ispunct(c)) {
                    contains_alnum_or_special = true;
                    break;
                }
            }

            if (!contains_alnum_or_special) {
                continue; // skip tokens with no valid content
            }

            // remove standard punctuation marks (not special characters) from the beginning or end
            int start = 0, end = token.size() - 1;
            while (start <= end && (token[start] == '.' || token[start] == ',' ||
                                    token[start] == '!' || token[start] == '?' ||
                                    token[start] == ';' || token[start] == '"' ||
                                    token[start] == '\'')) {
                start++;
            }
            while (end >= start && (token[end] == '.' || token[end] == ',' ||
                                    token[end] == '!' || token[end] == '?' ||
                                    token[end] == ';' || token[end] == '"' ||
                                    token[end] == '\'')) {
                end--;
            }

            cleaned_word = token.substr(start, end - start + 1);

            // normalize case for alphabetic content
            for (char &c : cleaned_word) {
                if (isalpha(c)) {
                    c = tolower(c);
                }
            }

            if (!cleaned_word.empty()) {
                insert(cleaned_word); // insert into the hash table
            }
        }
    }

    file.close(); // close the file

    // print the final counts
    cout << "Done!" << endl;
    cout << "The number of collisions is: " << collisions << endl;
    cout << "The number of unique words is: " << unique_words << endl;
    cout << "The total number of words is: " << total_words << endl;
}





// inserts a word into the hash table
void HashTable::insert(string word) {

    // compute the hash index
    unsigned long index = hashCode(word);
    LinkedList &bucket = buckets[index]; // access the appropriate bucket

    // check if the word already exists in the bucket
    Node* existingNode = bucket.find(word);
    if (existingNode) {

        // word already exists, increment frequency
        existingNode->setValue(existingNode->getValue() + 1);
    } else {
        // Word does nott exist, insert new node
        if (!bucket.empty()) {
            // Bucket is not empty, so this is a collision
            collisions++;
        }
        bucket.insert(word, 1); // insert the word with frequency of 1
        unique_words++;         // imcrement unique word count
    }
    total_words++; // increment total word count
}



// finds the frequency of a word in the hash table.
int HashTable::find_freq(string word) {
    // normalize the word by converting to lowercase
    for (char &c : word) {
        c = tolower(c);
    }

    // compute the hash index and search in the corresponding bucket
    unsigned long index = hashCode(word);
    Node* node = buckets[index].find(word);

    // if the word exists, return its frequency; otherwise, return 0
    return node ? node->getValue() : 0;
}


string HashTable::findMax() {
    MaxHeap heap; // create a max heap object.

    // iterate through all buckets in the hash table
    for (unsigned int i = 0; i < capacity; ++i) {
        Node* current = buckets[i].getHead(); // use getHead() to access the head
        while (current) {
            heap.insert(current->getKey(), current->getValue()); //use getKey() and getValue()
            current = current->getNext(); // use getNext() to move to the next node
        }
    }

    // if the heap is empty, return a default value
    if (heap.empty()) {
        return "No words found";
    }

    // return the word with the highest frequency
    return heap.getMax().first;
}
