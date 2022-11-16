/*
 *  graph.cpp
 *  implementation file for the graph class
 *  author: jordan sun
 */

#include "graph.h"
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

// returns the size of the graph
size_t Graph::size() const
{
    return nodes.size();
}

// add a node to the graph, return true if successful
bool Graph::add_node(Node node)
{
    for (auto &n : nodes) {
        if (n == node) {
            return false;
        }
    }
    nodes.push_back(node);
    return true;
}

void print_path(const Node *node)
{
    if (node->last) {
        print_path(node->last);
        cout << " -> ";
    }
    cout << node->name;
}

// add an edge to the graph, return true if successful
bool Graph::add_edge(string src_name, string dest_name)
{
    // find the source and destination nodes
    Node *src = nullptr;
    Node *dest = nullptr;
    for (auto &n : nodes) {
        if (n.name == src_name) {
            src = &n;
        }
        if (n.name == dest_name)
        {
            dest = &n;
        }
    }
    
    // if either node is not found, return false
    if (!src || !dest) {
        cout << "Error: node not found" << endl;
        return false;
    }

    // if src is the same as dest, return false
    if (src_name == dest_name)
    {
        cout << dest_name << " -> " << src_name << endl;
        return false;
    }

    // check if there exist a path from src to dest
    src->last = nullptr;
    Node *curr = src;
    list<Node *> stack;
    stack.push_front(curr);

    while (!stack.empty())
    {
        curr = stack.front();
        stack.pop_front();

        // if the current node is the source, return false
        if (curr == dest)
        {
            print_path(curr);
            cout << " -> " << src->name << endl;
            return false;
        }

        // add the requestors of the current node to the stack
        for (auto requestor : curr->requestors)
        {
            requestor->last = curr;
            stack.push_front(requestor);
        }
    }

    // add the source to the destination's requestors
    if (dest->add_requestor(src)) {
        return true;
    }
    cout << "Error: edge already exists" << endl;
    return false;
}

// operators
ostream& operator<<(ostream& os, const Graph& graph)
{
    for (auto &node : graph.nodes) {
        os << node;
    }
    return os;
}