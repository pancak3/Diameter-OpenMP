cmake_minimum_required(VERSION 3.6)
project(onePunch)

set(SOURCE_FILES onePunch.c graph-diameter.c graph-diameter-origin-parallel.c )
add_executable(onePunch ${SOURCE_FILES})