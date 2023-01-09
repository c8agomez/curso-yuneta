##############################################
#   CMake
##############################################
project(01_Course C)
cmake_minimum_required(VERSION 3.0)
include(CheckIncludeFiles)
include(CheckSymbolExists)

set(CMAKE_INSTALL_PREFIX /home/yuneta/curso-yuneta/)

set(BIN_DEST_DIR ${CMAKE_INSTALL_PREFIX}/runfile)

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

SET (01_course
    src/hello_world.c
)

##############################################
#
##############################################
ADD_EXECUTABLE(hello_world01 ${01_course})

##############################################
#   Installation
##############################################
install(
    TARGETS hello_world01
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_WRITE GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE
    DESTINATION ${BIN_DEST_DIR}
)

