cmake_minimum_required(VERSION 3.6)
project(project1)

set(SOURCE_FILES project1.cpp headers/graph.h headers/project1.h)
add_executable(project1 ${SOURCE_FILES})