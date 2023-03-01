# specify the required cmake version
cmake_minimum_required(VERSION 3.21)
# set the project name and version
project(common VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# searching necessary packages for building the unit tests
find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

# Including extra cmake rules
include(cmake/clang-dev-tools.cmake)

# include further diretories with cmake instructions
add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(unit-test)
