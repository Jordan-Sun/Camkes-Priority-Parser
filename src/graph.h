/*
 *  graph.h
 *  header file for the graph class
 *  author: jordan sun
 */
#pragma once

#include "node.h"
#include <memory>
#include <vector>

class Graph {
private:
    // nodes in the graph
    std::vector<std::shared_ptr<Node>> nodes;
    static std::vector<std::string> displayed_shapes;

public:
    Graph() = default;
    ~Graph() = default;

    // add a node to the graph, return true if successful
    bool add_node(std::shared_ptr<Node> node);
    // add an edge to the graph, return true if successful
    bool add_edge(std::string src_name, std::string dest_name);

    // returns the size of the graph
    size_t size() const;
    // returns a node in the graph
    std::shared_ptr<Node> get_node(std::string name);

    // operators
    friend std::ostream& operator<<(std::ostream &os, const Graph &graph);
};