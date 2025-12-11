#ifndef TODOITEM_H
#define TODOITEM_H

#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

enum class Priority {
    LOW,
    MEDIUM,
    HIGH,
    URGENT
};

enum class Status {
    PENDING,
    IN_PROGRESS,
    COMPLETED
};

struct TodoItem {
    int id;
    std::string title;
    std::string description;
    std::string dueDate;
    Priority priority;
    Status status;
    std::time_t createdAt;
    std::time_t updatedAt;
    
    // Default constructor - ADD THIS
    TodoItem() : id(0), title(""), description(""), dueDate(""), 
                 priority(Priority::MEDIUM), status(Status::PENDING) {
        std::time_t now = std::time(nullptr);
        createdAt = now;
        updatedAt = now;
    }
    
    // Constructor with parameters
    TodoItem(int id, std::string title, std::string desc = "", 
             std::string dueDate = "", Priority priority = Priority::MEDIUM);
    
    // For priority queue comparison
    bool operator<(const TodoItem& other) const;
    bool operator>(const TodoItem& other) const;
    
    // Convert enums to strings
    std::string priorityToString() const;
    std::string statusToString() const;
    
    // Calculate time remaining
    int daysRemaining() const;
};

#endif // TODOITEM_H