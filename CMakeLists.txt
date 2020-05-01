cmake_minimum_required(VERSION 3.13)
project(blueprint)

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/codegen/token_kind_generator.py)

set(CMAKE_CXX_STANDARD 14)
file(GLOB SOURCES src/*.cpp)
include_directories(headers)
add_executable(blueprint ${SOURCES})
