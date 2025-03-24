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


###############################################################################
# Main game executable (excluding sqlite_test.cpp to avoid main() conflict)
add_executable(${MAIN_EXECUTABLE_NAME}
        src/main.cpp
        generated/src/Helper.cpp
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
