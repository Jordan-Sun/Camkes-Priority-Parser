# Camkes Priority Parser

![Build Badge](https://img.shields.io/github/workflow/status/Jordan-Sun/Camkes-Priority-Parser/CMake/master)

Usage: `./DAGParser <dag_file> <priority_file>`

- Parse the dag tree from the .dot format file `<dag_file>`.  
- Parse the `_priority` of the tasks and the `r_priority_protocol` from either a setup file or a camkes configuration file `<priority_file>`.  
- Prints the computed `r_priority` and `r_num_threads` to `stdout`.  
- Prints the log to `log.txt`.

## Examples
1. Open shell at the current folder.
2. Run `cmake CMakeList.txt` to setup cmake.
3. Run `make` to build the `DAGParser` program.
4. Run `./DAGParser TestFiles/graph.dot TestFiles/task-system.camkes`.  
5. The output should be
```
pip.r_priority = 30;
pip.r_num_threads = 2;
propagation.r_priority = 40;
propagation.r_num_threads = 2;
ipcp.r_priority = 40;
ipcp.r_num_threads = 1;
```
6. Run `./DAGParser TestFiles/diamond-graph.dot TestFiles/diamond-task-system.camkes` for a different set of test files.  
7. The output should be
```
pip.r_priority = 20;
pip.r_num_threads = 2;
propagation.r_priority = 30;
propagation.r_num_threads = 2;
ipcp.r_priority = 30;
ipcp.r_num_threads = 1;
```