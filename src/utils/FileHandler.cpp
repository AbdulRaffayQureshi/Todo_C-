#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <sys/stat.h>
#include <vector>

FileHandler::FileHandler(const std::string& filename) : filename(filename) {}

bool FileHandler::saveToFile(const PriorityQueue& todos) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
        return false;
    }
    
    // Write header with version and timestamp
    std::time_t now = std::time(nullptr);
    file << "TODO_DATA_V1.0|" << now << "\n";
    
    // Convert priority queue to vector for saving
    std::vector<TodoItem> itemsToSave;
    PriorityQueue tempQueue = todos; // Create copy
    
    while (!tempQueue.isEmpty()) {
        itemsToSave.push_back(tempQueue.pop());
    }
    
    // Save count
    size_t count = itemsToSave.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    // Save each todo
    for (const auto& item : itemsToSave) {
        std::string serialized = serializeTodo(item);
        size_t length = serialized.length();
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(serialized.c_str(), length);
    }
    
    file.close();
    std::cout << "✅ Saved " << count << " todos to " << filename << std::endl;
    return true;
}

bool FileHandler::loadFromFile(PriorityQueue& todos) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "📝 No existing data found. Starting fresh." << std::endl;
        return false;
    }
    
    // Read header
    std::string header;
    std::getline(file, header);
    
    if (header.find("TODO_DATA_V1.0") == std::string::npos) {
        std::cout << "⚠️  Invalid file format." << std::endl;
        return false;
    }
    
    // Read count
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    std::cout << "📥 Loading " << count << " todos from " << filename << "..." << std::endl;
    
    for (size_t i = 0; i < count; i++) {
        // Read length
        size_t length;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        
        // Read data
        char* buffer = new char[length + 1];
        file.read(buffer, length);
        buffer[length] = '\0';
        
        std::string serialized(buffer);
        delete[] buffer;
        
        // Deserialize and add to queue
        TodoItem item = deserializeTodo(serialized);
        todos.push(item);
    }
    
    file.close();
    std::cout << "✅ Loaded " << count << " todos successfully." << std::endl;
    return true;
}

bool FileHandler::createBackup(const std::vector<TodoItem>& todos) {
    try {
        std::string timestamp = getCurrentTimestamp();
        std::string backupFilename = "backup/todo_backup_" + timestamp + ".dat";
        
        // Create backup directory if it doesn't exist
        #ifdef _WIN32
        system("mkdir backup 2>nul");
        #else
        system("mkdir -p backup 2>/dev/null");
        #endif
        
        std::ofstream backupFile(backupFilename, std::ios::binary);
        if (!backupFile.is_open()) {
            std::cerr << "❌ Could not create backup file: " << backupFilename << std::endl;
            return false;
        }
        
        // Write backup header
        backupFile << "TODO_BACKUP_V1.0|" << std::time(nullptr) << "\n";
        
        // Save count
        size_t count = todos.size();
        backupFile.write(reinterpret_cast<const char*>(&count), sizeof(count));
        
        // Save each todo
        for (const auto& item : todos) {
            std::string serialized = serializeTodo(item);
            size_t length = serialized.length();
            backupFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
            backupFile.write(serialized.c_str(), length);
        }
        
        backupFile.close();
        
        // Also create a CSV backup
        exportToCSV(todos);
        
        std::cout << "✅ Backup created: " << backupFilename << std::endl;
        std::cout << "📊 Backed up " << count << " todos" << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Backup failed: " << e.what() << std::endl;
        return false;
    }
}

bool FileHandler::restoreFromBackup() {
    // List available backups
    std::cout << "Available backups:" << std::endl;
    
    #ifdef _WIN32
    system("dir backup\\*.dat /b 2>nul");
    #else
    system("ls backup/*.dat 2>/dev/null");
    #endif
    
    std::string backupFile;
    std::cout << "\nEnter backup filename (or press Enter to cancel): ";
    std::getline(std::cin, backupFile);
    
    if (backupFile.empty()) {
        std::cout << "Restore cancelled." << std::endl;
        return false;
    }
    
    // Add backup/ prefix if not present
    if (backupFile.find("backup/") == std::string::npos && 
        backupFile.find("backup\\") == std::string::npos) {
        backupFile = "backup/" + backupFile;
    }
    
    std::ifstream file(backupFile, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "❌ Could not open backup file: " << backupFile << std::endl;
        return false;
    }
    
    // Read backup header
    std::string header;
    std::getline(file, header);
    
    if (header.find("TODO_BACKUP_V1.0") == std::string::npos) {
        std::cout << "⚠️  Invalid backup format." << std::endl;
        return false;
    }
    
    // Extract backup timestamp
    size_t pipePos = header.find('|');
    if (pipePos != std::string::npos) {
        std::string timestampStr = header.substr(pipePos + 1);
        std::time_t backupTime = std::stol(timestampStr);
        std::cout << "Backup created: " << std::ctime(&backupTime);
    }
    
    // Read count
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    std::cout << "📥 Restoring " << count << " todos..." << std::endl;
    
    // Create priority queue to return
    PriorityQueue restoredQueue;
    
    for (size_t i = 0; i < count; i++) {
        // Read length
        size_t length;
        file.read(reinterpret_cast<char*>(&length), sizeof(length));
        
        // Read data
        char* buffer = new char[length + 1];
        file.read(buffer, length);
        buffer[length] = '\0';
        
        std::string serialized(buffer);
        delete[] buffer;
        
        // Deserialize and add to queue
        TodoItem item = deserializeTodo(serialized);
        restoredQueue.push(item);
    }
    
    file.close();
    
    // Save restored data to main file
    if (saveToFile(restoredQueue)) {
        std::cout << "✅ Restore completed successfully!" << std::endl;
        return true;
    }
    
    return false;
}

