/*
 *  node.cpp
 *  implementation file for the node class
 *  author: jordan sun
 */ 

#include "node.h"

using namespace std;

Protocol get_protocol(const std::string protocol)
{
    if (protocol == "inherited")
    {
        return Protocol::PIP;
    }
    else if (protocol == "propagated")
    {
        return Protocol::PROP;
    }
    else if (protocol == "fixed")
    {
        return Protocol::IPCP;
    }
    else
    {
        return Protocol::UNSET;
    }
}

Node::Node(string name, string shape, bool extra_thread, int priority, Protocol protocol)
    : name(name), shape(shape), extra_thread(extra_thread), priority(priority), protocol(protocol), last(nullptr)
{
}

// add a requestor to the node, return true if successful
bool Node::add_requestor(std::shared_ptr<Node> requestor)
{
    return immed_requestors.insert(requestor).second;
}

// check if the node has the given requestor
bool Node::has_requestor(std::shared_ptr<Node> requestor) const
{
    return immed_requestors.find(requestor) != immed_requestors.end();
}

// returns the requestors of the node
set<shared_ptr<const Node>> Node::get_requestors() const
{
    set<shared_ptr<const Node>> requestors;

    // only add itself if it uses the IPCP protocol
    if (protocol == Protocol::IPCP)
    {
        requestors.insert(shared_from_this());
    }
    // otherwise, add all the requestors of the requestor
    else
    {
        for (shared_ptr<const Node> requestor : immed_requestors)
        {
            // add the requestor if it is a true requestor
            if (requestor->priority != NONE)
            {
                requestors.insert(requestor);
            }
            // add the requestors of the requestor
            set<shared_ptr<const Node>> requestors_of_requestor = requestor->get_requestors();
            requestors.insert(requestors_of_requestor.begin(), requestors_of_requestor.end());
        }
    }

    return requestors;
}

// returns the number of requestors of the node
int Node::get_num_requestors() const
{
    return get_requestors().size();
}

// returns the task requestors of the node
set<shared_ptr<const Node>> Node::get_tasks() const
{
    set<shared_ptr<const Node>> requestors;

    for (shared_ptr<const Node> requestor : immed_requestors)
    {
        // add the requestor if it is a true requestor
        if (requestor->priority != NONE)
        {
            requestors.insert(requestor);
        }
        // add the requestors of the requestor
        set<shared_ptr<const Node>> requestors_of_requestor = requestor->get_requestors();
        requestors.insert(requestors_of_requestor.begin(), requestors_of_requestor.end());
    }

    return requestors;
}

// returns the maximum priority of the node and its requestors
pair<shared_ptr<const Node>, int> Node::get_max_priority() const
{
    int max_priority = priority;
    shared_ptr<const Node> max_priority_node = shared_from_this();

    for (auto requestor : get_tasks())
    {
        if (requestor->priority > max_priority)
        {
            max_priority = requestor->priority;
            max_priority_node = requestor;
        }
    }

    return make_pair(max_priority_node, max_priority);
}

// operators
bool Node::operator==(const Node& rhs) const
{
    return name == rhs.name;
}

ostream& operator<<(ostream& os, const Node& node)
{
    auto max_priority = node.get_max_priority();
    os << node.name << ".r_priority = " << max_priority.second << ";\n"
    << node.name << ".r_num_threads = " << node.get_num_requestors() + (node.extra_thread ? 1 : 0) << ";" << endl;
    return os;
}