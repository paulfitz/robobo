cmake_minimum_required(VERSION 2.6)

find_package(YARP REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include ${YARP_INCLUDE_DIRS})

add_executable(eventy src/main.cpp src/IntegralImage.cpp)
target_link_libraries(eventy ${YARP_LIBRARIES})

