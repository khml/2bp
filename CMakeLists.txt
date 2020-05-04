cmake_minimum_required(VERSION 3.13)
project(bp)

set(BP bp)
set(CMAKE_CXX_STANDARD 14)

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/codegen/token_kind_generator.py)

set(CYAN_LIB cyan)
file(GLOB CYAN_SOURCES cyan/cyan/src/*.cpp)
add_library(${CYAN_LIB} STATIC ${CYAN_SOURCES})
target_include_directories(${CYAN_LIB} PUBLIC cyan/cyan/include)

file(GLOB SOURCES src/*.cpp)

add_executable(${BP} ${SOURCES})
target_include_directories(${BP} PUBLIC headers)
target_link_libraries(${BP} ${CYAN_LIB})
#target_compile_definitions(${BP} PUBLIC DEBUG=0)