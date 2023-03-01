# Additional target to perform clang-format/clang-tidy run
# Requires clang-format and clang-tidy

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.hpp)

FUNCTION (EXCLUDE_FILES_FROM_DIR_IN_LIST _InFileList _excludeDirName _verbose)
  foreach (ITR ${_InFileList})
    if ("${_verbose}")
      message(STATUS "ITR=${ITR}")
    endif ("${_verbose}")

    if ("${ITR}" MATCHES "(.*)${_excludeDirName}(.*)")                   # Check if the item matches the directory name in _excludeDirName
      message(STATUS "Remove Item from List:${ITR}")
      list (REMOVE_ITEM _InFileList ${ITR})                              # Remove the item from the list
    endif ("${ITR}" MATCHES "(.*)${_excludeDirName}(.*)")

  endforeach(ITR)
  set(ALL_SOURCE_FILES ${_InFileList} PARENT_SCOPE)                          # Return the SOURCE_FILES variable to the calling parent
ENDFUNCTION (EXCLUDE_FILES_FROM_DIR_IN_LIST)

# Get all project files
EXCLUDE_FILES_FROM_DIR_IN_LIST("${ALL_SOURCE_FILES}" "/build/" FALSE)
EXCLUDE_FILES_FROM_DIR_IN_LIST("${ALL_SOURCE_FILES}" "/unit-test/" FALSE)
EXCLUDE_FILES_FROM_DIR_IN_LIST("${ALL_SOURCE_FILES}" "/include/" FALSE)

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
        -std=c++17
        -I${CMAKE_SOURCE_DIR}/include
)
