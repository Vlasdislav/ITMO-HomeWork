cmake_minimum_required (VERSION 3.8)

project(clw-08)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX") # CMake already contains W3 in its flags
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra-semi -g -fsanitize=address -fno-omit-frame-pointer") # -O1
endif()

# Uncomment to work on task 1, fibonacci
add_executable(task-1-test src/task_1/test.cpp)

# Uncomment to work on task 2, functions
add_executable(task-2-test src/task_2/test.cpp)

# Uncomment to work on task 3, priority_queue
add_executable(task-3-test src/task_3/test.cpp)
add_executable(task-3-test-custom-comparator src/task_3/test_custom_comparator.cpp)
