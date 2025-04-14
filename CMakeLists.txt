cmake_minimum_required(VERSION 3.26)

set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

# C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set sysroot explicit to avoid Xcode warnings
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

# Optional: custom modules
include(cmake/Options.cmake OPTIONAL)
include(cmake/CompilerFlags.cmake OPTIONAL)
include(cmake/CopyHelper.cmake OPTIONAL)

# ========================================================================
# Include SFML (from Homebrew)
include_directories(SYSTEM /opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# Executabilul principal
add_executable(${MAIN_EXECUTABLE_NAME}
        src/main.cpp
        generated/src/Helper.cpp
)

# Include generated headers
target_include_directories(${MAIN_EXECUTABLE_NAME}
        SYSTEM PRIVATE
        generated/include
)

# Link SFML libraries
target_link_libraries(${MAIN_EXECUTABLE_NAME}
        sfml-graphics
        sfml-window
        sfml-system
)

# Compiler flags (dacă ai definit funcția în CompilerFlags.cmake)
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

# Instalare
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# Copiere fișiere suplimentare (ex: fonturi sau fișiere txt)
copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(FILES assets/arial.ttf COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/assets)
configure_file(assets/arial.ttf assets/arial.ttf COPYONLY)