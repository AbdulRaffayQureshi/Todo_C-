#include "SortSearch.h"
#include <algorithm>
#include <iostream>

// Linear Search - O(n)
int SortSearch::linearSearch(const std::vector<TodoItem>& items, int id) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].id == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Binary Search - O(log n) - requires sorted array
int SortSearch::binarySearch(const std::vector<TodoItem>& items, int id) {
    int left = 0;
    int right = static_cast<int>(items.size()) - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (items[mid].id == id) {
            return mid;
        }
        
        if (items[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

std::vector<int> SortSearch::searchByTitle(const std::vector<TodoItem>& items, const std::string& title) {
    std::vector<int> results;
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i].title.find(title) != std::string::npos) {
            results.push_back(static_cast<int>(i));
        }
    }
    return results;
}

// Quick Sort - O(n log n) average, O(n²) worst
void SortSearch::quickSort(std::vector<TodoItem>& items, int low, int high) {
    if (low < high) {
        int pi = partition(items, low, high);
        quickSort(items, low, pi - 1);
        quickSort(items, pi + 1, high);
    }
}

int SortSearch::partition(std::vector<TodoItem>& items, int low, int high) {
    TodoItem pivot = items[high];
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (compareByPriority(items[j], pivot)) {
            i++;
            std::swap(items[i], items[j]);
        }
    }
    std::swap(items[i + 1], items[high]);
    return i + 1;
}

// Merge Sort - O(n log n)
void SortSearch::mergeSort(std::vector<TodoItem>& items, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(items, left, mid);
        mergeSort(items, mid + 1, right);
        merge(items, left, mid, right);
    }
}

void SortSearch::merge(std::vector<TodoItem>& items, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<TodoItem> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = items[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = items[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (compareByDueDate(L[i], R[j])) {
            items[k] = L[i];
            i++;
        } else {
            items[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        items[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        items[k] = R[j];
        j++;
        k++;
    }
}

// Heap Sort - O(n log n)
void SortSearch::heapSort(std::vector<TodoItem>& items) {
    int n = static_cast<int>(items.size());
    
    // Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(items, n, i);
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        std::swap(items[0], items[i]);
        heapify(items, i, 0);
    }
}

void SortSearch::heapify(std::vector<TodoItem>& items, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && compareByPriority(items[left], items[largest]))
        largest = left;
    
    if (right < n && compareByPriority(items[right], items[largest]))
        largest = right;
    
    if (largest != i) {
        std::swap(items[i], items[largest]);
        heapify(items, n, largest);
    }
}

// Bubble Sort - O(n²)
void SortSearch::bubbleSort(std::vector<TodoItem>& items) {
    int n = static_cast<int>(items.size());
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (compareByStatus(items[j + 1], items[j])) {
                std::swap(items[j], items[j + 1]);
            }
        }
    }
}

// Comparison functions
bool SortSearch::compareById(const TodoItem& a, const TodoItem& b) {
    return a.id < b.id;
}

bool SortSearch::compareByPriority(const TodoItem& a, const TodoItem& b) {
    return static_cast<int>(a.priority) > static_cast<int>(b.priority);
}

bool SortSearch::compareByDueDate(const TodoItem& a, const TodoItem& b) {
    return a.dueDate < b.dueDate;
}

bool SortSearch::compareByStatus(const TodoItem& a, const TodoItem& b) {
    return static_cast<int>(a.status) < static_cast<int>(b.status);
}