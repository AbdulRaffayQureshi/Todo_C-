#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "../controllers/TodoController.h"
#include "../utils/ColorManager.h"
#include <vector>
#include <string>

class DisplayManager {
private:
    TodoController& controller;
    
public:
    DisplayManager(TodoController& controller);
    
    // Display methods
    void showMainMenu();
    void showAllTodos();
    void showTodoDetails(int id);
    void showSearchResults(const std::vector<TodoItem*>& results);
    void showStatistics();
    
    // Input methods
    int getMenuChoice();
    std::string getInput(const std::string& prompt);
    int getIntInput(const std::string& prompt);
    Priority getPriorityInput();
    std::string getDateInput();
    
    // UI Components
    void printHeader(const std::string& title);
    void printFooter();
    void printTodoTable(const std::vector<TodoItem>& todos);
    void printTodoCard(const TodoItem& todo);
    
    // Demo functions for presentation
    void runDemoMode();
    void addNewTodo();
    void showAlgorithmsDemo();
    
private:
    void clearInputBuffer();
};

#endif // DISPLAYMANAGER_H