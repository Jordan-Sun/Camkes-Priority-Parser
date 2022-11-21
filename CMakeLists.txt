cmake_minimum_required(VERSION 3.0.0)
project(DAGParser VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 11)

add_executable(NodeTest node_test.cpp node.cpp)
add_executable(GraphTest graph_test.cpp graph.cpp node.cpp)
add_executable(DAGParser main.cpp node.cpp graph.cpp)

add_test(NAME NodeTest COMMAND NodeTest)
add_test(NAME GraphTest COMMAND GraphTest)
add_test(NAME ParseGraph COMMAND DAGParser ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/graph.dot ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/task-system.camkes)
add_test(NAME ParseDiamondGraph COMMAND DAGParser ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/diamond-graph.dot ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/diamond-task-system.camkes)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
