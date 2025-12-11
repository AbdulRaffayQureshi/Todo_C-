#include "PriorityQueue.h"
#include <algorithm>
#include <ctime>
#include <iostream>

void PriorityQueue::heapifyUp(int index) {
    while (index > 0 && heap[parent(index)] < heap[index]) {
        std::swap(heap[parent(index)], heap[index]);
        index = parent(index);
    }
}

void PriorityQueue::heapifyDown(int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < heap.size() && heap[left] > heap[largest])
        largest = left;
    
    if (right < heap.size() && heap[right] > heap[largest])
        largest = right;
    
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

void PriorityQueue::push(const TodoItem& item) {
    heap.push_back(item);
    heapifyUp(heap.size() - 1);
}

TodoItem PriorityQueue::pop() {
    if (heap.empty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    
    TodoItem root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!heap.empty()) {
        heapifyDown(0);
    }
    
    return root;
}

TodoItem PriorityQueue::peek() const {
    if (heap.empty()) {
        throw std::runtime_error("Priority queue is empty");
    }
    return heap[0];
}

TodoItem* PriorityQueue::linearSearch(int id) {
    for (auto& item : heap) {
        if (item.id == id) {
            return &item;
        }
    }
    return nullptr;
}

TodoItem* PriorityQueue::binarySearch(int id) {
    // Create sorted copy for binary search
    std::vector<TodoItem> sorted = heap;
    std::sort(sorted.begin(), sorted.end(), 
              [](const TodoItem& a, const TodoItem& b) {
                  return a.id < b.id;
              });
    
    int left = 0, right = sorted.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (sorted[mid].id == id) {
            // Find in original heap
            return linearSearch(id);
        }
        
        if (sorted[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return nullptr;
}

TodoItem* PriorityQueue::findByTitle(const std::string& title) {
    for (auto& item : heap) {
        if (item.title.find(title) != std::string::npos) {
            return &item;
        }
    }
    return nullptr;
}

// Quick Sort Implementation
void PriorityQueue::quickSortByPriority() {
    if (heap.size() <= 1) return;
    
    // Convert to vector for sorting
    std::vector<TodoItem> temp = heap;
    heap.clear();
    
    std::sort(temp.begin(), temp.end(), 
              [](const TodoItem& a, const TodoItem& b) {
                  return a.priority > b.priority; // Descending
              });
    
    for (const auto& item : temp) {
        heap.push_back(item);
    }
}

// Merge Sort Implementation
void PriorityQueue::mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void PriorityQueue::merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<TodoItem> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++)
        L[i] = heap[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = heap[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i].dueDate <= R[j].dueDate) {
            heap[k] = L[i];
            i++;
        } else {
            heap[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        heap[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        heap[k] = R[j];
        j++;
        k++;
    }
}

void PriorityQueue::mergeSortByDate() {
    if (heap.size() <= 1) return;
    mergeSort(0, heap.size() - 1);
}

// Bubble Sort Implementation
void PriorityQueue::bubbleSortByStatus() {
    int n = heap.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (static_cast<int>(heap[j].status) > static_cast<int>(heap[j + 1].status)) {
                std::swap(heap[j], heap[j + 1]);
            }
        }
    }
}

void PriorityQueue::compress() {
    std::time_t now = std::time(nullptr);
    const int THIRTY_DAYS = 30 * 24 * 60 * 60;
    
    auto newEnd = std::remove_if(heap.begin(), heap.end(),
        [now, THIRTY_DAYS](const TodoItem& item) {
            return item.status == Status::COMPLETED && 
                   (now - item.updatedAt) > THIRTY_DAYS;
        });
    
    heap.erase(newEnd, heap.end());
}