#include "src/controllers/TodoController.h"
#include "src/views/DisplayManager.h"
#include "tests/TestDataGenerator.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Windows specific headers
#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

void runApplication()
{
    TodoController controller;
    DisplayManager display(controller);

    bool running = true;

    while (running)
    {
        display.showMainMenu();
        int choice = display.getMenuChoice();

        switch (choice)
        {
        case 1:
            display.addNewTodo();
            break;

        case 2:
            display.showAllTodos();
            break;

        case 3:
        {
            // Search todo
            std::cout << "\nAvailable Todo IDs: ";
            auto todos = controller.getAllTodos();
            for (const auto &t : todos)
            {
                std::cout << t.id << " ";
            }
            std::cout << std::endl;

            int id = display.getIntInput("Enter ID to search: ");
            TodoItem *found = controller.searchById(id);

            if (found != nullptr)
            {
                std::cout << ColorManager::GREEN << "Found Todo ID " << id << "!\n"
                          << ColorManager::RESET;
                display.printTodoCard(*found);
            }
            else
            {
                std::cout << ColorManager::RED << "Todo not found!\n"
                          << ColorManager::RESET;
            }
            break;
        }

        case 4:
        {
            ColorManager::clearScreen();
            std::cout << ColorManager::MAGENTA << ColorManager::BOLD;
            std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
            std::cout << "║                  UPDATE TODO                       ║\n";
            std::cout << "╚══════════════════════════════════════════════════════╝\n";
            std::cout << ColorManager::RESET;

            // Get all todos
            auto allTodos = controller.getAllTodos();

            if (allTodos.empty())
            {
                std::cout << ColorManager::YELLOW << "\nNo todos found. Add some todos first!\n"
                          << ColorManager::RESET;
            }
            else
            {
                // Show available todos
                std::cout << ColorManager::CYAN << "\nAvailable Todos:\n"
                          << ColorManager::RESET;
                display.printTodoTable(allTodos);

                // Get ID to update
                int id = display.getIntInput("\nEnter ID of todo to update: ");

                // Check if ID exists
                TodoItem *todo = controller.searchById(id);

                if (todo == nullptr)
                {
                    std::cout << ColorManager::RED << "Todo ID " << id << " not found!\n"
                              << ColorManager::RESET;
                    std::cout << "Available IDs: ";
                    for (const auto &t : allTodos)
                    {
                        std::cout << t.id << " ";
                    }
                    std::cout << std::endl;
                }
                else
                {
                    // Show current todo details
                    std::cout << ColorManager::GREEN << "\n✅ Found Todo ID " << id << ColorManager::RESET << std::endl;
                    display.printTodoCard(*todo);

                    std::cout << ColorManager::CYAN << "\n=== Enter New Values (press Enter to keep current) ===\n"
                              << ColorManager::RESET;

                    // Get updated values
                    std::string newTitle = display.getInput("Enter new title: ");
                    std::string newDesc = display.getInput("Enter new description: ");
                    std::string newDate = display.getDateInput();

                    // Get priority
                    std::cout << ColorManager::CYAN << "\nSelect New Priority:\n"
                              << ColorManager::RESET;
                    std::cout << "1. " << ColorManager::GREEN << "Low\n"
                              << ColorManager::RESET;
                    std::cout << "2. " << ColorManager::YELLOW << "Medium\n"
                              << ColorManager::RESET;
                    std::cout << "3. " << ColorManager::MAGENTA << "High\n"
                              << ColorManager::RESET;
                    std::cout << "4. " << ColorManager::RED << "Urgent\n"
                              << ColorManager::RESET;
                    std::cout << "0. " << ColorManager::DIM << "Keep Current Priority\n"
                              << ColorManager::RESET;

                    int priorityChoice = display.getIntInput("Enter choice (0-4): ");
                    Priority newPriority = todo->priority;

                    if (priorityChoice != 0)
                    {
                        switch (priorityChoice)
                        {
                        case 1:
                            newPriority = Priority::LOW;
                            break;
                        case 2:
                            newPriority = Priority::MEDIUM;
                            break;
                        case 3:
                            newPriority = Priority::HIGH;
                            break;
                        case 4:
                            newPriority = Priority::URGENT;
                            break;
                        }
                    }

                    // Get status
                    std::cout << ColorManager::CYAN << "\nSelect New Status:\n"
                              << ColorManager::RESET;
                    std::cout << "1. " << ColorManager::YELLOW << "Pending\n"
                              << ColorManager::RESET;
                    std::cout << "2. " << ColorManager::BLUE << "In Progress\n"
                              << ColorManager::RESET;
                    std::cout << "3. " << ColorManager::GREEN << "Completed\n"
                              << ColorManager::RESET;
                    std::cout << "0. " << ColorManager::DIM << "Keep Current Status\n"
                              << ColorManager::RESET;

                    int statusChoice = display.getIntInput("Enter choice (0-3): ");
                    Status newStatus = todo->status;

                    if (statusChoice != 0)
                    {
                        switch (statusChoice)
                        {
                        case 1:
                            newStatus = Status::PENDING;
                            break;
                        case 2:
                            newStatus = Status::IN_PROGRESS;
                            break;
                        case 3:
                            newStatus = Status::COMPLETED;
                            break;
                        }
                    }

                    // Update the todo
                    bool success = controller.updateTodo(id, newTitle, newDesc, newDate,
                                                         newPriority, newStatus);

                    if (success)
                    {
                        std::cout << ColorManager::GREEN << "\n✅ Todo updated successfully!\n"
                                  << ColorManager::RESET;
                        std::cout << "Updated Todo Details:\n";
                        TodoItem *updatedTodo = controller.searchById(id);
                        if (updatedTodo)
                        {
                            display.printTodoCard(*updatedTodo);
                        }
                    }
                    else
                    {
                        std::cout << ColorManager::RED << "\n❌ Failed to update todo!\n"
                                  << ColorManager::RESET;
                    }
                }
            }
            break;
        }

        case 5:
        {
            // Mark as complete
            ColorManager::clearScreen();
            std::cout << ColorManager::CYAN << "\nAvailable Todo IDs:\n"
                      << ColorManager::RESET;

            auto todos = controller.getAllTodos();
            for (const auto &t : todos)
            {
                std::cout << t.id << ": " << t.title << " (" << t.statusToString() << ")\n";
            }

            int id = display.getIntInput("\nEnter ID to mark as complete: ");

            if (controller.markAsComplete(id))
            {
                std::cout << ColorManager::GREEN << "Todo " << id << " marked as complete!\n"
                          << ColorManager::RESET;
            }
            else
            {
                std::cout << ColorManager::RED << "Todo not found!\n"
                          << ColorManager::RESET;
            }
            break;
        }

        case 6:
        {
            // Sort todos
            std::cout << "\n1. Sort by Priority (Quick Sort)\n";
            std::cout << "2. Sort by Due Date (Merge Sort)\n";
            std::cout << "3. Sort by Status (Bubble Sort)\n";
            int sortChoice = display.getIntInput("Choose sorting method: ");

            switch (sortChoice)
            {
            case 1:
                controller.sortByPriority();
                std::cout << "Sorted by priority using Quick Sort!\n";
                break;
            case 2:
                controller.sortByDueDate();
                std::cout << "Sorted by due date using Merge Sort!\n";
                break;
            case 3:
                controller.sortByStatus();
                std::cout << "Sorted by status using Bubble Sort!\n";
                break;
            }

            // Show sorted results
            display.showAllTodos();
            break;
        }

        case 7:
            display.showStatistics();
            break;

        case 8:
        {
            // File operations
            ColorManager::clearScreen();
            std::cout << ColorManager::MAGENTA << ColorManager::BOLD;
            std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
            std::cout << "║                FILE OPERATIONS                    ║\n";
            std::cout << "╚══════════════════════════════════════════════════════╝\n";
            std::cout << ColorManager::RESET;

            std::cout << "\n1. Create Backup (Binary + CSV)\n";
            std::cout << "2. Export to CSV\n";
            std::cout << "3. Export to JSON\n";
            std::cout << "4. Restore from Backup\n";
            std::cout << "5. Show File Statistics\n";

            int fileChoice = display.getIntInput("Choose file operation (1-5): ");

            switch (fileChoice)
            {
            case 1:
                if (controller.createBackup())
                {
                    std::cout << ColorManager::GREEN << "\n✅ Backup created successfully!\n"
                              << ColorManager::RESET;
                    std::cout << "Files saved in 'backup/' and 'exports/' directories\n";
                }
                else
                {
                    std::cout << ColorManager::RED << "\n❌ Backup creation failed!\n"
                              << ColorManager::RESET;
                }
                break;

            case 2:
                if (controller.exportToCSV())
                {
                    std::cout << ColorManager::GREEN << "\n✅ CSV export successful!\n"
                              << ColorManager::RESET;
                    std::cout << "File saved in 'exports/' directory\n";
                }
                else
                {
                    std::cout << ColorManager::RED << "\n❌ CSV export failed!\n"
                              << ColorManager::RESET;
                }
                break;

            case 3:
                if (controller.exportToJSON())
                {
                    std::cout << ColorManager::GREEN << "\n✅ JSON export successful!\n"
                              << ColorManager::RESET;
                    std::cout << "File saved in 'exports/' directory\n";
                }
                else
                {
                    std::cout << ColorManager::RED << "\n❌ JSON export failed!\n"
                              << ColorManager::RESET;
                }
                break;

            case 4:
                if (controller.restoreFromBackup())
                {
                    std::cout << ColorManager::GREEN << "\n✅ Restore completed successfully!\n"
                              << ColorManager::RESET;
                    std::cout << "Please restart the application to load restored data\n";
                }
                else
                {
                    std::cout << ColorManager::YELLOW << "\n⚠️  Restore cancelled or failed\n"
                              << ColorManager::RESET;
                }
                break;

            case 5:
                controller.showFileStats();
                break;

            default:
                std::cout << ColorManager::RED << "Invalid choice!\n"
                          << ColorManager::RESET;
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        case 9:
            display.showAlgorithmsDemo();
            break;

        case 10:
            display.runDemoMode();
            break;

        case 0:
            running = false;
            std::cout << "Saving data and exiting...\n";
            controller.saveToFile();
            break;

        default:
            std::cout << "Invalid choice!\n";
        }

        if (choice != 0)
        {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }
}

// ========== PRESENTATION HELPER FUNCTION ==========
void showPresentationGuide()
{
// Ensure colors work
#ifdef _WIN32
    system("chcp 65001 > nul");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode))
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif

    // Clear screen
    system("cls");

    // Presentation header
    std::cout << "\033[1;35m"; // Magenta bold
    std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
    std::cout << "║           TODO APP - PRESENTATION GUIDE           ║\n";
    std::cout << "╚══════════════════════════════════════════════════════╝\n";
    std::cout << "\033[0m\n";

    // Step-by-step guide
    std::cout << "\033[1;33mFOLLOW THIS SEQUENCE FOR BEST DEMO:\033[0m\n\n";

    std::cout << "STEP 1: \033[32m[Option 10] - DEMO MODE\033[0m\n";
    std::cout << "   • Pre-loads 5 sample todos\n";
    std::cout << "   • Shows project features\n";
    std::cout << "   • Prepares data for demonstration\n\n";

    std::cout << "STEP 2: \033[32m[Option 9] - DSA ALGORITHMS\033[0m\n";
    std::cout << "   • Explains MVC Architecture\n";
    std::cout << "   • Shows time/space complexity\n";
    std::cout << "   • Compares sorting algorithms\n\n";

    std::cout << "STEP 3: \033[32m[Option 2] - VIEW ALL TODOS\033[0m\n";
    std::cout << "   • Shows colored terminal output\n";
    std::cout << "   • Demonstrates priority highlighting\n";
    std::cout << "   • Shows due date calculations\n\n";

    std::cout << "STEP 4: \033[32m[Option 6] - SORT TODOS\033[0m\n";
    std::cout << "   • Choose [1] Quick Sort (by Priority)\n";
    std::cout << "   • Choose [2] Merge Sort (by Date)\n";
    std::cout << "   • Choose [3] Bubble Sort (by Status)\n\n";

    std::cout << "STEP 5: \033[32m[Option 8] - FILE OPERATIONS\033[0m\n";
    std::cout << "   • Choose [1] Create Backup\n";
    std::cout << "   • Choose [2] Export to CSV\n\n";

    std::cout << "STEP 6: \033[32m[Option 7] - STATISTICS\033[0m\n";
    std::cout << "   • Shows progress bars\n";
    std::cout << "   • Shows completion analytics\n";
    std::cout << "   • Demonstrates data visualization\n\n";

    std::cout << "\033[1;36mKEY POINTS TO EXPLAIN DURING PRESENTATION:\033[0m\n";
    std::cout << "• MVC Architecture separation\n";
    std::cout << "• Priority Queue (Binary Heap) - O(log n) operations\n";
    std::cout << "• Multiple sorting algorithms with different complexities\n";
    std::cout << "• File persistence and backup system\n";
    std::cout << "• Space optimization features\n\n";

    std::cout << "\033[1;35mPress Enter to start the TodoApp...\033[0m";
    std::cin.ignore();
    std::cin.get();

    // Clear screen for the actual app
    system("cls");
}

int main()
{
    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

// Enable ANSI escape codes on Windows
#ifdef _WIN32
    system("chcp 65001 > nul"); // UTF-8
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode))
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif

    // ========== PRESENTATION MODE CHECK ==========
    std::cout << "\033[1;36m"; // Cyan bold
    std::cout << "\n╔══════════════════════════════════════════════════════╗\n";
    std::cout << "║           TODO APP - DSA PROJECT                  ║\n";
    std::cout << "╚══════════════════════════════════════════════════════╝\n";
    std::cout << "\033[0m\n";

    std::cout << "Enter 'P' for Presentation Guide, or any other key to skip: ";
    char choice;
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 'P' || choice == 'p')
    {
        showPresentationGuide();
    }

    // Clear screen before showing main menu
    system("cls");

    // ========== REST OF YOUR EXISTING CODE ==========
    try
    {
        runApplication();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
