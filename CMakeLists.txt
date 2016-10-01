project(Filtrage)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "-std=c++11")
set (OpenCV_DIR /home/pierre/opencv/build)


cmake_minimum_required(VERSION 2.8)

message(ol)
include_directories(include)


file(GLOB_RECURSE SRC src/*.cpp include/*.h)
aux_source_directory(. SRC_LIST)
find_package( OpenCV REQUIRED )
add_executable(Filtrage ${SRC})
target_link_libraries( Filtrage ${OpenCV_LIBS} )

