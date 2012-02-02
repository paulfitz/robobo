find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})
link_libraries(${YARP_LIBRARIES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
add_executable(yarp_pt_listener yarp_pt_listener.cpp)
add_executable(yarp_pt_talker yarp_pt_talker.cpp)

