#include "maxheap.h"
#include <utility>
using namespace std;

//constructor: Initialize an empty heap
MaxHeap::MaxHeap() {}

// restore heap property upwards from the given index
void MaxHeap::heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;         // get parent index
       
        if (heap[index].second > heap[parent].second) {
            swap(heap[index], heap[parent]); // swap with parent if necessary
            
            index = parent;                 // move up the tree
        } else {

            break;        // stop if heap property is satisfied
        }
    }
}

// restore heap property downwards from the given index
void MaxHeap::heapify_down(int index) {
    int size = heap.size(); // get heap size
    while (index < size) {
        int left = 2 * index + 1; //get left child index
        int right = 2 * index + 2; // gett right child index
        int largest = index; //assume current index is largest.


        if (left < size && heap[left].second > heap[largest].second) {
            largest = left; // update largest if left child is larger.
        }

        if (right < size && heap[right].second > heap[largest].second) {
            
            largest = right; // Update largest if right child is larger
        }
        if (largest != index) {
           
            swap(heap[index], heap[largest]); // swap with the largest child
            
            index = largest; // Move down the tree.
        } else {
            break; // stop if heap property is satisfied.
        }
    }
}

// inserts a word-frequency pair into the heap.

void MaxHeap::insert(string word, int frequency) {
    heap.push_back({word, frequency}); // Add the pair to the heap
    heapify_up(heap.size() - 1); // restore heap property upwards
}

// returns the word-frequency pair with the maximum frequency
pair<string, int> MaxHeap::getMax() {
    if (!heap.empty()) {
        return heap[0]; // return the root of the heap.
    }
    return {"", 0}; //return empty pair if the heap is empty
}

// removes the word-frequency pair with the maximum frequency.
void MaxHeap::removeMax() {
    if (!heap.empty()) {

        heap[0] = heap.back(); // replace root with the last element
        heap.pop_back(); // remove the last element

        heapify_down(0); //restore heap property downwards.
    }
}

// checks if the heap is empty
bool MaxHeap::empty() {
    return heap.empty();
}
