cmake_minimum_required(VERSION 3.26)

set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

# C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# macOS sysroot workaround
if(APPLE)
    set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")
endif()

# Opțional: alte module
include(cmake/Options.cmake OPTIONAL)
include(cmake/CompilerFlags.cmake OPTIONAL)
include(cmake/CopyHelper.cmake OPTIONAL)

find_package(nlohmann_json CONFIG REQUIRED)

# Detectează platforma și setează include/lib
if(APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
elseif(UNIX)
    include_directories(/usr/include)
    link_directories(/usr/lib)
elseif(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/external/SFML/include)
    link_directories(${CMAKE_SOURCE_DIR}/external/SFML/lib)
endif()

# Executabil principal
add_executable(${MAIN_EXECUTABLE_NAME}
        src/main.cpp
        generated/src/Helper.cpp
        src/Bancnota.h
        src/Bancnota.cpp
        src/Player.h
        src/Player.cpp
        src/Achievement.h
        src/Achievement.cpp
        src/Game.h
        src/Game.cpp
        src/Upgrade.h
        src/DoubleTapUpgrade.h
        src/DoubleTapUpgrade.cpp
        src/LevelUpgrade.h
        src/LevelUpgrade.cpp
        src/BanknoteUpgrade.h
        src/BanknoteUpgrade.cpp
        src/UltraUpgrade.h
        src/UltraUpgrade.cpp
        src/Reward.h
        src/UpgradeException.h
        src/JsonException.h
)

# Include foldere suplimentare
target_include_directories(${MAIN_EXECUTABLE_NAME}
        PRIVATE generated/include
)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Link SFML (manual, evităm find_package)

    # macOS and Windows: manual SFML linking
target_link_libraries(${MAIN_EXECUTABLE_NAME}
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)


# Sanitizatori (opțional)
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


