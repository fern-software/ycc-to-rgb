cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)
project(cpp_arithmetic LANGUAGES C)
set(CMAKE_VERBOSE_MAKEFILE true)

# set warnings to all
set(CMAKE_C=_FLAGS "${CMAKE_C_FLAGS} -Wall")

# set standard
set(C_STANDARD C17)



# library
add_library(util lib/util.c)
target_include_directories(util PUBLIC include)

# executable
add_executable(ycctorgb app/ycctorgb.c)
target_include_directories(ycctorgb PUBLIC include)
target_link_libraries(ycctorgb util)
