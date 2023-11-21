cmake_minimum_required(VERSION 3.22.5)
project(archieve)

set(CXX_STANDARD_REQUIRED 17)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(archieve src/main.cpp src/image.cpp)

target_link_libraries(archieve ${OpenCV_LIBS})