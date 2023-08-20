cmake_minimum_required(VERSION 3.26)
project(UnoAlpha)

set(CMAKE_CXX_STANDARD 14)

# Add your executable target
add_executable(UnoAlpha UnoAlpha/src/main.cpp)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include the OpenCV include directories
target_include_directories(UnoAlpha PRIVATE ${OpenCV_INCLUDE_DIRS})

# Link your executable with OpenCV libraries
target_link_libraries(UnoAlpha PRIVATE ${OpenCV_LIBS})
