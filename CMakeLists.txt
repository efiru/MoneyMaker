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
# Find SFML 3 (Modern targets!)
find_package(SFML 3 REQUIRED COMPONENTS graphics window system audio)

# Find SQLite
find_package(SQLite3 REQUIRED)

###############################################################################
# Main game executable (excluding sqlite_test.cpp to avoid main() conflict)
add_executable(${MAIN_EXECUTABLE_NAME}
        src/main.cpp
        generated/src/Helper.cpp
)

# Link SFML and SQLite
target_link_libraries(${MAIN_EXECUTABLE_NAME}
        PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        SQLite::SQLite3
)

# Include SFML headers
target_include_directories(${MAIN_EXECUTABLE_NAME}
        SYSTEM PRIVATE ${SFML_INCLUDE_DIRS}
)

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