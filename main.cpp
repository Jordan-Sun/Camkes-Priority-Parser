/*
 *  main.cpp
 *  entry point for the program
 *  author: jordan sun
 */

#include "main.h"
#include "node.h"
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

int main(int argc, char* argv[])
{
    // check for correct number of arguments
    if (argc != NUM_ARGS)
    {
        cout << "Usage: " << argv[PROGRAM_NAME] << " <dag file> <priority file>" << endl;
        return INVALID_ARGS;
    }

    // open dag file
    ifstream dag_file(argv[DAG_FILE]);
    if (!dag_file.is_open())
    {
        cout << "Error: could not open dag file " << argv[DAG_FILE] << endl;
        return FAILED_TO_OPEN_FILE;
    }

    int dag_parser_state = START;
    regex node_regex("\".*\" \\[label=\".*\", shape=box,style=rounded\\];");
    regex conn_regex("\".*\" \\[shape=circle\\];");
    regex edge_regex("\".*\" -> \".*\";");
    string line;
    smatch match;

    while (getline(dag_file, line))
    {
        switch (dag_parser_state)
        {
            case START:
                // check for start of dag
                if (line.find("{") != string::npos)
                {
                    dag_parser_state = NODE;
                }
                break;
            case NODE:
                // check for node
                if (regex_search(line, match, node_regex))
                {
                    cout << "Found node: " << match.str() << endl;
                }
                // check for conn
                else if (regex_search(line, match, conn_regex))
                {
                    cout << "Found conn: " << match.str() << endl;
                    dag_parser_state = EDGE;
                }
                break;
            case EDGE:
                // check for edge
                if (regex_search(line, match, edge_regex))
                {
                    cout << "Found edge: " << match.str() << endl;
                }
                // check for conn
                else if (regex_search(line, match, conn_regex))
                {
                    cout << "Found conn: " << match.str() << endl;
                }
                // check for end of dag
                else if (line.find("}") != string::npos)
                {
                    dag_parser_state = END;
                }
                break;
        }
    }

    return SUCCESS;
}
