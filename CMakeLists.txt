cmake_minimum_required(VERSION 3.17)
project(kds_baseline)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(kds_baseline main.cpp DATA.h utils.h DATA.cpp)