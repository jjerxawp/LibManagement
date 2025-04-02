cmake_minimum_required(VERSION 3.10)

project(LibraryManagement CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add the include directory
include_directories(include)

# Add source files
set(SOURCES
    src/main.cpp
    src/book.cpp
    src/member.cpp
    src/utils.cpp
)

# Define the executable
add_executable(LibraryManagement ${SOURCES})

# Set the output directory for binaries
set_target_properties(LibraryManagement PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../build"
)
