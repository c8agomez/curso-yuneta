##############################################
#   CMake
##############################################
project(04_listenconnect)
cmake_minimum_required(VERSION 3.0)
include(CheckIncludeFiles)
include(CheckSymbolExists)

set(CMAKE_INSTALL_PREFIX /yuneta/development/projects/curso-yuneta/carlos-ochoa)

set(BIN_DEST_DIR ${CMAKE_INSTALL_PREFIX}/bin)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c99")

if(CMAKE_BUILD_TYPE MATCHES Debug)
  add_definitions(-DDEBUG)
  option(SHOWNOTES "Show preprocessor notes" OFF)

  if(CMAKE_COMPILER_IS_GNUCC)
    # GCC specific debug options
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
    set(AVOID_VERSION -avoid-version)
  endif(CMAKE_COMPILER_IS_GNUCC)
endif(CMAKE_BUILD_TYPE MATCHES Debug)

add_definitions(-D_GNU_SOURCE)
add_definitions(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64)

check_include_files(regex.h HAVE_REGEX_H)
if(HAVE_REGEX_H)
    add_definitions(-DHAVE_REGEX_H)
else(HAVE_REGEX_H)
    message("***  WARNING: GNU C regex library not found.")
endif(HAVE_REGEX_H)


##############################################
#   Source
##############################################
SET (04_course
    src/listenconnect.c
)

##############################################
# EXECUTABLE
##############################################
ADD_EXECUTABLE(listenconnect ${04_course})

TARGET_LINK_LIBRARIES(listenconnect
    /yuneta/development/output/lib/libuv.a

    pthread dl  # used by libuv
    lzma        # used by libunwind
    z rt m
    uuid
    util
)

##############################################
#   Installation
##############################################
install(
    TARGETS listenconnect
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_WRITE GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
    DESTINATION ${BIN_DEST_DIR}
)

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
