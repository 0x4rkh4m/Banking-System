# Minimum required version of CMake
cmake_minimum_required(VERSION 3.30)

# Project name and version
project(BankSystem VERSION 1.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Set compiler flags for GCC and Clang
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Gather all source files
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.c)

# Set the output directory for the binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})
