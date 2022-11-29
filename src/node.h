/*
 *  node.h
 *  header file for the node class
 *  author: jordan sun
 */
#pragma once

#include <string>
#include <set>
#include <memory>
#include <ostream>

#define NONE -1

enum class Protocol
{
    UNSET,
    PIP,
    PROP,
    IPCP,
};

Protocol get_protocol(const std::string protocol);

class Node : public std::enable_shared_from_this<Node>
{
private:
    // returns the requestors of the node
    std::set<std::shared_ptr<const Node>> get_requestors() const;
    // returns the task requestors of the node
    std::set<std::shared_ptr<const Node>> get_tasks() const;
    // require an extra thread if true
    const bool extra_thread;

public:
    const std::string name;
    const std::string shape;
    // only a true requestor if the priority is not NONE
    int priority;
    Protocol protocol;
    std::set<std::shared_ptr<Node>> immed_requestors;
    // temp variable used in the graph class
    std::shared_ptr<Node> last;

    Node(std::string name, std::string shape, bool extra_thread = false, int priority = NONE, Protocol protocol = Protocol::UNSET);
    ~Node() = default;

    // add a requestor to the node, return true if successful
    bool add_requestor(std::shared_ptr<Node> requestor);

    // check if the node has the given requestor
    bool has_requestor(std::shared_ptr<Node> requestor) const;

    // returns the number of requestors of the node
    int get_num_requestors() const;

    // returns the maximum priority of the node and its requestors
    std::pair<std::shared_ptr<const Node>, int> get_max_priority() const;

    // operators
    bool operator==(const Node &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Node &node);
};