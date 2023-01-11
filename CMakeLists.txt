##############################################
#   CMake
##############################################
project(Hello_World C)
cmake_minimum_required(VERSION 3.0)
include(CheckIncludeFiles)
include(CheckSymbolExists)

set(CMAKE_INSTALL_PREFIX /home/yuneta/curso-yuneta)

set(BIN_DEST_DIR ${CMAKE_INSTALL_PREFIX})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")


##############################################
#   Source
##############################################
add_subdirectory(01-print-hello-world/c)
add_subdirectory(02-print-hello-world-loop/c)

# compile in Release mode optimized but adding debug symbols, useful for profiling :
#
#     cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_EXPORT_COMPILE_COMMANDS=On ..
#
# or compile with NO optimization and adding debug symbols :
#
#     cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=On ..
#
# Compilando para ARM poner cmake -DNOT_INCLUDE_LIBUNWIND
