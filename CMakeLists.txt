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
if(WIN32)
    # Only set Windows-specific paths when building on Windows.
    set(SQLite3_INCLUDE_DIR "C:/actual/path/to/sqlite3/include")
    set(SQLite3_LIBRARY "C:/actual/path/to/sqlite3/sqlite3.lib")
elseif(APPLE)
    # Use Homebrew's installation on macOS.
    set(SQLite3_INCLUDE_DIR "/opt/homebrew/opt/sqlite/include")
    set(SQLite3_LIBRARY "/opt/homebrew/opt/sqlite/lib/libsqlite3.dylib")
endif()
# Find SQLite
find_package(SQLite3 REQUIRED)

###############################################################################
# Main game executable (excluding sqlite_test.cpp to avoid main() conflict)
add_executable(${MAIN_EXECUTABLE_NAME}
        src/main.cpp
        generated/src/Helper.cpp
)

# Link SQLite
target_link_libraries(${MAIN_EXECUTABLE_NAME} SQLite::SQLite3)

# Include generated headers
target_include_directories(${MAIN_EXECUTABLE_NAME}
        SYSTEM PRIVATE generated/include
)

# Set compiler flags (optional sanitizers)
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

# Install main executable
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# Copy additional resource files
copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

###############################################################################
# SQLite test binary
add_executable(sqlite_test src/sqlite_test.cpp)
target_link_libraries(sqlite_test PRIVATE SQLite::SQLite3)