cmake_minimum_required(VERSION 2.6)
project(http_parser)
enable_testing()
set(CMAKE_BUILD_TYPE "Debug")
add_definitions(-std=c++11)
message(STATUS ${CXX_FLAGS})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR})
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_BINARY_DIR}/libs)

macro(add_vg_source_dir name)
    file(GLOB SRC_FILE ${name}/*.h ${name}/*.hpp ${name}/*.cc ${name}/*.cpp ${name}/*.c)
    list(APPEND ALL_SRC ${SRC_FILE})
    source_group(${name} FILES ${SRC_FILE})
endmacro()

add_vg_source_dir(parser)

file(GLOB SRC_FILE *.h *.cpp)
list(APPEND ALL_SRC ${SRC_FILE})

add_library(http_parser STATIC ${ALL_SRC})