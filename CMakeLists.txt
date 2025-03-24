cmake_minimum_required(VERSION 3.26)

# Define main project and executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

# Find SFML package (make sure SFML is installed)
find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

# Find SQLite package
find_package(SQLite3 REQUIRED)

###############################################################################

# Main game executable (EXCLUDES sqlite_test.cpp to prevent duplicate main() issue)
add_executable(${MAIN_EXECUTABLE_NAME}
        src/main.cpp
        generated/src/Helper.cpp
)

# Link SFML and SQLite to the main executable
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio SQLite::SQLite3)

###############################################################################

# Separate test executable for SQLite (so it doesn't conflict with the main game)
add_executable(sqlite_test src/sqlite_test.cpp)
target_link_libraries(sqlite_test PRIVATE SQLite::SQLite3)

###############################################################################

# Set compiler flags (Optional)
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

###############################################################################

# Include directories for system headers
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)

###############################################################################

# Install binaries
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})