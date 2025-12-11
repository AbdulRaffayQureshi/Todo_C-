#ifdef _WIN32
#include <windows.h>
#endif

#include "ColorManager.h"
#include <iostream>
#include <iomanip>

// ANSI escape codes for colors
const std::string ColorManager::RED = "\033[31m";
const std::string ColorManager::GREEN = "\033[32m";
const std::string ColorManager::YELLOW = "\033[33m";
const std::string ColorManager::BLUE = "\033[34m";
const std::string ColorManager::MAGENTA = "\033[35m";
const std::string ColorManager::CYAN = "\033[36m";
const std::string ColorManager::WHITE = "\033[37m";
const std::string ColorManager::RESET = "\033[0m";

const std::string ColorManager::BG_RED = "\033[41m";
const std::string ColorManager::BG_GREEN = "\033[42m";
const std::string ColorManager::BG_YELLOW = "\033[43m";
const std::string ColorManager::BG_BLUE = "\033[44m";
const std::string ColorManager::BG_MAGENTA = "\033[45m";
const std::string ColorManager::BG_CYAN = "\033[46m";
const std::string ColorManager::BG_WHITE = "\033[47m";

const std::string ColorManager::BOLD = "\033[1m";
const std::string ColorManager::DIM = "\033[2m";
const std::string ColorManager::UNDERLINE = "\033[4m";

std::string ColorManager::colorText(const std::string& text, const std::string& color) {
    return color + text + RESET;
}

std::string ColorManager::colorPriority(int priority) {
    switch (priority) {
        case 0: return colorText("Low", GREEN);
        case 1: return colorText("Medium", YELLOW);
        case 2: return colorText("High", MAGENTA);
        case 3: return colorText("Urgent", RED + BOLD);
        default: return colorText("Unknown", WHITE);
    }
}

std::string ColorManager::colorStatus(const std::string& status) {
    if (status == "Pending") return colorText(status, RED);
    if (status == "In Progress") return colorText(status, YELLOW);
    if (status == "Completed") return colorText(status, GREEN);
    return colorText(status, WHITE);
}

std::string ColorManager::colorDueDate(int daysRemaining) {
    if (daysRemaining < 0) return colorText("Overdue", RED + BOLD);
    if (daysRemaining == 0) return colorText("Today", YELLOW + BOLD);
    if (daysRemaining <= 3) return colorText(std::to_string(daysRemaining) + " days", YELLOW);
    return colorText(std::to_string(daysRemaining) + " days", GREEN);
}

void ColorManager::printProgressBar(int percentage, int width) {
    int filledWidth = (percentage * width) / 100;
    
    std::cout << "[";
    for (int i = 0; i < width; ++i) {
        if (i < filledWidth) {
            if (percentage < 30) std::cout << RED << "=";
            else if (percentage < 70) std::cout << YELLOW << "=";
            else std::cout << GREEN << "=";
        } else {
            std::cout << DIM << "-";
        }
    }
    std::cout << RESET << "] " << percentage << "%" << std::endl;
}

void ColorManager::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}