cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)
project(ycctorgb LANGUAGES C)
set(CMAKE_VERBOSE_MAKEFILE true)

option(EXPORT_ASM "Save assembly and temp objects while compiling" false)

if (EXPORT_ASM)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -save-temps")
endif()

# set warnings to all
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# set standard
set(C_STANDARD C17)

# library
add_library(colourspace lib/util.c lib/conversion.c)
target_include_directories(colourspace PUBLIC include)

# executables
add_executable(ycc2rgb app/ycc2rgb.c)
target_include_directories(ycc2rgb PUBLIC include)
target_link_libraries(ycc2rgb colourspace)

add_executable(rgb2ycc app/rgb2ycc.c)
target_include_directories(rgb2ycc PUBLIC include)
target_link_libraries(rgb2ycc colourspace)
