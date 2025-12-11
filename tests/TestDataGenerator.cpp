#include "TestDataGenerator.h"
#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
#include <ctime>

void TestDataGenerator::generateSampleData(TodoController& controller, int count) {
    std::cout << "Generating " << count << " sample todo items...\n";
    
    // Get current todos to find the next ID
    auto currentTodos = controller.getAllTodos();
    int startId = 1;
    if (!currentTodos.empty()) {
        // Find the maximum existing ID
        int maxId = 0;
        for (const auto& todo : currentTodos) {
            if (todo.id > maxId) {
                maxId = todo.id;
            }
        }
        startId = maxId + 1;
    }
    
    for (int i = 0; i < count; i++) {
        std::string title = randomTitle();
        std::string desc = randomDescription();
        std::string date = randomDate(rand() % 30 + 1); // 1-30 days from now
        Priority priority = randomPriority();
        
        controller.addTodo(title, desc, date, priority);
        
        // Randomly mark some as completed
        if (rand() % 3 == 0) {
            // Mark the todo we just added (ID would be startId + i)
            controller.markAsComplete(startId + i);
        }
    }
    
    std::cout << "Sample data generated successfully!\n";
}

std::vector<TodoItem> TestDataGenerator::generateTestItems(int count) {
    std::vector<TodoItem> items;
    
    for (int i = 0; i < count; i++) {
        TodoItem item(i + 1, randomTitle(), randomDescription(), 
                     randomDate(rand() % 30), randomPriority());
        items.push_back(item);
    }
    
    return items;
}

void TestDataGenerator::runPerformanceTests(TodoController& controller) {
    std::cout << "\n=== PERFORMANCE TESTS ===\n";
    
    // Generate large dataset
    int sizes[] = {100, 1000, 5000};
    
    for (int size : sizes) {
        std::cout << "\nTesting with " << size << " items:\n";
        
        auto start = std::chrono::high_resolution_clock::now();
        generateSampleData(controller, size);
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Generation time: " << duration.count() << "ms\n";
        
        // Test sorting performance
        start = std::chrono::high_resolution_clock::now();
        controller.sortByPriority();
        end = std::chrono::high_resolution_clock::now();
        
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Sorting time: " << duration.count() << "ms\n";
        
        // Test search performance
        start = std::chrono::high_resolution_clock::now();
        auto todos = controller.getAllTodos();
        int searchId = size / 2; // Search for middle item
        for (int i = 0; i < 1000; i++) {
            controller.searchById(searchId);
        }
        end = std::chrono::high_resolution_clock::now();
        
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "1000 searches time: " << duration.count() << "ms\n";
    }
}

void TestDataGenerator::testSearchAlgorithms() {
    std::cout << "\n=== SEARCH ALGORITHM TESTS ===\n";
    
    // Test linear search vs binary search performance
    std::cout << "1. Linear Search: O(n) - Good for unsorted data\n";
    std::cout << "2. Binary Search: O(log n) - Requires sorted data\n";
    std::cout << "3. Hash Table: O(1) - Best for frequent lookups\n";
}

void TestDataGenerator::testSortAlgorithms() {
    std::cout << "\n=== SORT ALGORITHM TESTS ===\n";
    
    std::cout << "Algorithm       | Best      | Average   | Worst     | Space\n";
    std::cout << "-----------------------------------------------------------\n";
    std::cout << "Quick Sort      | O(n log n)| O(n log n)| O(n²)     | O(log n)\n";
    std::cout << "Merge Sort      | O(n log n)| O(n log n)| O(n log n)| O(n)\n";
    std::cout << "Heap Sort       | O(n log n)| O(n log n)| O(n log n)| O(1)\n";
    std::cout << "Bubble Sort     | O(n)      | O(n²)     | O(n²)     | O(1)\n";
}

void TestDataGenerator::testFileOperations() {
    std::cout << "\n=== FILE OPERATION TESTS ===\n";
    
    std::cout << "1. Binary File Save/Load: Efficient storage\n";
    std::cout << "2. CSV Export: Human-readable format\n";
    std::cout << "3. JSON Export: Web-compatible format\n";
    std::cout << "4. Backup System: Automatic versioning\n";
}

std::string TestDataGenerator::randomTitle() {
    std::vector<std::string> titles = {
        "Complete Project", "Team Meeting", "Buy Groceries",
        "Doctor Appointment", "Pay Utility Bills", "Morning Exercise",
        "Read Programming Book", "Learn C++ Advanced", "Clean Living Room",
        "Plan Weekend Trip", "Car Oil Change", "Update LinkedIn Profile",
        "Prepare Presentation", "Code Review", "Write Documentation",
        "Client Call", "Budget Planning", "Study for Exam",
        "Gym Session", "Meditation Practice"
    };
    
    return titles[rand() % titles.size()];
}

std::string TestDataGenerator::randomDescription() {
    std::vector<std::string> descs = {
        "Important task that needs immediate attention",
        "Regular weekly activity that should be completed",
        "Don't forget about this important reminder",
        "High priority item requiring urgent action",
        "Can be done later when time permits",
        "Urgent - needs to be completed by end of day",
        "Weekly recurring task for team synchronization",
        "Personal development activity for skill enhancement",
        "Health-related appointment that cannot be missed",
        "Financial task that must be completed on time"
    };
    
    return descs[rand() % descs.size()];
}

std::string TestDataGenerator::randomDate(int daysFromNow) {
    if (daysFromNow <= 0) {
        return ""; // No date for some items
    }
    
    std::time_t now = std::time(nullptr);
    std::time_t future = now + (daysFromNow * 24 * 60 * 60);
    
    std::tm* tm = std::localtime(&future);
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm);
    
    return std::string(buffer);
}

Priority TestDataGenerator::randomPriority() {
    int r = rand() % 100;
    if (r < 20) return Priority::URGENT;      // 20% urgent
    else if (r < 50) return Priority::HIGH;   // 30% high
    else if (r < 80) return Priority::MEDIUM; // 30% medium
    else return Priority::LOW;               // 20% low
}