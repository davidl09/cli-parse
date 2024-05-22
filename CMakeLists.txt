cmake_minimum_required(VERSION 3.27)
project(cliparse)

set(CMAKE_CXX_STANDARD 23)

add_executable(cliparse main.cpp)

target_include_directories(cliparse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
