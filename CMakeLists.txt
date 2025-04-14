cmake_minimum_required(VERSION 3.26)

set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fix pentru avertismente macOS
set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")

# Include SFML headers și liburi (folosind Homebrew)
include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

# Opțional: alte module
include(cmake/Options.cmake OPTIONAL)
include(cmake/CompilerFlags.cmake OPTIONAL)
include(cmake/CopyHelper.cmake OPTIONAL)

# Executabil principal
add_executable(${MAIN_EXECUTABLE_NAME}
        src/main.cpp
        generated/src/Helper.cpp
)

# Include foldere suplimentare
target_include_directories(${MAIN_EXECUTABLE_NAME}
        PRIVATE generated/include
)

# Link SFML manual (evităm find_package)
target_link_libraries(${MAIN_EXECUTABLE_NAME}
        sfml-graphics
        sfml-window
        sfml-system
)

# Optional: adaugă sanitizatori
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

# Instalează binar și fișiere resurse
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# Copiere fonturi și fișiere adiționale
copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
copy_files(FILES assets/arial.ttf COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/assets)
configure_file(assets/arial.ttf assets/arial.ttf COPYONLY)