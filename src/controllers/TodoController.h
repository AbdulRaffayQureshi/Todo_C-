#ifndef TODOCONTROLLER_H
#define TODOCONTROLLER_H

#include "../models/TodoItem.h"
#include "../models/PriorityQueue.h"
#include "../utils/FileHandler.h"
#include <vector>
#include <string>

class TodoController {
private:
    static std::vector<TodoItem> todosStorage; // Changed to static
    FileHandler fileHandler;
    int nextId;
    
public:
    TodoController();
    
    // CRUD Operations
    void addTodo(const std::string& title, const std::string& description,
                const std::string& dueDate, Priority priority);
    bool updateTodo(int id, const std::string& title = "",
                   const std::string& description = "",
                   const std::string& dueDate = "",
                   Priority priority = Priority::MEDIUM,
                   Status status = Status::PENDING);
    bool deleteTodo(int id);
    
    // Status Management
    bool markAsComplete(int id);
    bool markAsInProgress(int id);
    
    // Search Operations
    TodoItem* searchById(int id);
    std::vector<TodoItem*> searchByTitle(const std::string& title);
    std::vector<TodoItem*> searchByPriority(Priority priority);
    std::vector<TodoItem*> searchByStatus(Status status);
    
    // Sorting
    void sortByPriority();
    void sortByDueDate();
    void sortByStatus();
    void sortById();
    
    // Statistics
    int getCompletedCount() const;
    int getPendingCount() const;
    int getInProgressCount() const;
    void showStatistics() const;
    
    // File Operations
    bool saveToFile();
    bool loadFromFile();
    bool createBackup();           // <-- ONLY ONE DECLARATION
    bool exportToCSV();            // <-- ONLY ONE DECLARATION
    bool exportToJSON();
    bool restoreFromBackup();
    void showFileStats() const;
    void compressOldItems();
    
    // Data Access
    std::vector<TodoItem> getAllTodos() const;
    void generateNextId();
};

#endif // TODOCONTROLLER_H