cmake_minimum_required(VERSION 3.10)

project(LibManagement CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include and source directories
include_directories(include)

# List your source files
set(SOURCES
    src/main.cpp
    src/library.cpp
    # src/book.cpp
    # src/member.cpp
    # src/utils.cpp
)

# Create the executable
add_executable(LibManagement ${SOURCES})

# Set output directory relative to the project root (LibManagement/build)
set_target_properties(LibManagement PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)
