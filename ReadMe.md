# Camkes Priority Parser

![Build Badge](https://img.shields.io/github/workflow/status/Jordan-Sun/Camkes-Priority-Parser/CMake/master)

Usage: `DAGParser -g dag_file -c priority_file [-l log_file | --extra]`

- Parse the dag tree from the .dot format file `dag_file`.  
- Parse the `_priority` of the tasks and the `r_priority_protocol` from either a setup file or a camkes configuration file `priority_file`.  
- Prints the computed `r_priority` and `r_num_threads` to `stdout`.  
- Prints the log to `log_file` or `default.log` by default.

## Examples
1. Open shell at the current folder.
2. Run `cmake CMakeList.txt` to setup cmake.
3. Run `make` to build the `DAGParser` program.
4. Run `./DAGParser -g TestFiles/graph.dot -c TestFiles/task-system.camkes`.  
5. The output should be
```
pip.r_priority = 30;
pip.r_num_threads = 2;
propagation.r_priority = 40;
propagation.r_num_threads = 2;
ipcp.r_priority = 40;
ipcp.r_num_threads = 1;
```
6. Run `./DAGParser -g TestFiles/diamond-graph.dot -c TestFiles/diamond-task-system.camkes --extra` for a different set of test files with an extra `r_num_threads`.  
7. The output should be
```
pip.r_priority = 20;
pip.r_num_threads = 3;
propagation.r_priority = 30;
propagation.r_num_threads = 3;
ipcp.r_priority = 30;
ipcp.r_num_threads = 2;
```