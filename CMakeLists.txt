cmake_minimum_required(VERSION 3.13)
project(bp)

set(BP bp)
set(CMAKE_CXX_STANDARD 14)

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/codegen/token_kind_generator.py)

file(GLOB SOURCES src/*.cpp)

add_executable(${BP} ${SOURCES})
target_include_directories(${BP} PUBLIC headers)
target_include_directories(${BP} PUBLIC cyan/include)
target_link_directories(${BP} PUBLIC cyan)
target_link_libraries(${BP} cyan.a)
