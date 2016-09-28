project(Filtrage)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set (OpenCV_DIR /home/pierre/opencv/build)

cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
find_package( OpenCV REQUIRED )
add_executable( Filtrage main.cpp )
target_link_libraries( Filtrage ${OpenCV_LIBS} )
