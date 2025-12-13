cmake_minimum_required(VERSION 3.0.0)
project(nodepp-argon VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(NODEPP_ARGON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Search for Nodepp Core
if (NOT TARGET nodepp)
    find_package(nodepp REQUIRED)
    if(NOT nodepp_FOUND)
        message(FATAL_ERROR "Nodepp not found. Please install nodepp.")
    endif()
endif()

# Search for Argon2
find_library(ARGON2_LIBRARY NAMES argon2 REQUIRED)
# Check if the library file was found
if(NOT ARGON2_LIBRARY)
    message(FATAL_ERROR "Argon2 library not found. Please install libargon2-dev or equivalent files.")
endif()

# Search for argon2.h
find_path(ARGON2_INCLUDE_DIR NAMES argon2.h REQUIRED
    HINTS /usr/include /usr/local/include
    PATH_SUFFIXES argon2
)
if(NOT ARGON2_INCLUDE_DIR)
    message(FATAL_ERROR "Argon2 header file (argon2.h) not found.")
endif()

# interface-target
add_library(nodepp-argon INTERFACE)

# Combine project headers and Argon2 headers
target_include_directories(nodepp-argon INTERFACE 
    ${NODEPP_ARGON_INCLUDE_DIR}
    ${ARGON2_INCLUDE_DIR}
)

# Link against nodepp and the actual library path found by CMake
target_link_libraries(nodepp-argon INTERFACE 
    nodepp 
    ${ARGON2_LIBRARY}
)