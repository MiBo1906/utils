enable_testing()

# specify the binary for the unit tests and deeper structure
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.cpp)

add_executable(unit-test-config ${TEST_SOURCES})

if(NOT MSVC)
  set(PThreadLib -pthread)
endif()

target_link_libraries(unit-test-config ${PThreadLib} GTest::gtest_main config)

# specify the include directories
include_directories(${GTEST_INCLUDE_DIRS})
gtest_discover_tests(unit-test-config)