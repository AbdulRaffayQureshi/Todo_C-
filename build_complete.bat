@echo off
echo ==========================================
echo    COMPILING COMPLETE MVC TODO APP
echo ==========================================
echo.

echo Closing any running TodoApp...
taskkill /f /im TodoApp.exe 2>nul
del TodoApp.exe 2>nul
del *.o 2>nul

echo.
echo Step 1: Compiling all source files...
echo ==========================================

echo Compiling models...
g++ -std=c++17 -c src/models/TodoItem.cpp -I. -o TodoItem.o
g++ -std=c++17 -c src/models/PriorityQueue.cpp -I. -o PriorityQueue.o

echo Compiling utils...
g++ -std=c++17 -c src/utils/ColorManager.cpp -I. -o ColorManager.o
g++ -std=c++17 -c src/utils/FileHandler.cpp -I. -o FileHandler.o

echo Compiling controllers...
g++ -std=c++17 -c src/controllers/TodoController.cpp -I. -o TodoController.o

echo Compiling views...
g++ -std=c++17 -c src/views/DisplayManager.cpp -I. -o DisplayManager.o

echo Compiling algorithms...
g++ -std=c++17 -c src/algorithms/SortSearch.cpp -I. -o SortSearch.o

echo Compiling tests...
g++ -std=c++17 -c tests/TestDataGenerator.cpp -I. -o TestDataGenerator.o

echo Compiling main...
g++ -std=c++17 -c main.cpp -I. -o main.o

echo.
echo Step 2: Linking all object files...
echo ==========================================
g++ -std=c++17 -o TodoApp.exe ^
    main.o ^
    TodoItem.o ^
    PriorityQueue.o ^
    ColorManager.o ^
    FileHandler.o ^
    TodoController.o ^
    DisplayManager.o ^
    SortSearch.o ^
    TestDataGenerator.o

if %errorlevel% equ 0 (
    echo.
    echo     BUILD SUCCESSFUL!
    echo.
    echo ==========================================
    echo     APPLICATION READY!
    echo ==========================================
    echo.
    echo For presentation:
    echo 1. Run the app
    echo 2. Choose Option 10 for Demo Mode
    echo 3. Choose Option 9 for DSA Algorithms
    echo.
    timeout /t 3
    echo Starting application...
    echo ==========================================
    TodoApp.exe
) else (
    echo.
    echo ✗ Build failed! Trying minimal version...
    echo.
    echo ==========================================
    echo    MINIMAL BUILD ATTEMPT
    echo ==========================================
    
    g++ -std=c++17 -o TodoApp_minimal.exe ^
        main.cpp ^
        src/models/TodoItem.cpp ^
        src/models/PriorityQueue.cpp ^
        src/controllers/TodoController.cpp ^
        src/views/DisplayManager.cpp ^
        src/utils/ColorManager.cpp ^
        -I.
    
    if %errorlevel% equ 0 (
        echo ✓ Minimal build successful!
        echo Run: TodoApp_minimal.exe
        timeout /t 2
        TodoApp_minimal.exe
    )
)

pause
