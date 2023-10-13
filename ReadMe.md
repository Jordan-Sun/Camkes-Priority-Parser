# Camkes Priority Parser

## Introduction

Camkes priority parser provides a parser that parse a .dot formatted dag tree and a setup file or a camkes configuration file. The parser will then print the computed `priority` and `num_threads` to `stdout`. It additionally warns the user if there are potential overcounting or other issues.

## Insallation 

The parser can be build from source rather quickly through running cmake:
```
git clone https://github.com/Jordan-Sun/Camkes-Priority-Parser.git
cmake CMakeList.txt
make
```

## Usage

Usage: `DAGParser -g|--graph <dag_file> -c|--config <priority_file> [-l|--log <log_file>] [-r|--replace <output_file>] [--extra]`

- `<dag_file>` is the path to the the .dot format file to parse the dag tree from.  
- `<priority_file>` is the path to the setup file or camkes configuration file to parse the `_priority` of the tasks and the `r_priority_protocol` from.
- `<log_file>` is the path to the log file to print to log to, otherwise the log will be printed to `default.log`.
- `<replacement_file>` is the path to the output file to printed the configuration file with the corresponding arguments replaced.
- if the extra flag is set, an extra thread will be added to `r_num_threads`.

## Example

Test files could be found under the `TestFiles` folder.

### Non-diamond graph
Run `./DAGParser -g TestFiles/graph.dot -c TestFiles/task-system.camkes`.  
The output should be
```
pip.r_priority = 30;
pip.r_num_threads = 2;
propagation.r_priority = 40;
propagation.r_num_threads = 2;
ipcp.r_priority = 40;
ipcp.r_num_threads = 1;
```

### Diamond graph
Run `./DAGParser -g TestFiles/diamond-graph.dot -c TestFiles/diamond-task-system.camkes --extra` for a different set of test files with an extra `r_num_threads`.  
The output should be
```
pip.r_priority = 20;
pip.r_num_threads = 3;
propagation.r_priority = 30;
propagation.r_num_threads = 3;
ipcp.r_priority = 30;
ipcp.r_num_threads = 2;
```
