cmake_minimum_required(VERSION 3.7)
project(argparser)

set(CMAKE_CXX_STANDARD 17)

add_library(argparser STATIC ArgParser.cpp)

target_include_directories(argparser PUBLIC "include/")

get_property(TARGETS DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY BUILDSYSTEM_TARGETS)
get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if(HAS_PARENT)
set(ARGPARSER_INCLUDES "${PROJECT_SOURCE_DIR}/include" PARENT_SCOPE)
set(ARGPARSER_LIBS "${TARGETS}" PARENT_SCOPE)
endif()