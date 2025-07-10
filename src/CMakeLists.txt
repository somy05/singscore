cmake_minimum_required(VERSION 3.10)

# Define your project name
project(SingScore)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Specify SFML directories (for system installation)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-graphics sfml-window sfml-system sfml-audio)

# Find PortAudio
find_path(PORTAUDIO_INCLUDE_DIR portaudio.h)
find_library(PORTAUDIO_LIBRARY portaudio)

if(NOT PORTAUDIO_INCLUDE_DIR OR NOT PORTAUDIO_LIBRARY)
    message(FATAL_ERROR "PortAudio not found")
endif()

# Add SFML and PortAudio include directories
include_directories(${SFML_INCLUDE_DIRS} ${PORTAUDIO_INCLUDE_DIR})

# Specify source files
set(SOURCE_FILES main.cpp Game.cpp audioInput.cpp audioOutput.cpp states/gameState.cpp states/menuState.cpp states/playingState.cpp states/splashState.cpp)


# Create the executable from source files
add_executable(SingScore ${SOURCE_FILES})

# Link the required SFML libraries and PortAudio
target_link_libraries(SingScore ${SFML_LIBRARIES} ${PORTAUDIO_LIBRARY})

# Copy assets to build directory
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
if(EXISTS ${ASSETS_SOURCE_DIR})
    message(STATUS "Copying assets from: ${ASSETS_SOURCE_DIR}")
    file(COPY ${ASSETS_SOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})
else()
    message(FATAL_ERROR "Assets directory not found at: ${ASSETS_SOURCE_DIR}")
endif()