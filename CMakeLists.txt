cmake_minimum_required(VERSION 3.15)
project(survival_horror)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_CXX_STANDARD 20) # Requires C11 standard

add_executable(${PROJECT_NAME} main.cpp player.cpp world.cpp ray.cpp enemy.cpp)

target_link_libraries(${PROJECT_NAME} raylib)
include_directories(${PROJECT_NAME} include)
include_directories(${PROJECT_NAME} header)
# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

