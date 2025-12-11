#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "TodoItem.h"
#include <vector>

class PriorityQueue {
private:
    std::vector<TodoItem> heap;
    
    // Heap operations
    void heapifyUp(int index);
    void heapifyDown(int index);
    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }
    
public:
    PriorityQueue() = default;
    
    // Core operations
    void push(const TodoItem& item);
    TodoItem pop();
    TodoItem peek() const;
    bool isEmpty() const { return heap.empty(); }
    size_t size() const { return heap.size(); }
    
    // Search operations
    TodoItem* linearSearch(int id);
    TodoItem* binarySearch(int id); // Only works on sorted vector
    TodoItem* findByTitle(const std::string& title);
    
    // Sorting algorithms
    void quickSortByPriority();
    void mergeSortByDate();
    void bubbleSortByStatus();
    
    // Space optimization
    void compress(); // Remove completed items older than 30 days
    
private:
    // Quick sort helper
    void quickSort(int low, int high);
    int partition(int low, int high);
    
    // Merge sort helper
    void mergeSort(int left, int right);
    void merge(int left, int mid, int right);
};

#endif // PRIORITYQUEUE_H