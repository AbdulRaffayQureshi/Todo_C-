#ifndef TESTDATAGENERATOR_H
#define TESTDATAGENERATOR_H

#include "../src/controllers/TodoController.h"
#include <vector>
#include <string>

class TestDataGenerator {
public:
    static void generateSampleData(TodoController& controller, int count = 10);
    static std::vector<TodoItem> generateTestItems(int count);
    static void runPerformanceTests(TodoController& controller);
    static void testSearchAlgorithms();
    static void testSortAlgorithms();
    static void testFileOperations();
    
private:
    static std::string randomTitle();
    static std::string randomDescription();
    static std::string randomDate(int daysFromNow);
    static Priority randomPriority();
};

#endif // TESTDATAGENERATOR_H