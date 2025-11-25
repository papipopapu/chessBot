cmake_minimum_required(VERSION 3.14)
project(ChessBot VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Source files
set(SOURCES
    core/bot.cpp
    core/position.cpp
    core/tables.cpp
    core/types.cpp
)

set(HEADERS
    core/position.h
    core/tables.h
    core/types.h
    core/eval.h
)

# Create executable
add_executable(chessbot ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(chessbot PRIVATE ${CMAKE_SOURCE_DIR}/core)

# Output directory
set_target_properties(chessbot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Install target
install(TARGETS chessbot DESTINATION bin)
