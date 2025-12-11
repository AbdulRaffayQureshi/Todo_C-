#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "../models/TodoItem.h"
#include "../models/PriorityQueue.h"
#include <string>
#include <vector>

class FileHandler {
private:
    std::string filename;
    
    // Helper methods for serialization - THESE WERE MISSING!
    std::string serializeTodo(const TodoItem& item);
    TodoItem deserializeTodo(const std::string& data);
    std::string getCurrentTimestamp();
    
public:
    FileHandler(const std::string& filename = "todos.dat");
    
    // Save and load operations
    bool saveToFile(const PriorityQueue& todos);
    bool loadFromFile(PriorityQueue& todos);
    
    // Backup and restore
    bool createBackup(const std::vector<TodoItem>& todos);
    bool restoreFromBackup();
    
    // Export to different formats
    bool exportToCSV(const std::vector<TodoItem>& todos);
    bool exportToJSON(const std::vector<TodoItem>& todos);
    
    // Statistics
    void showFileStats() const;
};

#endif // FILEHANDLER_H