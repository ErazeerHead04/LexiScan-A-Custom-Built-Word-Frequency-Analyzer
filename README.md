
# LexiScan - A Custom-Built Word Frequency Analyzer

**LexiScan** is a C++ command-line application that analyzes text by counting total and unique words, tracking word frequency, and providing performance insights into custom-built hash functions. Built without STL containers, the project showcases a fully handcrafted hash table and linked list implementation using object-oriented principles.

## Features

- **Text Analytics**: Count total words, unique words, and track frequency of specific terms.
- **Custom Hash Table**: Uses separate chaining to handle collisions and track word entries.
- **Six Hash Functions**: Performance evaluated based on collision count to choose the most efficient.
- **Collision Tracking**: Built-in tools to monitor hash table performance.
- **Optional Max-Heap**: Bonus feature to find the most frequent word in O(1) time.
- **Robust Tokenization**: Ignores punctuation and normalizes case for accurate word analysis.
- **Manual Data Structures**: All hash tables, linked lists, and (optional) heaps are implemented from scratch—no STL.

## Supported Commands

- `import <path>` – Load a `.txt` file for analysis  
- `count_collisions` – Return number of hash collisions  
- `count_unique_words` – Return number of unique words  
- `count_words` – Return total number of words  
- `find_freq <word>` – Return frequency of a specific word  
- `find_max` – *(Bonus)* Return word with highest frequency in O(1) using a heap  
- `exit` – Exit the program  

## Technologies Used

- **Language**: C++
- **Core Concepts**:
  - Hash Tables (with separate chaining)
  - Linked Lists
  - Heaps (optional)
  - Object-Oriented Programming
- **No STL Containers**: All data structures are written manually for learning and performance benchmarking.

## File Structure

```
LexiScan/
├── linkedlist.h / linkedlist.cpp        # Custom singly linked list
├── hashtable.h / hashtable.cpp         # Hash table with separate chaining
├── maxheap.h / maxheap.cpp             # Optional: max-heap for O(1) frequency access
├── main.cpp                            # Command-line interface logic
├── makefile                            # Compilation instructions
├── report.pdf                          # Hash function documentation & performance analysis
```

## How to Run

1. Compile the project using the makefile:
   ```bash
   make
   ```

3. Follow the on-screen command prompts to interact with the text data.

> **Note**: Designed for Unix/Linux/macOS systems. Ensure the input text file path is correct.

## Hash Function Evaluation

- Six custom hash functions are implemented and compared based on:
  - Average collision count
  - Distribution across hash table buckets
- The most performant function (i.e., least collisions) is set as the default.
- All pseudocode, performance stats, and analysis are available in the accompanying `Documentation.pdf`.
