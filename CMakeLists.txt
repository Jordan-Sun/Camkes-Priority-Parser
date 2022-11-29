cmake_minimum_required(VERSION 3.0.0)
project(DAGParser VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 11)

add_executable(NodeTest src/node_test.cpp src/node.cpp)
add_executable(GraphTest src/graph_test.cpp src/graph.cpp src/node.cpp)
add_executable(DAGParser src/main.cpp src/node.cpp src/graph.cpp)

add_test(NAME NodeTest COMMAND NodeTest)
add_test(NAME GraphTest COMMAND GraphTest)
add_test(NAME ParseGraph COMMAND DAGParser -g ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/graph.dot -c ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/task-system.camkes)
add_test(NAME ParseDiamondGraph COMMAND DAGParser -g ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/diamond-graph.dot -c ${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/diamond-task-system.camkes --extra)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
