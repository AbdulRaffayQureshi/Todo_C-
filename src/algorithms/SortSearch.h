#ifndef SORTSEARCH_H
#define SORTSEARCH_H

#include <vector>
#include "../models/TodoItem.h"

class SortSearch {
public:
    // Searching algorithms
    static int linearSearch(const std::vector<TodoItem>& items, int id);
    static int binarySearch(const std::vector<TodoItem>& items, int id);
    static std::vector<int> searchByTitle(const std::vector<TodoItem>& items, const std::string& title);
    
    // Sorting algorithms
    static void quickSort(std::vector<TodoItem>& items, int low, int high);
    static void mergeSort(std::vector<TodoItem>& items, int left, int right);
    static void heapSort(std::vector<TodoItem>& items);
    static void bubbleSort(std::vector<TodoItem>& items);
    
    // Utility functions
    static int partition(std::vector<TodoItem>& items, int low, int high);
    static void merge(std::vector<TodoItem>& items, int left, int mid, int right);
    static void heapify(std::vector<TodoItem>& items, int n, int i);
    
    // Comparison functions for different criteria
    static bool compareById(const TodoItem& a, const TodoItem& b);
    static bool compareByPriority(const TodoItem& a, const TodoItem& b);
    static bool compareByDueDate(const TodoItem& a, const TodoItem& b);
    static bool compareByStatus(const TodoItem& a, const TodoItem& b);
};

#endif // SORTSEARCH_H