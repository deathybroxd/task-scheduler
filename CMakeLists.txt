cmake_minimum_required(VERSION 3.16)
project(task-scheduler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_library(scheduler_lib 
    src/Task.cpp
    src/DependencyGraph.cpp
    src/EDFScheduler.cpp
    src/SimClock.cpp
    src/Report.cpp
    src/Simulator.cpp
)

target_include_directories(scheduler_lib PUBLIC include)
target_compile_options(scheduler_lib PRIVATE -Wall -Wextra)

add_executable(task-scheduler main.cpp)
target_link_libraries(task-scheduler PRIVATE scheduler_lib)

# make run
add_custom_target(run 
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/task-scheduler
    DEPENDS task-scheduler
)

# make val
add_custom_target(val
    COMMAND valgrind ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/task-scheduler
    DEPENDS task-scheduler
)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(tests)