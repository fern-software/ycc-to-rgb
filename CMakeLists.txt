cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)
project(ycctorgb LANGUAGES C)
set(CMAKE_VERBOSE_MAKEFILE true)

// TODO: use only one library instead of two

# set warnings to all
set(CMAKE_C=_FLAGS "${CMAKE_C_FLAGS} -Wall")

# set standard
set(C_STANDARD C17)

# library
add_library(util lib/util.c)
add_library(conversion lib/conversion.c)
target_include_directories(util PUBLIC include)
target_include_directories(conversion PUBLIC include)

# executables
add_executable(ycc2rgb app/ycc2rgb.c)
target_include_directories(ycc2rgb PUBLIC include)
target_link_libraries(ycc2rgb util)
target_link_libraries(ycc2rgb conversion)

add_executable(rgb2ycc app/rgb2ycc.c)
target_include_directories(rgb2ycc PUBLIC include)
target_link_libraries(rgb2ycc util)
target_link_libraries(rgb2ycc conversion)
