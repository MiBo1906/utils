file(GLOB_RECURSE SRC LIST_DIRECTORIES false *.cpp)

# specify the SOURCE variable for the current target
set(SOURCES ${SRC})

add_library(config SHARED ${SOURCES})

target_include_directories(config PRIVATE .)