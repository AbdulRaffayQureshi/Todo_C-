#include "TodoItem.h"
#include <sstream>
#include <iomanip>
#include <ctime>

TodoItem::TodoItem(int id, std::string title, std::string desc, 
                   std::string dueDate, Priority priority)
    : id(id), title(title), description(desc), dueDate(dueDate),
      priority(priority), status(Status::PENDING) {
    
    std::time_t now = std::time(nullptr);
    createdAt = now;
    updatedAt = now;
}

bool TodoItem::operator<(const TodoItem& other) const {
    // Higher priority comes first (URGENT > HIGH > MEDIUM > LOW)
    if (priority != other.priority) {
        return static_cast<int>(priority) > static_cast<int>(other.priority);
    }
    // If same priority, earlier due date comes first
    return dueDate < other.dueDate;
}

bool TodoItem::operator>(const TodoItem& other) const {
    return other < *this;
}

std::string TodoItem::priorityToString() const {
    switch (priority) {
        case Priority::LOW: return "Low";
        case Priority::MEDIUM: return "Medium";
        case Priority::HIGH: return "High";
        case Priority::URGENT: return "Urgent";
        default: return "Unknown";
    }
}

std::string TodoItem::statusToString() const {
    switch (status) {
        case Status::PENDING: return "Pending";
        case Status::IN_PROGRESS: return "In Progress";
        case Status::COMPLETED: return "Completed";
        default: return "Unknown";
    }
}

int TodoItem::daysRemaining() const {
    if (dueDate.empty()) return -1;
    
    std::tm due_tm = {};
    std::istringstream ss(dueDate);
    ss >> std::get_time(&due_tm, "%Y-%m-%d");
    
    if (ss.fail()) return -1;
    
    std::time_t due_time = std::mktime(&due_tm);
    std::time_t now = std::time(nullptr);
    
    double diff = std::difftime(due_time, now) / (60 * 60 * 24);
    return static_cast<int>(diff);
}