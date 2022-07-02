cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)
project(cpp_arithmetic LANGUAGES C)
set(CMAKE_VERBOSE_MAKEFILE true)

# set warnings to all
set(CMAKE_C=_FLAGS "${CMAKE_C_FLAGS} -Wall")

# set standard
set(C_STANDARD C17)

# executable
add_library(ycctorgb lib/util.c)
add_executable(main app/main.c)
target_include_directories(main PUBLIC include)
target_link_libraries(main ycctorgb)
