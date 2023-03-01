# specify a executeable in this directory
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# specify necessary libaries for the app
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} gtest gmock)