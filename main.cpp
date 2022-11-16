/*
 *  main.cpp
 *  entry point for the program
 *  author: jordan sun
 */

#include "main.h"
#include "node.h"
#include "graph.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

using namespace std;

int main(int argc, char* argv[])
{
    regex node_regex("\".*\" \\[.*\\]");
    regex edge_regex("\".*\" -> \".*\"");
    regex node_name_regex("\".*\"");
    regex priority_regex(".*\\._priority = [0-9]+");
    string line;
    smatch match;
    Graph graph;

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

    // parse dag file
    while (getline(dag_file, line))
    {
        // check for node
        if (regex_search(line, match, node_regex))
        {
            // find the node name
            string node = match.str();
            istringstream iss(node);
            // erase quotes from the matched node name
            string node_name;
            iss >> node_name;
            node_name.erase(std::remove(node_name.begin(), node_name.end(), '\"'), node_name.end());
            // add the node to the graph
            cout << "Found node: " << node_name << endl;
            Node n(node_name);
            graph.add_node(n);
        }
        // check for edge
        if (regex_search(line, match, edge_regex))
        {
            // find the node names
            string edge = match.str();
            istringstream iss(edge);
            // erase quotes from the matched node names
            string src_name, discard, dest_name;
            iss >> src_name >> discard >> dest_name;
            src_name.erase(std::remove(src_name.begin(), src_name.end(), '\"'), src_name.end());
            dest_name.erase(std::remove(dest_name.begin(), dest_name.end(), '\"'), dest_name.end());
            // add the edge to the graph
            cout << "Found edge: " << src_name << " -> " << dest_name << endl;
            graph.add_edge(src_name, dest_name);
        }
    }
    // close dag file
    dag_file.close();

    // open priority file
    ifstream priority_file(argv[PRIORITY_FILE]);
    if (!priority_file.is_open())
    {
        cout << "Error: could not open priority file " << argv[PRIORITY_FILE] << endl;
        return FAILED_TO_OPEN_FILE;
    }

    // parse priority file
    while(getline(priority_file, line))
    {
        // check for priority
        if (regex_search(line, match, priority_regex))
        {
            // find the node name and priority
            string priority = match.str();
            replace(priority.begin(), priority.end(), '.', ' ');
            istringstream iss(priority);
            string node_name, discard, equals, priority_value;
            iss >> node_name >> discard >> equals >> priority_value;
            // set the node priority
            cout << "Found priority: " << node_name << " = " << priority_value << endl;
            graph.get_node(node_name)->priority = stoi(priority_value);
        }
    }

    // close priority file
    priority_file.close();

    // print the graph
    cout << "Graph:" << endl << graph << endl;

    return SUCCESS;
}
