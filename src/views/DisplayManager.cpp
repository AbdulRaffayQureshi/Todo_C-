#include "DisplayManager.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <ctime>

// REMOVE THIS LINE: static std::vector<TodoItem> demoData;

DisplayManager::DisplayManager(TodoController& controller) 
    : controller(controller) {}

void DisplayManager::showMainMenu() {
    ColorManager::clearScreen();
    
    printHeader("TODO APPLICATION - MAIN MENU");
    
    std::cout << ColorManager::CYAN << "\n1. " << ColorManager::RESET << "Add New Todo\n";
    std::cout << ColorManager::CYAN << "2. " << ColorManager::RESET << "View All Todos\n";
    std::cout << ColorManager::CYAN << "3. " << ColorManager::RESET << "Search Todo\n";
    std::cout << ColorManager::CYAN << "4. " << ColorManager::RESET << "Update Todo\n";
    std::cout << ColorManager::CYAN << "5. " << ColorManager::RESET << "Mark as Complete\n";
    std::cout << ColorManager::CYAN << "6. " << ColorManager::RESET << "Sort Todos\n";
    std::cout << ColorManager::CYAN << "7. " << ColorManager::RESET << "Show Statistics\n";
    std::cout << ColorManager::CYAN << "8. " << ColorManager::RESET << "File Operations\n";
    std::cout << ColorManager::CYAN << "9. " << ColorManager::RESET << "DSA Algorithms Demo\n";
    std::cout << ColorManager::CYAN << "10. " << ColorManager::RESET << "Run Demo Mode\n";
    std::cout << ColorManager::CYAN << "0. " << ColorManager::RESET << "Exit\n";
    
    printFooter();
}

