cmake_minimum_required(VERSION 3.10)

project(ThreadPoolWithQueue)

# Set C++ standard (adjust as needed)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Export compile commands for tools like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")

# Recursively find all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Add the executable
add_executable(ThreadPoolWithQueue ${SOURCES})

# Include the src directory for headers (handles nested folders)
target_include_directories(ThreadPoolWithQueue PRIVATE src)

