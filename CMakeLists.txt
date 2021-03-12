cmake_minimum_required(VERSION 2.8 )

add_definitions(-std=c++11)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(FirstTask)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# Executable for create matrix exercise
add_executable (TSP src/main.cpp src/addremove.cpp src/display.cpp src/tspalgorithm.cpp)
target_link_libraries (TSP ${OpenCV_LIBRARIES})             


set(CMAKE_BUILD_TYPE Debug)

