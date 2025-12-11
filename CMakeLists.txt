cmake_minimum_required(VERSION 3.10)
project(TodoApp VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable colors in output
if(MSVC)
    add_compile_options(/EHsc /utf-8)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Source files
set(SOURCES
    src/models/TodoItem.cpp
    src/models/PriorityQueue.cpp
    src/controllers/TodoController.cpp
    src/views/DisplayManager.cpp
    src/utils/ColorManager.cpp
    src/utils/FileHandler.cpp
    src/algorithms/SortSearch.cpp
    tests/TestDataGenerator.cpp
    main.cpp
)

# Include directories
include_directories(
    src/models
    src/controllers
    src/views
    src/utils
    src/algorithms
    tests
)

# Create executable
add_executable(TodoApp ${SOURCES})

# Target properties
set_target_properties(TodoApp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# For Windows, link necessary libraries
if(WIN32)
    target_link_libraries(TodoApp)
endif()