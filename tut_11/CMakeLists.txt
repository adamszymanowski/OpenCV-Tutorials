# OpenCV requirements
cmake_minimum_required(VERSION 2.8)
set( OpenCV_DIR "~/build" )
find_package( OpenCV REQUIRED )

# Compile and link source file
project( source )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( app source.cpp )
target_link_libraries( app ${OpenCV_LIBS} )