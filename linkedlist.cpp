#include "linkedlist.h"
#include <iostream>
#include <string>
using namespace std;

// node Constructor: Initializes a node with a key-value pair and sets next to nullptr
Node::Node(string key, int value) : key(key), value(value), next(nullptr) {}

//getter for the key of the node
string Node::getKey() { return key;}

// getter for the value of the node
int Node::getValue() { return value; }

// setter for updating the key of the node
void Node::setKey(string key) { this->key = key;}

// Setter for updating the value of the node
void Node::setValue(int value) { this->value = value; }

// getter for the next pointer of the node
Node* Node::getNext() { return next; }

//constructor for LinkedList: Initializes an empty linked list
LinkedList::LinkedList() : head(nullptr), size(0) {}

// destructor for LinkedList: Frees all the allocated nodes
LinkedList::~LinkedList() { clear(); }

// checks if the linked list is empty
bool LinkedList::empty() const { return head == nullptr;}

// returns the number of elements in the linked list
unsigned int LinkedList::getSize() const { return size; }

// Inserts a new key-value pair or updates value if the key exists
void LinkedList::insert(string key, int value) {

    Node* existing = find(key); // check if the key already exists
    if (existing) {
        existing->setValue(existing->getValue() + value); // update the value.
    } else {
        Node* newNode = new Node(key, value); // Create a new node

        newNode->next = head; // insert at the beginning of the list
        head = newNode; // Update the head pointer.
        size++; //increment the size of the list
    }
}

// finds a node by its key and returns the node, or nullptr if not found.
Node* LinkedList::find(string key) {
    Node* current = head;

    while (current) { //traverse the list
        if (current->getKey() == key) return current; // key found

        current = current->next; // move to the next node.
    }
    return nullptr; // Key not found
}


// Clears all nodes in the linked list.
void LinkedList::clear() {
    while (head) {             //while there are nodes in the list
        Node* temp = head;   // store the current node.
        head = head->next;    // Move the head pointer
        delete temp;          // freee the node
    }
    size = 0; // Reset the size of the list
}

// getter for the head of the linked list.
Node* LinkedList::getHead() { return head;}

