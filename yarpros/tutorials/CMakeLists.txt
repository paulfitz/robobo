
add_subdirectory(yarp)

link_libraries(log4cxx XmlRpc)

include_directories($ENV{ROS_ROOT}/core/rosconsole/include)
include_directories($ENV{ROS_ROOT}/3rdparty/xmlrpcpp/src)
include_directories($ENV{ROS_ROOT}/std_msgs/msg_gen/cpp/include)

include_directories($ENV{ROS_ROOT}/core/roscpp/include)
include_directories($ENV{ROS_ROOT}/core/roslib/include)

link_directories($ENV{ROS_ROOT}/core/roslib/lib)
link_directories($ENV{ROS_ROOT}/core/rosconsole/lib)

add_executable(talker talker.cpp)
target_link_libraries(talker rosconsole roslib ros)
add_executable(int_talker int_talker.cpp)
target_link_libraries(int_talker rosconsole roslib ros)
add_executable(listener listener.cpp)
target_link_libraries(listener rosconsole roslib ros)
add_executable(add_two_ints_server add_two_ints_server.cpp)
target_link_libraries(add_two_ints_server rosconsole roslib ros)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(yarpmin yarpmin.h yarpmin.c)

add_executable(mini_talker mini_talker.cpp)
target_link_libraries(mini_talker yarpmin)

add_executable(pt_talker pt_talker.cpp)
target_link_libraries(pt_talker rosconsole roslib ros)

add_executable(pt_listener pt_listener.cpp)
target_link_libraries(pt_listener rosconsole roslib ros)


