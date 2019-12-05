cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME saver)
project(${PROJECT_NAME})

find_package(OpenCV 4.1.0 EXACT REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR}/include)
link_directories(${OpenCV_LIBRARY_DIRS})

file(GLOB SOURCE_CPP *.cpp)
file(GLOB SOURCE_H *.h)

add_executable(${PROJECT_NAME} ${SOURCE_CPP} ${SOURCE_H})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})
