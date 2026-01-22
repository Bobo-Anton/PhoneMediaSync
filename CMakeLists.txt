cmake_minimum_required(VERSION 3.16)

# Project name and language
project(PhoneMediaSyncServer LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create the executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Server.cpp
    src/SocketMonitor.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    inc
)