void DisplayManager::showAllTodos() {
    ColorManager::clearScreen();
    printHeader("ALL TODO ITEMS");
    
    // Get todos from CONTROLLER (includes demo + manual)
    auto todos = controller.getAllTodos();
    
    if (todos.empty()) {
        std::cout << ColorManager::YELLOW << "\nNo todos found. Add some todos first!\n" << ColorManager::RESET;
        std::cout << "Use Option 1 or Option 10 (Demo Mode) to add sample todos.\n";
    } else {
        printTodoTable(todos);
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void DisplayManager::showTodoDetails(int id) {
    // USE CONTROLLER to search
    TodoItem* todo = controller.searchById(id);
    
    if (todo != nullptr) {
        printTodoCard(*todo);
    } else {
        auto todos = controller.getAllTodos();
        std::cout << ColorManager::RED << "Todo not found! Available IDs: ";
        for (const auto& t : todos) {
            std::cout << t.id << " ";
        }
        std::cout << ColorManager::RESET << std::endl;
    }
}

void DisplayManager::showSearchResults(const std::vector<TodoItem*>& results) {
    if (results.empty()) {
        std::cout << ColorManager::YELLOW << "No results found!" << ColorManager::RESET << std::endl;
        return;
    }
    
    std::cout << ColorManager::GREEN << "\nFound " << results.size() << " result(s):\n" << ColorManager::RESET;
    std::cout << ColorManager::UNDERLINE << ColorManager::CYAN;
    std::cout << std::setw(5) << "ID" << " | "
              << std::setw(20) << "Title" << " | "
              << std::setw(12) << "Priority" << " | "
              << std::setw(12) << "Status" << ColorManager::RESET << std::endl;
    
    std::cout << std::string(55, '-') << std::endl;
    
    for (const auto& todo : results) {
        if (todo) {
            std::cout << std::setw(5) << todo->id << " | "
                      << std::setw(20) << (todo->title.length() > 20 ? todo->title.substr(0, 17) + "..." : todo->title) << " | "
                      << std::setw(12) << ColorManager::colorPriority(static_cast<int>(todo->priority)) << " | "
                      << std::setw(12) << ColorManager::colorStatus(todo->statusToString()) << std::endl;
        }
    }
}

void DisplayManager::showStatistics() {
    ColorManager::clearScreen();
    printHeader("STATISTICS");
    
    std::cout << ColorManager::CYAN << "\n=== Todo Statistics ===\n" << ColorManager::RESET;
    
    // Use controller's methods (includes demo + manual data)
    auto todos = controller.getAllTodos();
    int total = todos.size();
    int completed = controller.getCompletedCount();
    int pending = controller.getPendingCount();
    int inProgress = controller.getInProgressCount();
    
    std::cout << "Total Todos: " << total << std::endl;
    std::cout << "Completed: " << completed << std::endl;
    std::cout << "In Progress: " << inProgress << std::endl;
    std::cout << "Pending: " << pending << std::endl;
    
    if (total > 0) {
        int completionRate = (completed * 100) / total;
        std::cout << "\nCompletion Rate: ";
        ColorManager::printProgressBar(completionRate);
    }
    
    std::cout << ColorManager::CYAN << "\n=== Todo IDs Summary ===\n" << ColorManager::RESET;
    std::cout << "Available IDs: ";
    for (const auto& todo : todos) {
        std::cout << todo.id << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

int DisplayManager::getMenuChoice() {
    int choice;
    std::cout << ColorManager::GREEN << "\nEnter your choice (0-10): " << ColorManager::RESET;
    
    while (!(std::cin >> choice) || choice < 0 || choice > 10) {
        std::cout << ColorManager::RED << "Invalid input! Please enter a number between 0 and 10: " << ColorManager::RESET;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    clearInputBuffer();
    return choice;
}

std::string DisplayManager::getInput(const std::string& prompt) {
    std::string input;
    std::cout << ColorManager::YELLOW << prompt << ColorManager::RESET;
    std::getline(std::cin, input);
    return input;
}

int DisplayManager::getIntInput(const std::string& prompt) {
    int value;
    std::cout << ColorManager::YELLOW << prompt << ColorManager::RESET;
    
    while (!(std::cin >> value)) {
        std::cout << ColorManager::RED << "Invalid input! Please enter a number: " << ColorManager::RESET;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    clearInputBuffer();
    return value;
}

Priority DisplayManager::getPriorityInput() {
    std::cout << ColorManager::CYAN << "\nSelect Priority:\n" << ColorManager::RESET;
    std::cout << "1. " << ColorManager::GREEN << "Low\n" << ColorManager::RESET;
    std::cout << "2. " << ColorManager::YELLOW << "Medium\n" << ColorManager::RESET;
    std::cout << "3. " << ColorManager::MAGENTA << "High\n" << ColorManager::RESET;
    std::cout << "4. " << ColorManager::RED << "Urgent\n" << ColorManager::RESET;
    
    int choice = getIntInput("Enter choice (1-4): ");
    
    switch (choice) {
        case 1: return Priority::LOW;
        case 2: return Priority::MEDIUM;
        case 3: return Priority::HIGH;
        case 4: return Priority::URGENT;
        default: 
            std::cout << ColorManager::YELLOW << "Invalid choice, defaulting to Medium\n" << ColorManager::RESET;
            return Priority::MEDIUM;
    }
}

std::string DisplayManager::getDateInput() {
    std::string date;
    bool valid = false;
    
    while (!valid) {
        date = getInput("Enter due date (YYYY-MM-DD, or press Enter for no date): ");
        
        if (date.empty()) {
            return ""; // No date specified
        }
        
        // Basic validation for date format
        if (date.length() == 10 && date[4] == '-' && date[7] == '-') {
            // Check if it's a valid date
            try {
                int year = std::stoi(date.substr(0, 4));
                int month = std::stoi(date.substr(5, 2));
                int day = std::stoi(date.substr(8, 2));
                
                if (year >= 2024 && month >= 1 && month <= 12 && day >= 1 && day <= 31) {
                    valid = true;
                } else {
                    std::cout << ColorManager::RED << "Invalid date! Please enter a valid date.\n" << ColorManager::RESET;
                }
            } catch (...) {
                std::cout << ColorManager::RED << "Invalid date format!\n" << ColorManager::RESET;
            }
        } else {
            std::cout << ColorManager::RED << "Invalid format! Use YYYY-MM-DD format.\n" << ColorManager::RESET;
        }
    }
    
    return date;
}

void DisplayManager::printHeader(const std::string& title) {
    std::cout << ColorManager::MAGENTA << ColorManager::BOLD;
    std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
    std::cout << "║" << std::setw(50) << std::left << ("  " + title) << " ║\n";
    std::cout << "╚══════════════════════════════════════════════════════╝\n";
    std::cout << ColorManager::RESET;
}

void DisplayManager::printFooter() {
    std::cout << ColorManager::DIM << "\n══════════════════════════════════════════════════════\n" << ColorManager::RESET;
}

void DisplayManager::printTodoTable(const std::vector<TodoItem>& todos) {
    if (todos.empty()) {
        std::cout << ColorManager::YELLOW << "No todos to display.\n" << ColorManager::RESET;
        return;
    }
    
    std::cout << "\n" << ColorManager::UNDERLINE << ColorManager::CYAN;
    std::cout << std::setw(5) << "ID" << " | "
              << std::setw(25) << "Title" << " | "
              << std::setw(10) << "Priority" << " | "
              << std::setw(12) << "Status" << " | "
              << std::setw(12) << "Due Date" << ColorManager::RESET << std::endl;
    
    std::cout << std::string(72, '-') << std::endl;
    
    for (const auto& todo : todos) {
        std::cout << std::setw(5) << todo.id << " | "
                  << std::setw(25) << (todo.title.length() > 25 ? todo.title.substr(0, 22) + "..." : todo.title) << " | "
                  << std::setw(10) << ColorManager::colorPriority(static_cast<int>(todo.priority)) << " | "
                  << std::setw(12) << ColorManager::colorStatus(todo.statusToString()) << " | "
                  << std::setw(12) << (todo.dueDate.empty() ? "No date" : todo.dueDate) << std::endl;
    }
    
    std::cout << ColorManager::DIM << "\nTotal: " << todos.size() << " items" << ColorManager::RESET << std::endl;
    
    // Show available IDs clearly
    std::cout << ColorManager::CYAN << "\nAvailable IDs: ";
    for (const auto& todo : todos) {
        std::cout << todo.id << " ";
    }
    std::cout << ColorManager::RESET << std::endl;
}

void DisplayManager::printTodoCard(const TodoItem& todo) {
    std::cout << ColorManager::CYAN << ColorManager::BOLD << "\n╔═══════════════════════════════════════════════════╗\n";
    std::cout << "║                TODO DETAILS                 ║\n";
    std::cout << "╚═══════════════════════════════════════════════════╝\n" << ColorManager::RESET;
    
    std::cout << "\n" << ColorManager::BOLD << "ID: " << ColorManager::RESET << todo.id << std::endl;
    std::cout << ColorManager::BOLD << "Title: " << ColorManager::RESET << todo.title << std::endl;
    std::cout << ColorManager::BOLD << "Description: " << ColorManager::RESET << todo.description << std::endl;
    std::cout << ColorManager::BOLD << "Due Date: " << ColorManager::RESET << todo.dueDate;
    std::cout << " (" << ColorManager::colorDueDate(todo.daysRemaining()) << ")" << std::endl;
    std::cout << ColorManager::BOLD << "Priority: " << ColorManager::RESET 
              << ColorManager::colorPriority(static_cast<int>(todo.priority)) << std::endl;
    std::cout << ColorManager::BOLD << "Status: " << ColorManager::RESET 
              << ColorManager::colorStatus(todo.statusToString()) << std::endl;
}

void DisplayManager::runDemoMode() {
    ColorManager::clearScreen();
    printHeader("DEMO MODE - PRESENTATION READY");
    
    std::cout << ColorManager::GREEN << "\n📊 Loading demo todos...\n" << ColorManager::RESET;
    
    // Get current todos (demo data is already loaded in controller constructor)
    auto todos = controller.getAllTodos();
    
    std::cout << ColorManager::GREEN << "✅ Loaded " << todos.size() << " todos!\n" << ColorManager::RESET;
    
    std::cout << ColorManager::CYAN << "\n📋 TODO ID REFERENCE:\n" << ColorManager::RESET;
    for (const auto& todo : todos) {
        std::cout << todo.id << ". " << todo.title << " (" << todo.statusToString() << ")\n";
    }
    
    std::cout << ColorManager::YELLOW << "\n💡 TIP: Use these IDs for testing operations!\n" << ColorManager::RESET;
    std::cout << "• Try Option 4 with ID 2, 4, or 5 to update\n";
    std::cout << "• Try Option 5 with ID 2, 4, or 5 to mark as complete\n";
    std::cout << "• Try Option 3 with ID 1-5 to search\n";
    std::cout << "• Try Option 6 to sort todos\n";
    std::cout << "• Try Option 9 for DSA Algorithms Demo\n";
    
    std::cout << ColorManager::MAGENTA << "\n\nPress Enter to view all todos with their IDs..." << ColorManager::RESET;
    std::cin.get();
    
    // Now show the todos
    showAllTodos();
}

void DisplayManager::addNewTodo() {
    ColorManager::clearScreen();
    printHeader("ADD NEW TODO");
    
    // Get todo details
    std::string title = getInput("Enter title: ");
    if (title.empty()) {
        std::cout << ColorManager::RED << "Title cannot be empty!\n" << ColorManager::RESET;
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    
    std::string desc = getInput("Enter description: ");
    std::string date = getDateInput();
    
    // Get priority with menu
    std::cout << ColorManager::CYAN << "\nSelect Priority:\n" << ColorManager::RESET;
    std::cout << "1. " << ColorManager::GREEN << "Low\n" << ColorManager::RESET;
    std::cout << "2. " << ColorManager::YELLOW << "Medium\n" << ColorManager::RESET;
    std::cout << "3. " << ColorManager::MAGENTA << "High\n" << ColorManager::RESET;
    std::cout << "4. " << ColorManager::RED << "Urgent\n" << ColorManager::RESET;
    
    int priorityChoice = getIntInput("Enter choice (1-4): ");
    Priority priority;
    
    switch (priorityChoice) {
        case 1: priority = Priority::LOW; break;
        case 2: priority = Priority::MEDIUM; break;
        case 3: priority = Priority::HIGH; break;
        case 4: priority = Priority::URGENT; break;
        default: 
            std::cout << ColorManager::YELLOW << "Invalid choice, defaulting to Medium\n" << ColorManager::RESET;
            priority = Priority::MEDIUM;
    }
    
    // Add the todo THROUGH CONTROLLER (will be added to existing data)
    controller.addTodo(title, desc, date, priority);
    
    // Show confirmation
    auto todos = controller.getAllTodos();
    
    std::cout << ColorManager::GREEN << "\n✅ Todo added successfully!\n" << ColorManager::RESET;
    std::cout << "ID: " << (todos.empty() ? 1 : todos.back().id) << "\n";
    std::cout << "Title: " << title << "\n";
    std::cout << "Priority: " << ColorManager::colorPriority(static_cast<int>(priority)) << "\n";
    std::cout << "Status: " << ColorManager::colorStatus("Pending") << "\n";
    if (!date.empty()) {
        std::cout << "Due Date: " << date << "\n";
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void DisplayManager::showAlgorithmsDemo() {
    ColorManager::clearScreen();
    printHeader("DSA ALGORITHMS DEMONSTRATION");
    
    std::cout << ColorManager::GREEN << "\n=== SEARCHING ALGORITHMS ===\n" << ColorManager::RESET;
    
    std::cout << "\n" << ColorManager::CYAN << "1. Linear Search (O(n)):\n" << ColorManager::RESET;
    std::cout << "   - Time Complexity: O(n)\n";
    std::cout << "   - Space Complexity: O(1)\n";
    std::cout << "   - Best for: Small datasets, unsorted data\n";
    std::cout << "   - Implementation: Iterates through each element\n";
    
    std::cout << "\n" << ColorManager::CYAN << "2. Binary Search (O(log n)):\n" << ColorManager::RESET;
    std::cout << "   - Time Complexity: O(log n)\n";
    std::cout << "   - Space Complexity: O(1) iterative, O(log n) recursive\n";
    std::cout << "   - Best for: Large sorted datasets\n";
    std::cout << "   - Implementation: Divides search space in half\n";
    
    std::cout << ColorManager::GREEN << "\n=== SORTING ALGORITHMS ===\n" << ColorManager::RESET;
    
    std::cout << "\n" << ColorManager::CYAN << "1. Quick Sort (O(n log n) average):\n" << ColorManager::RESET;
    std::cout << "   - Best/Average Case: O(n log n)\n";
    std::cout << "   - Worst Case: O(n²)\n";
    std::cout << "   - Space: O(log n)\n";
    std::cout << "   - Used for: Sorting by priority\n";
    std::cout << "   - Type: Divide and conquer, in-place\n";
    
    std::cout << "\n" << ColorManager::CYAN << "2. Merge Sort (O(n log n)):\n" << ColorManager::RESET;
    std::cout << "   - Time Complexity: O(n log n) always\n";
    std::cout << "   - Space Complexity: O(n)\n";
    std::cout << "   - Used for: Sorting by due date\n";
    std::cout << "   - Type: Stable, not in-place\n";
    
    std::cout << "\n" << ColorManager::CYAN << "3. Heap Sort (O(n log n)):\n" << ColorManager::RESET;
    std::cout << "   - Time Complexity: O(n log n)\n";
    std::cout << "   - Space Complexity: O(1)\n";
    std::cout << "   - Used in: Priority queue implementation\n";
    std::cout << "   - Type: In-place, not stable\n";
    
    std::cout << "\n" << ColorManager::CYAN << "4. Bubble Sort (O(n²)):\n" << ColorManager::RESET;
    std::cout << "   - Time Complexity: O(n²)\n";
    std::cout << "   - Space Complexity: O(1)\n";
    std::cout << "   - Used for: Educational purposes, small datasets\n";
    std::cout << "   - Type: Simple, stable, in-place\n";
    
    std::cout << ColorManager::GREEN << "\n=== DATA STRUCTURES USED ===\n" << ColorManager::RESET;
    std::cout << "1. " << ColorManager::YELLOW << "Priority Queue (Binary Heap):\n" << ColorManager::RESET;
    std::cout << "   - Insertion: O(log n)\n";
    std::cout << "   - Extraction: O(log n)\n";
    std::cout << "   - Peek: O(1)\n";
    
    std::cout << "\n2. " << ColorManager::YELLOW << "Vector/Array:\n" << ColorManager::RESET;
    std::cout << "   - Random Access: O(1)\n";
    std::cout << "   - Insertion at end: O(1) amortized\n";
    std::cout << "   - Insertion at middle: O(n)\n";
    
    std::cout << ColorManager::GREEN << "\n=== SPACE OPTIMIZATION ===\n" << ColorManager::RESET;
    std::cout << "1. Automatic compression of completed items >30 days old\n";
    std::cout << "2. Binary file storage for efficient persistence\n";
    std::cout << "3. In-place sorting algorithms where possible\n";
    
    // Performance comparison table
    std::cout << ColorManager::MAGENTA << "\n\n=== PERFORMANCE COMPARISON ===\n" << ColorManager::RESET;
    std::cout << std::left << std::setw(20) << "Algorithm" 
              << std::setw(15) << "Best Case" 
              << std::setw(15) << "Average" 
              << std::setw(15) << "Worst Case" 
              << std::setw(15) << "Space" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    std::cout << std::setw(20) << "Linear Search" 
              << std::setw(15) << "O(1)" 
              << std::setw(15) << "O(n)" 
              << std::setw(15) << "O(n)" 
              << std::setw(15) << "O(1)" << std::endl;
    
    std::cout << std::setw(20) << "Binary Search" 
              << std::setw(15) << "O(1)" 
              << std::setw(15) << "O(log n)" 
              << std::setw(15) << "O(log n)" 
              << std::setw(15) << "O(1)" << std::endl;
    
    std::cout << std::setw(20) << "Quick Sort" 
              << std::setw(15) << "O(n log n)" 
              << std::setw(15) << "O(n log n)" 
              << std::setw(15) << "O(n²)" 
              << std::setw(15) << "O(log n)" << std::endl;
    
    std::cout << std::setw(20) << "Merge Sort" 
              << std::setw(15) << "O(n log n)" 
              << std::setw(15) << "O(n log n)" 
              << std::setw(15) << "O(n log n)" 
              << std::setw(15) << "O(n)" << std::endl;
    
    std::cout << std::setw(20) << "Heap Sort" 
              << std::setw(15) << "O(n log n)" 
              << std::setw(15) << "O(n log n)" 
              << std::setw(15) << "O(n log n)" 
              << std::setw(15) << "O(1)" << std::endl;
    
    std::cout << std::setw(20) << "Bubble Sort" 
              << std::setw(15) << "O(n)" 
              << std::setw(15) << "O(n²)" 
              << std::setw(15) << "O(n²)" 
              << std::setw(15) << "O(1)" << std::endl;
}

void DisplayManager::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}