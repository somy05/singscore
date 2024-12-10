cmake_minimum_required(VERSION 3.10)

# Define your project name
project(SingScore)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Specify SFML directories (for Homebrew installation)
set(SFML_INCLUDE_DIR "/opt/homebrew/include")
set(SFML_LIB_DIR "/opt/homebrew/lib")

# Add SFML include and library directories
include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

# Specify source files
set(SOURCE_FILES main.cpp Game.cpp states/gameState.cpp states/menuState.cpp states/playingState.cpp states/splashState.cpp)


# Create the executable from source files
add_executable(SingScore ${SOURCE_FILES})

# Link the required SFML libraries
target_link_libraries(SingScore sfml-graphics sfml-window sfml-system)

# Copy assets to build directory
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
if(EXISTS ${ASSETS_SOURCE_DIR})
    message(STATUS "Copying assets from: ${ASSETS_SOURCE_DIR}")
    file(COPY ${ASSETS_SOURCE_DIR} DESTINATION ${CMAKE_BINARY_DIR})
else()
    message(FATAL_ERROR "Assets directory not found at: ${ASSETS_SOURCE_DIR}")
endif()