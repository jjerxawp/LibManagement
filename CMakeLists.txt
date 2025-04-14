cmake_minimum_required(VERSION 3.10)

project(LibManagement CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory for header files
include_directories(include)

# List source files
set(SOURCES
    src/main.cpp
    src/library.cpp
    src/books.cpp
    src/users.cpp
)

# Create the executable
add_executable(LibManagement ${SOURCES})

# Set output directory to project_root/build
set_target_properties(LibManagement PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)