# 📝 Todo++ - C++ Todo Application with DSA & MVC Architecture

<div align="center">

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![MVC](https://img.shields.io/badge/Architecture-MVC-4A90E2?style=for-the-badge)
![DSA](https://img.shields.io/badge/Algorithms-DSA-00D26A?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Cross--Platform-7289DA?style=for-the-badge)

**A professional Todo Application implementing multiple Data Structures & Algorithms with MVC architecture, file persistence, and colored terminal UI.**

[![GitHub](https://img.shields.io/badge/GitHub-Repository-181717?style=for-the-badge&logo=github)](https://github.com/AbdulRaffayQureshi/Todo_C-)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](LICENSE)

</div>

## ✨ Features Overview

<div align="center">

| 🔍 Searching Algorithms  | 📊 Sorting Algorithms   | 💾 File Operations  | 🎨 UI Features       |
| ------------------------ | ----------------------- | ------------------- | -------------------- |
| Linear Search (O(n))     | Quick Sort (O(n log n)) | Binary File Storage | Colorful Terminal UI |
| Binary Search (O(log n)) | Merge Sort (O(n log n)) | CSV Export          | Progress Bars        |
| Title Search             | Heap Sort (O(n log n))  | JSON Export         | ASCII Art Headers    |
| Priority Queue Search    | Bubble Sort (O(n²))     | Auto Backup         | Status Highlighting  |

</div>

## 📁 Project Structure (MVC Architecture)

```bash
TodoApp/
├── 📋 main.cpp                    # Application entry point
├── 📜 CMakeLists.txt             # Build configuration
├── 🛠️ build_complete.bat         # Windows build script
├── 📚 src/
│   ├── 📦 models/                # Data models (M)
│   │   ├── TodoItem.h/cpp       # Todo item structure
│   │   └── PriorityQueue.h/cpp  # Heap-based priority queue
│   ├── 🎮 controllers/           # Business logic (C)
│   │   └── TodoController.h/cpp # CRUD operations
│   ├── 👁️ views/                # Presentation layer (V)
│   │   └── DisplayManager.h/cpp # Terminal UI manager
│   ├── ⚙️ utils/                 # Utility classes
│   │   ├── ColorManager.h/cpp   # ANSI color codes
│   │   ├── FileHandler.h/cpp    # File I/O operations
│   │   └── SortSearch.h/cpp     # Search & sort algorithms
│   ├── 🧠 algorithms/           # Algorithm implementations
│   │   └── SortSearch.h/cpp     # Multiple sorting algorithms
│   └── 🧪 tests/                # Testing utilities
│       └── TestDataGenerator.h/cpp # Performance testing
```

## 🚀 Getting Started

### Prerequisites

- **C++17 Compiler** (g++/clang/MSVC)
- **CMake** (version 3.10+)
- **Git** for version control

### Quick Installation

#### Method 1: Using Batch Script (Windows)

```bash
# Clone the repository
git clone https://github.com/AbdulRaffayQureshi/Todo_C-.git
cd Todo_C-

# Build and run
build_complete.bat
```

#### Method 2: Using CMake

```bash
# Clone repository
git clone https://github.com/AbdulRaffayQureshi/Todo_C-.git
cd Todo_C-

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .

# Run application
./TodoApp  # or TodoApp.exe on Windows
```

## 🔧 Build Configuration

**`CMakeLists.txt`** - Professional build setup:

```cmake
cmake_minimum_required(VERSION 3.10)
project(TodoApp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/EHsc /utf-8)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()
```

**`build_complete.bat`** - Windows compilation script:

```batch
@echo off
echo ==========================================
echo    COMPILING COMPLETE MVC TODO APP
echo ==========================================
g++ -std=c++17 -o TodoApp.exe main.cpp src/.../*.cpp -I.
```

## 🎮 Usage & Features

### Main Menu Interface

```
╔══════════════════════════════════════════════════════╗
║           TODO APPLICATION - MAIN MENU               ║
╚══════════════════════════════════════════════════════╝

1. Add New Todo
2. View All Todos
3. Search Todo
4. Update Todo
5. Mark as Complete
6. Sort Todos
7. Show Statistics
8. File Operations
9. DSA Algorithms Demo
10. Run Demo Mode
0. Exit
```

### Demo Mode (Perfect for Presentations)

Access comprehensive demo with sample data:

- **Pre-loaded 5 sample todos** with various priorities
- **Color-coded status display**
- **Algorithm complexity explanations**
- **Performance metrics**

## 🧠 Data Structures & Algorithms

### 📊 Algorithm Complexity Comparison

| Algorithm         | Best Case  | Average Case | Worst Case | Space    | Implementation           |
| ----------------- | ---------- | ------------ | ---------- | -------- | ------------------------ |
| **Linear Search** | O(1)       | O(n)         | O(n)       | O(1)     | Sequential iteration     |
| **Binary Search** | O(1)       | O(log n)     | O(log n)   | O(1)     | Divide & conquer         |
| **Quick Sort**    | O(n log n) | O(n log n)   | O(n²)      | O(log n) | Partition-based          |
| **Merge Sort**    | O(n log n) | O(n log n)   | O(n log n) | O(n)     | Stable, divide & conquer |
| **Heap Sort**     | O(n log n) | O(n log n)   | O(n log n) | O(1)     | Binary heap              |
| **Bubble Sort**   | O(n)       | O(n²)        | O(n²)      | O(1)     | Simple comparison        |

### 🏗️ Priority Queue Implementation

```cpp
class PriorityQueue {
private:
    std::vector<TodoItem> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void push(const TodoItem& item);  // O(log n)
    TodoItem pop();                    // O(log n)
    TodoItem peek() const;             // O(1)
};
```

## 💾 File Persistence System

### Multi-Format Support

```cpp
class FileHandler {
public:
    bool saveToFile(const PriorityQueue& todos);    // Binary format
    bool exportToCSV(const std::vector<TodoItem>& todos);
    bool exportToJSON(const std::vector<TodoItem>& todos);
    bool createBackup(const std::vector<TodoItem>& todos);
    bool restoreFromBackup();
};
```

### File Structure

- **Binary (.dat)**: Efficient storage with versioning
- **CSV**: Human-readable spreadsheet format
- **JSON**: Web-compatible structured data
- **Auto-backup**: Timestamped backups in `backup/` directory

## 🎨 Terminal UI Features

### Color Management System

```cpp
class ColorManager {
public:
    // ANSI escape codes
    static const std::string RED, GREEN, YELLOW, BLUE;
    static const std::string BOLD, UNDERLINE, RESET;

    static std::string colorPriority(int priority);
    static std::string colorStatus(const std::string& status);
    static void printProgressBar(int percentage, int width = 50);
};
```

### Visual Elements

- **Color-coded priorities** (Urgent: 🔴, High: 🟣, Medium: 🟡, Low: 🟢)
- **Progress bars** for completion rates
- **ASCII art borders** and headers
- **Status indicators** with emoji-style feedback

## 📈 Statistics & Analytics

### Real-time Metrics

```
=== Statistics ===
Total Todos: 12
Completed: 5 (41.7%)
In Progress: 3 (25.0%)
Pending: 4 (33.3%)

[██████████--------------------] 41%
```

### Performance Testing

```cpp
class TestDataGenerator {
public:
    static void generateSampleData(TodoController& controller, int count = 10);
    static void runPerformanceTests(TodoController& controller);
    static void testSearchAlgorithms();
    static void testSortAlgorithms();
};
```

## 🔍 Search Capabilities

### Multi-criteria Search

```cpp
// Search by ID (using linear/binary search)
TodoItem* searchById(int id);

// Search by title (partial match)
std::vector<TodoItem*> searchByTitle(const std::string& title);

// Search by priority/status
std::vector<TodoItem*> searchByPriority(Priority priority);
std::vector<TodoItem*> searchByStatus(Status status);
```

## 🔄 Sorting Options

### Multiple Sorting Algorithms

```cpp
// Quick Sort by Priority
void sortByPriority();  // O(n log n) average

// Merge Sort by Due Date
void sortByDueDate();   // O(n log n) guaranteed

// Bubble Sort by Status
void sortByStatus();    // O(n²) educational

// Heap Sort (built into PriorityQueue)
void heapSort(std::vector<TodoItem>& items);
```

## 📊 Todo Item Structure

```cpp
struct TodoItem {
    int id;
    std::string title;
    std::string description;
    std::string dueDate;
    Priority priority;  // LOW, MEDIUM, HIGH, URGENT
    Status status;      // PENDING, IN_PROGRESS, COMPLETED
    std::time_t createdAt;
    std::time_t updatedAt;

    // Operator overloads for PriorityQueue
    bool operator<(const TodoItem& other) const;
    bool operator>(const TodoItem& other) const;
};
```

## 🚀 Presentation Features

### Built-in Demo Mode

Perfect for academic presentations:

1. **Pre-loaded sample data**
2. **Algorithm explanations**
3. **Performance comparisons**
4. **Step-by-step walkthrough**

### Presentation Guide

Access via main menu or press 'P' at startup:

```cpp
void showPresentationGuide() {
    // Shows step-by-step presentation sequence
    // Explains MVC architecture
    // Demonstrates all features
}
```

## 🧪 Testing & Validation

### Automated Test Generation

```cpp
// Generate random test data
TestDataGenerator::generateSampleData(controller, 100);

// Run performance benchmarks
TestDataGenerator::runPerformanceTests(controller);

// Compare algorithm performance
TestDataGenerator::testSortAlgorithms();
```

## 🔧 Compilation Options

### Minimal Build (Quick Start)

```bash
g++ -std=c++17 -o TodoApp.exe main.cpp \
    src/models/TodoItem.cpp \
    src/models/PriorityQueue.cpp \
    src/controllers/TodoController.cpp \
    src/views/DisplayManager.cpp \
    src/utils/ColorManager.cpp \
    -I.
```

### Complete Build (All Features)

```bash
# Uses build_complete.bat or CMake
# Includes all algorithms, file handlers, and utilities
```

## 📁 Directory Structure After Build

```
TodoApp/
├── TodoApp.exe                 # Compiled executable
├── todos.dat                   # Persistent data (auto-generated)
├── backup/                     # Auto-generated backups
│   └── todo_backup_20241205_143022.dat
├── exports/                    # Export directory
│   ├── todos_export_20241205.csv
│   └── todos_export_20241205.json
└── src/                        # Source code (tracked in Git)
```

## 🎯 Key Features Summary

✅ **MVC Architecture** - Clean separation of concerns  
✅ **Multiple Sorting Algorithms** - Educational comparison  
✅ **Priority Queue** - Efficient task management  
✅ **File Persistence** - Binary, CSV, JSON formats  
✅ **Colorful Terminal UI** - Professional presentation  
✅ **Cross-platform** - Windows, Linux, macOS support  
✅ **Demo Mode** - Ready for presentations  
✅ **Statistics & Analytics** - Progress tracking  
✅ **Backup System** - Data safety  
✅ **Performance Testing** - Algorithm benchmarks

## 🤝 Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**Abdul Raffay Qureshi**

- GitHub: [@AbdulRaffayQureshi](https://github.com/AbdulRaffayQureshi)
- Project: [Todo_C-](https://github.com/AbdulRaffayQureshi/Todo_C-)

## 🌟 Acknowledgments

- Inspired by academic Data Structures & Algorithms curriculum
- MVC pattern implementation for clean architecture
- ANSI color codes for terminal UI enhancement
- C++17 modern features utilization

---

<div align="center">

**Built with ❤️ using C++17, MVC Architecture, and DSA Principles**

[![Star History Chart](https://api.star-history.com/svg?repos=AbdulRaffayQureshi/Todo_C-&type=Date)](https://star-history.com/#AbdulRaffayQureshi/Todo_C-&Date)

</div>

## 📞 Support

For issues, questions, or contributions:

1. Check the [Issues](https://github.com/AbdulRaffayQureshi/Todo_C-/issues) page
2. Create a new issue with detailed description
3. Star the repository if you find it useful!

---

**Happy Coding!** 🚀✨

_"Good code is its own best documentation." - Steve McConnell_
