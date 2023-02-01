#############################################
#   CMake
##############################################
project(Curso-yuneta C)
cmake_minimum_required(VERSION 3.0)


##############################################
#   Source
##############################################
add_subdirectory(01-print-hello-world/c)
add_subdirectory(02-print-hello-world-loop/c)
add_subdirectory(03-print-hello-name-loop/c)
add_subdirectory(04-tcpuv/c)
add_subdirectory(05-tcpuv/c)
add_subdirectory(06-tcpuv-list_files/c)

# compile in Release mode optimized but adding debug symbols, useful for profiling :
#
#     cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
#
# or compile with NO optimization and adding debug symbols :
#
#     cmake -DCMAKE_BUILD_TYPE=Debug ..
#
# Compilando para ARM poner cmake -DNOT_INCLUDE_LIBUNWIND
#

