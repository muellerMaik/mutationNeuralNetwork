cmake_minimum_required(VERSION 3.20)
project(mmNEAT LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

# Add pybind11 from cloned repo
add_subdirectory(extern/pybind11)

# Find TBB
find_package(TBB REQUIRED)

# Include directories
include_directories(
    src
)

# Source files
set(SRC_FILES
    src/main.cpp
    src/network.cpp
    src/connection.cpp
    src/neuron.cpp
    src/randomGenerator.cpp
    pybind/pybind.cpp
)

# Create Python module
pybind11_add_module(mmNEAT ${SRC_FILES})

# Link TBB
target_link_libraries(mmNEAT PRIVATE TBB::tbb)
