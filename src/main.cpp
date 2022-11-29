/*
 *  main.cpp
 *  entry point for the program
 *  author: jordan sun
 */

#include "main.h"
#include "node.h"
#include "graph.h"
#include <getopt.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>

using namespace std;

static int extra_thread_flag = false;
static struct option long_options[] =
    {
        {"extra", no_argument, &extra_thread_flag, true},
        {"graph", required_argument, 0, 'g'},
        {"config", required_argument, 0, 'c'},
        {"log", required_argument, 0, 'l'},
        {"replace", required_argument, 0, 'r'},
        {0, 0, 0, 0}};

int main(int argc, char* argv[])
{
    // options
    string dag_file_name = "";
    string priority_file_name = "";
    string log_file_name = "default.log";
    string replace_file_name = "";

    // boolean flags
    bool graph_flag = false;
    bool config_flag = false;
    bool replacement_flag = false;

    // regex for parsing the input file
    regex node_regex("\".*\" \\[.*\\]");
    regex edge_regex("\".*\" -> \".*\"");
    regex node_shape_regex("shape=[a-z]+");

    regex priority_regex(".*\\._priority = [0-9]+");
    regex protocol_regex(".*\\.r_priority_protocol = \".*\"");
    regex r_priority_regex("([a-zA-Z]+)\\.r_priority = (.*)");
    regex r_num_threads_regex("([a-zA-Z]+)\\.r_num_threads = (.*)");

    // helper variables
    string line;
    smatch match;
    vector<string> acceptable_shapes = {"box", "circle"};
    vector<string> ignored_nodes;
    Graph graph;

    // parse the command line arguments
    while (true)
    {
        int option_index = 0;
        int c = getopt_long(argc, argv, "g:c:l:r:", long_options, &option_index);
        
        if (c == -1)
            break;

        switch (c)
        {
        case 'g':
            dag_file_name = optarg;
            graph_flag = true;
            break;
        
        case 'c':
            priority_file_name = optarg;
            config_flag = true;
            break;

        case 'l':
            log_file_name = optarg;
            break;
        
        case 'r':
            replace_file_name = optarg;
            replacement_flag = true;
            break;

        default:
            break;
        }
    }

    // check if the required arguments are present
    if (!graph_flag || !config_flag)
    {
        if (!graph_flag)
            cout << "Error: graph file not specified" << endl;
        if (!config_flag)
            cout << "Error: config file not specified" << endl;
        cout << "Usage: " << argv[0] << " -g|--graph <dag_file> -c|--config <priority_file> [-l|--log <log_file>] [--extra]" << endl;
        return INVALID_ARGS;
    }

    // open dag file
    ifstream dag_file(dag_file_name);
    if (!dag_file.is_open())
    {
        cerr << "Error: could not open dag file " << dag_file_name << endl;
        return FAILED_TO_OPEN_FILE;
    }

    // open priority file
    ifstream priority_file(priority_file_name);
    if (!priority_file.is_open())
    {
        cerr << "Error: could not open priority file " << priority_file_name << endl;
        return FAILED_TO_OPEN_FILE;
    }

    // open log file
    ofstream log_file(log_file_name);
    if (!log_file.is_open())
    {
        cerr << "Error: could not open log file " << log_file_name << endl;
        return FAILED_TO_OPEN_FILE;
    }

    // parse dag file
    while (getline(dag_file, line))
    {
        // check for node
        if (regex_search(line, match, node_regex))
        {
            string node = match.str();
            // find the node name
            istringstream iss(node);
            string node_name;
            iss >> node_name;
            // erase quotes from the matched node name
            node_name.erase(std::remove(node_name.begin(), node_name.end(), '\"'), node_name.end());
            // find the node shape
            if (regex_search(node, match, node_shape_regex))
            {
                string shape_label = match.str();
                replace(shape_label.begin(), shape_label.end(), '=', ' ');
                istringstream iss(shape_label);
                string discard, shape;
                iss >> discard >> shape;
                // add the node to the graph if it is acceptable
                if (find(acceptable_shapes.begin(), acceptable_shapes.end(), shape) != acceptable_shapes.end())
                {
                    auto n = make_shared<Node>(node_name, shape, extra_thread_flag);
                    if (graph.add_node(n))
                    {
                        log_file << "Added " << shape << " node: " << node_name << endl;
                    }
                    else
                    {
                        cerr << "Error: node " << node_name << " already exists" << endl;
                    }
                }
                // add the node to the list of ignored nodes
                else
                {
                    log_file << "Ignored " << shape << " node: " << node_name << endl;
                    ignored_nodes.push_back(node_name);
                }
            }
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
            // skip the edge if either node is ignored
            if (find(ignored_nodes.begin(), ignored_nodes.end(), src_name) != ignored_nodes.end() ||
                find(ignored_nodes.begin(), ignored_nodes.end(), dest_name) != ignored_nodes.end())
            {
                log_file << "Ignored edge: " << src_name << " -> " << dest_name << endl;
            }
            // otherwise try to add the edge to the graph
            else if (graph.add_edge(src_name, dest_name))
            {
                log_file << "Added edge: " << src_name << " -> " << dest_name << endl;
            }
        }
    }
    // close dag file
    dag_file.close();

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
            log_file << "Found priority: " << node_name << " = " << priority_value << endl;
            graph.get_node(node_name)->priority = stoi(priority_value);
        }

        // check for protocol
        if (regex_search(line, match, protocol_regex))
        {
            // find the node name and protocol
            string protocol = match.str();
            replace(protocol.begin(), protocol.end(), '.', ' ');
            istringstream iss(protocol);
            string node_name, discard, equals, protocol_value;
            iss >> node_name >> discard >> equals >> protocol_value;
            // erase quotes from the matched protocol
            protocol_value.erase(std::remove(protocol_value.begin(), protocol_value.end(), '\"'), protocol_value.end());
            // set the node protocol
            log_file << "Found protocol: " << node_name << " = " << protocol_value << endl;
            graph.get_node(node_name)->protocol = get_protocol(protocol_value);
        }
    }

    // print the graph
    cout << graph << endl;

    if (replacement_flag)
    {
        // copy the config file to the tmp file but replace the r_priority and r_num_threads fields
        priority_file.clear();
        priority_file.seekg(0, ios::beg);
        ofstream replace_file(replace_file_name);
        if (!replace_file.is_open())
        {
            cerr << "Error: could not open replace file " << replace_file_name << endl;
            return FAILED_TO_OPEN_FILE;
        }

        while(getline(priority_file, line))
        {
            if (regex_search(line, match, r_priority_regex))
            {
                string node_name = match.str(1);
                auto node = graph.get_node(node_name);
                if (node)
                {
                    line = regex_replace(line, r_priority_regex, "$1.r_priority = " + to_string(node->get_max_priority().second));
                    log_file << "Found r_priority node: " << node_name << endl;
                }
                else
                {
                    cerr << "Could not find node: " << node_name << endl;
                }
            }
            else if (regex_search(line, match, r_num_threads_regex))
            {
                string node_name = match.str(1);
                auto node = graph.get_node(node_name);
                if (node)
                {
                    line = regex_replace(line, r_num_threads_regex, "$1.r_num_threads = " + to_string(node->get_num_requestors()));
                    log_file << "Found r_num_threads node: " << node_name << endl;
                }
                else
                {
                    cerr << "Could not find node: " << node_name << endl;
                }
            }
            replace_file << line << endl;
        }
    }

    // close priority file
    priority_file.close();


    return SUCCESS;
}