bool FileHandler::exportToCSV(const std::vector<TodoItem>& todos) {
    std::string timestamp = getCurrentTimestamp();
    std::string csvFilename = "exports/todos_export_" + timestamp + ".csv";
    
    // Create exports directory if it doesn't exist
    #ifdef _WIN32
    system("mkdir exports 2>nul");
    #else
    system("mkdir -p exports 2>/dev/null");
    #endif
    
    std::ofstream csvFile(csvFilename);
    if (!csvFile.is_open()) {
        std::cerr << "❌ Could not create CSV file: " << csvFilename << std::endl;
        return false;
    }
    
    // Write CSV header
    csvFile << "ID,Title,Description,Due Date,Priority,Status,Created At,Updated At\n";
    
    // Write each todo
    for (const auto& item : todos) {
        csvFile << item.id << ","
                << "\"" << item.title << "\","
                << "\"" << item.description << "\","
                << item.dueDate << ","
                << item.priorityToString() << ","
                << item.statusToString() << ","
                << item.createdAt << ","
                << item.updatedAt << "\n";
    }
    
    csvFile.close();
    std::cout << "✅ CSV exported: " << csvFilename << std::endl;
    return true;
}

bool FileHandler::exportToJSON(const std::vector<TodoItem>& todos) {
    std::string timestamp = getCurrentTimestamp();
    std::string jsonFilename = "exports/todos_export_" + timestamp + ".json";
    
    // Create exports directory if it doesn't exist
    #ifdef _WIN32
    system("mkdir exports 2>nul");
    #else
    system("mkdir -p exports 2>/dev/null");
    #endif
    
    std::ofstream jsonFile(jsonFilename);
    if (!jsonFile.is_open()) {
        std::cerr << "❌ Could not create JSON file: " << jsonFilename << std::endl;
        return false;
    }
    
    // Write JSON
    jsonFile << "{\n";
    jsonFile << "  \"todos\": [\n";
    
    for (size_t i = 0; i < todos.size(); i++) {
        const auto& item = todos[i];
        jsonFile << "    {\n";
        jsonFile << "      \"id\": " << item.id << ",\n";
        jsonFile << "      \"title\": \"" << item.title << "\",\n";
        jsonFile << "      \"description\": \"" << item.description << "\",\n";
        jsonFile << "      \"dueDate\": \"" << item.dueDate << "\",\n";
        jsonFile << "      \"priority\": \"" << item.priorityToString() << "\",\n";
        jsonFile << "      \"status\": \"" << item.statusToString() << "\",\n";
        jsonFile << "      \"createdAt\": " << item.createdAt << ",\n";
        jsonFile << "      \"updatedAt\": " << item.updatedAt << "\n";
        jsonFile << "    }";
        
        if (i < todos.size() - 1) {
            jsonFile << ",";
        }
        jsonFile << "\n";
    }
    
    jsonFile << "  ]\n";
    jsonFile << "}\n";
    
    jsonFile.close();
    std::cout << "✅ JSON exported: " << jsonFilename << std::endl;
    return true;
}

void FileHandler::showFileStats() const {
    struct stat fileInfo;
    
    if (stat(filename.c_str(), &fileInfo) == 0) {
        std::cout << "\n=== FILE STATISTICS ===\n";
        std::cout << "File: " << filename << std::endl;
        std::cout << "Size: " << fileInfo.st_size << " bytes" << std::endl;
        std::cout << "Last modified: " << std::ctime(&fileInfo.st_mtime);
        
        // Calculate file age
        std::time_t now = std::time(nullptr);
        double ageHours = std::difftime(now, fileInfo.st_mtime) / 3600.0;
        std::cout << "Age: " << std::fixed << std::setprecision(1) << ageHours << " hours\n";
    } else {
        std::cout << "📝 File does not exist or cannot be accessed" << std::endl;
    }
}

// Helper method to serialize a TodoItem
std::string FileHandler::serializeTodo(const TodoItem& item) {
    std::stringstream ss;
    ss << item.id << "|"
       << item.title << "|"
       << item.description << "|"
       << item.dueDate << "|"
       << static_cast<int>(item.priority) << "|"
       << static_cast<int>(item.status) << "|"
       << item.createdAt << "|"
       << item.updatedAt;
    return ss.str();
}

// Helper method to deserialize a TodoItem
TodoItem FileHandler::deserializeTodo(const std::string& data) {
    std::stringstream ss(data);
    std::string token;
    std::vector<std::string> tokens;
    
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    
    if (tokens.size() < 8) {
        throw std::runtime_error("Invalid todo data format");
    }
    
    TodoItem item;
    item.id = std::stoi(tokens[0]);
    item.title = tokens[1];
    item.description = tokens[2];
    item.dueDate = tokens[3];
    item.priority = static_cast<Priority>(std::stoi(tokens[4]));
    item.status = static_cast<Status>(std::stoi(tokens[5]));
    item.createdAt = std::stol(tokens[6]);
    item.updatedAt = std::stol(tokens[7]);
    
    return item;
}

std::string FileHandler::getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* tm = std::localtime(&now);
    
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", tm);
    
    return std::string(buffer);
}