cmake_minimum_required(VERSION 2.6)

project(thrift_compiler)


# thrift/compiler/cpp
set(THRIFT_ROOT "" CACHE PATH "Location of thrift compiler source") 

file(GLOB_RECURSE folder_source ${THRIFT_ROOT}/src/*.cc)
file(GLOB_RECURSE folder_source2 ${THRIFT_ROOT}/src/*.c)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(${THRIFT_ROOT})
include_directories(${THRIFT_ROOT}/src)
BISON_TARGET(tcc_parser ${THRIFT_ROOT}/src/thrifty.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc)
FLEX_TARGET(tcc_scanner ${THRIFT_ROOT}/src/thriftl.ll  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc)
ADD_FLEX_BISON_DEPENDENCY(tcc_scanner tcc_parser)


include_directories(${CMAKE_SOURCE_DIR})
add_executable(tcc ${folder_source} ${folder_source2} 
  ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc)

