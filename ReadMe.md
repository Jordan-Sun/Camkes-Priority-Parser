# Camkes Priority Parser

Parse the dag tree from a .dot format file.  
Parse the `_priority` of the tasks and the `r_priority_protocol` from a configuration file or a camkes configuration file.  
Prints the computed `r_priority` and `r_num_threads`.  
Prints the log to `log.txt`.

Usage: `./DAGParser <dag_file> <priority_file>`

## Examples
Open shell at the current folder.
Run `cmake CMakeList.txt` to setup cmake.
Run `make` to build the `DAGParser` program.
Run `./DAGParser TestFiles/graph.dot TestFiles/task-system.camkes`.
Alternatively, run `./DAGParser TestFiles/diamond-graph.dot TestFiles/diamond-task-system.camkes` for a different set of files.