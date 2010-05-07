cmake_minimum_required(VERSION 2.6)

project(rosyarp_experiments)

find_package(Boost 1.34 COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set(ROS_ROOT "$ENV{ROS_ROOT}" CACHE STRING "Path to ROS")
if (NOT ROS_ROOT)
  message(FATAL_ERROR "Please set ROS_ROOT")
endif ()

include_directories(${ROS_ROOT}/core/roslib/include)
include_directories(${ROS_ROOT}/core/roscpp/include)
link_directories(${ROS_ROOT}/core/roscpp/lib)

add_executable(rosyarp_transport rosyarp_transport.cpp)
target_link_libraries(rosyarp_transport ros ${Boost_LIBRARIES})
