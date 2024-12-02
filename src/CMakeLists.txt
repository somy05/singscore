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
set(SOURCE_FILES main.cpp Game.cpp gameState.h gameState.cpp)

# Create the executable from source files
add_executable(SingScore ${SOURCE_FILES})

# Link the required SFML libraries
target_link_libraries(SingScore sfml-graphics sfml-window sfml-system)