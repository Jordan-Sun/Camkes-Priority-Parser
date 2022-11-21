# CMake generated Testfile for 
# Source directory: /Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist
# Build directory: /Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(NodeTest "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/NodeTest")
set_tests_properties(NodeTest PROPERTIES  _BACKTRACE_TRIPLES "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/CMakeLists.txt;13;add_test;/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/CMakeLists.txt;0;")
add_test(GraphTest "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/GraphTest")
set_tests_properties(GraphTest PROPERTIES  _BACKTRACE_TRIPLES "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/CMakeLists.txt;14;add_test;/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/CMakeLists.txt;0;")
add_test(ParseGraph "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/DAGParser" "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/TestFiles/graph.dot" "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/TestFiles/task-system.camkes")
set_tests_properties(ParseGraph PROPERTIES  _BACKTRACE_TRIPLES "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/CMakeLists.txt;15;add_test;/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/CMakeLists.txt;0;")
add_test(ParseDiamondGraph "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/DAGParser" "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/TestFiles/diamond-graph.dot" "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/TestFiles/diamond-task-system.camkes")
set_tests_properties(ParseDiamondGraph PROPERTIES  _BACKTRACE_TRIPLES "/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/CMakeLists.txt;16;add_test;/Users/jor/Documents/School/WashU/FL2022/Student/M&G Research/M Assist/CMakeLists.txt;0;")
