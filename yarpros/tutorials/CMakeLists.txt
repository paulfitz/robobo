include_directories(${ROS_ROOT}/core/rosconsole/include)
include_directories(${ROS_ROOT}/3rdparty/xmlrpcpp/src)
include_directories(${ROS_ROOT}/std_msgs/msg_gen/cpp/include)
link_directories(${ROS_ROOT}/core/roslib/lib)
link_directories(${ROS_ROOT}/core/rosconsole/lib)

add_executable(talker talker.cpp)
target_link_libraries(talker rosconsole roslib ros)
add_executable(listener listener.cpp)
target_link_libraries(listener rosconsole roslib ros)
add_executable(add_two_ints_server add_two_ints_server.cpp)
target_link_libraries(add_two_ints_server rosconsole roslib ros)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(yarpmin yarpmin.h yarpmin.c)

add_executable(mini_talker mini_talker.cpp)
target_link_libraries(mini_talker yarpmin)

