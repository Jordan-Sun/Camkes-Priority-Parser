cmake_minimum_required(VERSION 3.0.0)
project(DAGParser VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(NodeTest node_test.cpp node.cpp)
add_executable(GraphTest graph_test.cpp graph.cpp node.cpp)
add_executable(DAGParser main.cpp node.cpp graph.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
