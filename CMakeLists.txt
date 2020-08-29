cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)

project(renderer)

find_package(Vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_subdirectory(src)