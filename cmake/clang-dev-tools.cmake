# Additional target to perform clang-format/clang-tidy run
# Requires clang-format and clang-tidy

# Get all project files
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)
set (EXCLUDE_DIR "/build/")
foreach (TMP_PATH ${ALL_SOURCE_FILES})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM ALL_SOURCE_FILES ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)

add_custom_target(
        clang-format
        COMMAND /usr/bin/clang-format
        -style=file
        -i
        ${ALL_SOURCE_FILES}
)

add_custom_target(
        clang-tidy
        COMMAND /usr/bin/clang-tidy
        ${ALL_SOURCE_FILES}
        -checks=cppcoreguidelines-*,clang-*,google-*
        --
        -std=c++11
        ${INCLUDE_DIRECTORIES}
)
