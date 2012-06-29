cmake_minimum_required(VERSION 2.6)

find_package(YARP REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src ${YARP_INCLUDE_DIRS})

add_executable(eventy src/main.cpp src/IntegralImage.cpp src/Pattern.cpp src/Pattern.h)
target_link_libraries(eventy ${YARP_LIBRARIES})

add_executable(invert src/invert.cpp src/Pattern.cpp src/Pattern.h)
target_link_libraries(invert ${YARP_LIBRARIES})

