#ifndef COLORMANAGER_H
#define COLORMANAGER_H

#include <string>

class ColorManager {
public:


    // Text colors
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    static const std::string RESET;
    
    // Background colors
    static const std::string BG_RED;
    static const std::string BG_GREEN;
    static const std::string BG_YELLOW;
    static const std::string BG_BLUE;
    static const std::string BG_MAGENTA;
    static const std::string BG_CYAN;
    static const std::string BG_WHITE;
    
    // Text styles
    static const std::string BOLD;
    static const std::string DIM;
    static const std::string UNDERLINE;
    
    // Color methods
    static std::string colorText(const std::string& text, const std::string& color);
    static std::string colorPriority(int priority);
    static std::string colorStatus(const std::string& status);
    static std::string colorDueDate(int daysRemaining);
    
    // Progress bar
    static void printProgressBar(int percentage, int width = 50);
    
    // Clear screen
    static void clearScreen();
};

#endif // COLORMANAGER_H