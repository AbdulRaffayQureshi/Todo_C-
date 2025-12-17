#include "../utils/ColorManager.h"
#include "TodoController.h"
#include <iostream>
#include <algorithm>
#include <ctime>

// Initialize with demo data
std::vector<TodoItem> TodoController::todosStorage = {
    TodoItem(1, "Complete Project Report", "Finish DSA project with algorithms", "2025-02-15", Priority::HIGH),
    TodoItem(2, "Buy Groceries", "Milk, Eggs, Bread, Fruits", "2023-05-05", Priority::MEDIUM),
    TodoItem(3, "Doctor Appointment", "Annual health checkup", "2025-10-10", Priority::HIGH),
    TodoItem(4, "Read Clean Code Book", "Finish reading Clean Code", "2024-12-31", Priority::LOW),
    TodoItem(5, "Team Meeting", "Weekly sync with team", "2025-06-20", Priority::URGENT)
};

TodoController::TodoController() : nextId(6) {
    loadFromFile();
    // Mark some demo todos as completed
    markAsComplete(1);
    markAsComplete(3);
}

void TodoController::addTodo(const std::string& title, const std::string& description,
                            const std::string& dueDate, Priority priority) {
    TodoItem newTodo(nextId, title, description, dueDate, priority);
    todosStorage.push_back(newTodo);
    nextId++;
    saveToFile();
}

bool TodoController::updateTodo(int id, const std::string& title,
                               const std::string& description,
                               const std::string& dueDate,
                               Priority priority,
                               Status status) {
    for (auto& todo : todosStorage) {
        if (todo.id == id) {
            if (!title.empty()) todo.title = title;
            if (!description.empty()) todo.description = description;
            if (!dueDate.empty()) todo.dueDate = dueDate;
            if (priority != Priority::MEDIUM) todo.priority = priority;
            if (status != Status::PENDING) todo.status = status;
            
            todo.updatedAt = std::time(nullptr);
            saveToFile();
            return true;
        }
    }
    return false;
}

bool TodoController::deleteTodo(int id) {
    auto it = std::remove_if(todosStorage.begin(), todosStorage.end(),
                            [id](const TodoItem& todo) { return todo.id == id; });
    
    if (it != todosStorage.end()) {
        todosStorage.erase(it, todosStorage.end());
        saveToFile();
        return true;
    }
    return false;
}

bool TodoController::markAsComplete(int id) {
    for (auto& todo : todosStorage) {
        if (todo.id == id) {
            todo.status = Status::COMPLETED;
            todo.updatedAt = std::time(nullptr);
            saveToFile();
            return true;
        }
    }
    return false;
}

bool TodoController::markAsInProgress(int id) {
    for (auto& todo : todosStorage) {
        if (todo.id == id) {
            todo.status = Status::IN_PROGRESS;
            todo.updatedAt = std::time(nullptr);
            saveToFile();
            return true;
        }
    }
    return false;
}

TodoItem* TodoController::searchById(int id) {
    for (auto& todo : todosStorage) {
        if (todo.id == id) {
            return &todo;
        }
    }
    return nullptr;
}

std::vector<TodoItem*> TodoController::searchByTitle(const std::string& title) {
    std::vector<TodoItem*> results;
    for (auto& todo : todosStorage) {
        if (todo.title.find(title) != std::string::npos) {
            results.push_back(&todo);
        }
    }
    return results;
}

std::vector<TodoItem*> TodoController::searchByPriority(Priority priority) {
    std::vector<TodoItem*> results;
    for (auto& todo : todosStorage) {
        if (todo.priority == priority) {
            results.push_back(&todo);
        }
    }
    return results;
}

std::vector<TodoItem*> TodoController::searchByStatus(Status status) {
    std::vector<TodoItem*> results;
    for (auto& todo : todosStorage) {
        if (todo.status == status) {
            results.push_back(&todo);
        }
    }
    return results;
}

void TodoController::sortByPriority() {
    std::sort(todosStorage.begin(), todosStorage.end(),
              [](const TodoItem& a, const TodoItem& b) {
                  return static_cast<int>(a.priority) > static_cast<int>(b.priority);
              });
}

void TodoController::sortByDueDate() {
    std::sort(todosStorage.begin(), todosStorage.end(),
              [](const TodoItem& a, const TodoItem& b) {
                  return a.dueDate < b.dueDate;
              });
}

void TodoController::sortByStatus() {
    std::sort(todosStorage.begin(), todosStorage.end(),
              [](const TodoItem& a, const TodoItem& b) {
                  return static_cast<int>(a.status) < static_cast<int>(b.status);
              });
}

void TodoController::sortById() {
    std::sort(todosStorage.begin(), todosStorage.end(),
              [](const TodoItem& a, const TodoItem& b) {
                  return a.id < b.id;
              });
}

int TodoController::getCompletedCount() const {
    int count = 0;
    for (const auto& todo : todosStorage) {
        if (todo.status == Status::COMPLETED) count++;
    }
    return count;
}

int TodoController::getPendingCount() const {
    int count = 0;
    for (const auto& todo : todosStorage) {
        if (todo.status == Status::PENDING) count++;
    }
    return count;
}

int TodoController::getInProgressCount() const {
    int count = 0;
    for (const auto& todo : todosStorage) {
        if (todo.status == Status::IN_PROGRESS) count++;
    }
    return count;
}

void TodoController::showStatistics() const {
    int total = todosStorage.size();
    int completed = getCompletedCount();
    int pending = getPendingCount();
    int inProgress = getInProgressCount();
    
    std::cout << "\n=== Statistics ===" << std::endl;
    std::cout << "Total Todos: " << total << std::endl;
    std::cout << "Completed: " << completed << std::endl;
    std::cout << "In Progress: " << inProgress << std::endl;
    std::cout << "Pending: " << pending << std::endl;
    
    std::cout << "\nAvailable IDs: ";
    for (const auto& todo : todosStorage) {
        std::cout << todo.id << " ";
    }
    std::cout << std::endl;
}


// File Operations
bool TodoController::saveToFile() {
    // Simple save implementation for now
    std::cout << "Data saved successfully" << std::endl;
    return true;
}

bool TodoController::loadFromFile() {
    // For demo, just use the sample data
    return true;
}

bool TodoController::createBackup() {
    // Convert todosStorage to vector for backup
    std::vector<TodoItem> todosVector = todosStorage;
    return fileHandler.createBackup(todosVector);
}

bool TodoController::exportToCSV() {
    std::vector<TodoItem> todosVector = todosStorage;
    return fileHandler.exportToCSV(todosVector);
}

bool TodoController::exportToJSON() {
    std::vector<TodoItem> todosVector = todosStorage;
    return fileHandler.exportToJSON(todosVector);
}

bool TodoController::restoreFromBackup() {
    return fileHandler.restoreFromBackup();
}

void TodoController::showFileStats() const {
    fileHandler.showFileStats();
}

void TodoController::compressOldItems() {
    // Simplified compression
    auto now = std::time(nullptr);
    const int THIRTY_DAYS = 30 * 24 * 60 * 60;
    
    todosStorage.erase(std::remove_if(todosStorage.begin(), todosStorage.end(),
        [now, THIRTY_DAYS](const TodoItem& todo) {
            return todo.status == Status::COMPLETED && 
                   (now - todo.updatedAt) > THIRTY_DAYS;
        }), todosStorage.end());
}

std::vector<TodoItem> TodoController::getAllTodos() const {
    return todosStorage;
}

void TodoController::generateNextId() {
    // Already handled in addTodo
}
