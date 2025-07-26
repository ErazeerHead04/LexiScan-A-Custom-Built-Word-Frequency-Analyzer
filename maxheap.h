#ifndef _MAXHEAP_H
#define _MAXHEAP_H
#include <vector>
#include <string>
using namespace std;

// MaxHeap class to maintain a heap of word-frequency pairs.
class MaxHeap {
    private:
        vector<pair<string, int>> heap; // Array for heap storage.
        void heapify_up(int index);    // Restore heap property upwards.
        void heapify_down(int index); // Restore heap property downwards.

    public:
        MaxHeap();                     // Constructor.
        void insert(string word, int frequency); // Insert a word and its frequency.
        pair<string, int> getMax();    // Get the word with the maximum frequency.
        void removeMax();              // Remove the maximum frequency word.
        bool empty();                  // Check if the heap is empty.
};

#endif
