/*
 *  node.cpp
 *  implementation file for the node class
 *  author: jordan sun
 */ 

#include "node.h"

using namespace std;

Node::Node(string name, size_t priority)
: name(name), priority(priority)
{
}

// add a requestor to the node, return true if successful
bool Node::add_requestor(Node *requestor)
{
    return requestors.insert(requestor).second;
}

// check if the node has the given requestor
bool Node::has_requestor(Node *requestor) const
{
    return requestors.find(requestor) != requestors.end();
}

// returns the number of requestors of the node
size_t Node::get_num_requestors() const
{
    size_t num_requestors = 0;
    for (const Node *requestor : requestors)
    {
        // add the number of requestors of the requestor, plus 1 if the requestor is a true requestor
        num_requestors += requestor->get_num_requestors() + (requestor->priority ? 1 : 0);
    }
    return num_requestors;
}

// returns the maximum priority of the node and its requestors
pair<const Node *, size_t> Node::get_max_priority() const
{
    size_t max_priority = priority;
    const Node* max_priority_node = this;
    for (auto requestor : requestors)
    {
        auto requestor_priority = requestor->get_max_priority();
        if (requestor_priority.second > max_priority)
        {
            max_priority = requestor_priority.second;
            max_priority_node = requestor_priority.first;
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
    os << node.name << " has " << node.get_num_requestors() << " requestors, with a max priority of " << max_priority.second << " from " << max_priority.first->name << endl;
    return os;
}