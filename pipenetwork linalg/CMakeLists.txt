cmake_minimum_required( VERSION 3.4.3 )

# Project name and programming language
project( pipenetwork CXX )

# Gather files and store paths in CMake variables
file( GLOB LIBRARY_SOURCE_FILES library/src/*.cpp )
file( GLOB TEST_SOURCE_FILES library/test/*.cpp )
file( GLOB HEADER_FILES library/inc/*.h* )
file( GLOB LINALG_SOURCE_FILES external/linalg/src/*.cpp )
file( GLOB LINALG_TEST_SOURCE_FILES external/linalg/test/*.cpp )
file( GLOB LINALG_HEADER_FILES external/linalg/inc/*.h* )

# Specify the folders with header files, otherwise our includes are not found
include_directories( external/catch )
include_directories( external/linalg/inc)
include_directories( library/inc )

# Enables exporting all symbols to the dll on windows
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

# When compiling with gcc we need to compile libraries with fPIC (stands for
# position independent code).
if( CMAKE_COMPILER_IS_GNUCXX )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11 -Wall -Wextra" )
endif( CMAKE_COMPILER_IS_GNUCXX )

# Add compilation target for our library
add_library( pipenetwork SHARED ${LIBRARY_SOURCE_FILES} ${HEADER_FILES} )
add_library( linalg SHARED ${LINALG_SOURCE_FILES} ${LINALG_HEADER_FILES} )

# Add compilation target for our executables
add_executable( pipenetwork_testrunner ${TEST_SOURCE_FILES} ${HEADER_FILES} )
add_executable( main drivers/main.cpp ${HEADER_FILES} )

# Add link depenencies
target_link_libraries( pipenetwork linalg ) #should be wroten first 
target_link_libraries( pipenetwork_testrunner pipenetwork )
target_link_libraries( main pipenetwork )
target_link_libraries( main linalg )
